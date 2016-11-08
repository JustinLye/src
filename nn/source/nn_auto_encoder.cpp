#include "nn_auto_encoder.h"

using namespace nn::encoder;

const double training_policy::default_zero_out_pct = 0.40;
const double training_policy::default_gauss_std_dev = 0.001;

training_policy::training_policy() :
	base_training_policy(),
	_hidden_layer_dims(-1),
	_noising_method(NN_GAUSSIAN_METHOD),
	_noise_sigma(-1) {}

training_policy::training_policy(const training_policy& copy_policy) :
	base_training_policy(copy_policy),
	_hidden_layer_dims(copy_policy._hidden_layer_dims),
	_noising_method(copy_policy._noising_method),
	_noise_sigma(copy_policy._noise_sigma) {}

training_policy::training_policy(training_policy&& move_policy) :
	base_training_policy(move_policy),
	_hidden_layer_dims(std::move(move_policy._hidden_layer_dims)),
	_noising_method(std::move(move_policy._noising_method)),
	_noise_sigma(std::move(move_policy._noise_sigma)) {}

training_policy::training_policy(const nn::training_policy_info& init_policy_info) :
	base_training_policy(init_policy_info),
	_hidden_layer_dims(-1),
	_noising_method(NN_GAUSSIAN_METHOD),
	_noise_sigma(-1) {}

training_policy::training_policy(const nn::training_policy_info& init_policy_info, int init_hidden_dims, int noise_method) :
	base_training_policy(init_policy_info),
	_hidden_layer_dims(init_hidden_dims),
	_noising_method(NN_GAUSSIAN_METHOD) {}

void training_policy::print(std::ostream& s) const {
	base_training_policy::print(s);
	s << "\tHidden Dims:\t" << _hidden_layer_dims << std::endl;
	s << "\tNoise Method:\t";
	if (_noising_method == NN_GAUSSIAN_METHOD) {
		s << "GAUSSIAN";
	} else if (_noising_method == NN_ZERO_OUT_METHOD) {
		s << "ZERO OUT";
	} else {
		s << "NOT RECOGNIZED";
	}
	s << std::endl;
	s << "\tNoise Sigma:\t" << _noise_sigma << std::endl;
}


hidden_layer::hidden_layer() :
	base_hidden_layer(),
	policy(nullptr),
	noised_input(1, 1),
	has_targets_flag(false),
	has_noise_flag(false),
	dim_links_flag(false) {
	
	std::cerr << "error: this hidden_layer constructor is currently not supported. please use hidden_layer(input_layer*, output_layer*, const training_policy*)\n";
	throw std::runtime_error("unsupported constructor call\n");
}

hidden_layer::hidden_layer(const hidden_layer& copy_layer) :
	base_hidden_layer(copy_layer),
	policy(nullptr),
	noised_input(copy_layer.noised_input),
	has_targets_flag(copy_layer.has_targets_flag),
	has_noise_flag(copy_layer.has_noise_flag),
	dim_links_flag(copy_layer.dim_links_flag) {}


hidden_layer::hidden_layer(hidden_layer&& move_layer) :
	base_hidden_layer(move_layer),
	policy(nullptr),
	noised_input(std::move(move_layer.noised_input)),
	has_targets_flag(std::move(move_layer.has_targets_flag)),
	has_noise_flag(std::move(move_layer.has_noise_flag)),
	dim_links_flag(std::move(move_layer.dim_links_flag)) {}

hidden_layer::hidden_layer(nn::input_layer* init_input_layer, nn::output_layer* init_output_layer, const training_policy* init_training_policy) :
	base_hidden_layer(init_input_layer, init_output_layer),
	policy(init_training_policy),
	noised_input(1, 1),
	has_targets_flag(false),
	has_noise_flag(false),
	dim_links_flag(false) {
	initialize();
	if (!can_train()) {
		print_layer_status_errors("hidden_layer was not constructed.\nnote: input_layer, output_layer, and the training policy must be complete. Will allow pointers to incomplete layers or policies at a later date.\n Please USE hidden_layer(input_layer*, output_layer*, const training_policy*)");
		throw std::runtime_error("error: hidden_layer was not constructed");
	}
}

void hidden_layer::initialize() {
	set_target();
	add_noise();
	dim_links();
	if (!can_train()) {
		print_layer_status_warnings("some actions were not completed during hidden_layer initialization");
	}
}
	
void hidden_layer::clear_delta() {
	incoming_links.clear_delta();
	outgoing_links.clear_delta();
	clear_delta();
	output_nodes->clear_delta();

}
void hidden_layer::randomize_weights() {
	incoming_links.randomize_weights();
	outgoing_links.randomize_weights();
}


void hidden_layer::feed_forward(int rows_offset) {
	int sample_size = get_sample_size(rows_offset);

	//forward to hidden layer
	//network_values.topRows(sample_size) = (input_nodes->network_values.topRows(sample_size) * incoming_links.weights).rowwise() + incoming_links.bias;
	//forward to hidden layer then apply logistic sigmoid activation function to hidden layer
	network_activation.topRows(sample_size) = 1.0 / (Eigen::exp(((noised_input.topRows(sample_size) * incoming_links.weights).rowwise() + incoming_links.bias).array() * -1.0) + 1.0);
	//store first derivative
	network_activation_prime.topRows(sample_size) = network_activation_prime.topRows(sample_size).array() * (1.0 - network_activation_prime.topRows(sample_size).array());

	//forward to output layer then apply logistic sigmoid activation function to hidden layer
	output_nodes->network_activation.topRows(sample_size) = 1.0 / (Eigen::exp(((network_activation.topRows(sample_size) * outgoing_links.weights).rowwise() + outgoing_links.bias).array() * -1.0)*-1.0);
	//sort first derivative
	output_nodes->network_activation_prime.topRows(sample_size) = output_nodes->network_activation_prime.topRows(sample_size).array() * (1.0 - output_nodes->network_activation_prime.topRows(sample_size).array());
}
void hidden_layer::back_propogate(int rows_offset) {
	int sample_size = get_sample_size(rows_offset);

	// output layer
	output_nodes->network_sensitivity.topRows(sample_size) = output_nodes->network_error.topRows(sample_size).array() * output_nodes->network_activation_prime.topRows(sample_size).array();
	// not sure why we are dividing the sensitivity by the sample size
	outgoing_links.weights_delta += policy->lrate * network_activation.topRows(sample_size).transpose() * output_nodes->network_sensitivity.topRows(sample_size) / sample_size;
	// not sure why the bias is propogated this while or why we are dividing the sensitivity by the sample size
	outgoing_links.bias_delta += policy->lrate * output_nodes->network_sensitivity.topRows(sample_size).colwise().sum()/sample_size;

	// todo: add sparsity error term to hidden layer sensitivity

	// add the propogation of the outer layers delta's
	network_sensitivity.topRows(sample_size) = (output_nodes->network_sensitivity.topRows(sample_size) * outgoing_links.weights.transpose()).array() * network_activation_prime.topRows(sample_size).array();
	incoming_links.weights_delta.topRows(sample_size) += policy->lrate * input_nodes->network_values.topRows(sample_size).transpose() * network_sensitivity.topRows(sample_size) / sample_size;
	incoming_links.bias_delta.topRows(sample_size) += policy->lrate * network_sensitivity.topRows(sample_size).colwise().sum() / sample_size;

}

void hidden_layer::set_errors(int rows_offset) {
	int sample_size = get_sample_size(rows_offset);

	//output layer errors
	output_nodes->network_error.topRows(sample_size) = output_nodes->network_targets.topRows(sample_size) - output_nodes->network_activation.topRows(sample_size);

	//todo: apply sparsity error

	// weight regularization (or decay) : d/dw -(1/2)beta*W_ij^2 --> -beta * W_ij
	if (policy->use_weight_reg()) {
		incoming_links.weights_delta = incoming_links.weights * (-1.0 * policy->weight_reg_scaling());
		outgoing_links.weights_delta = outgoing_links.weights * (-1.0 * policy->weight_reg_scaling());
	}
}


void hidden_layer::add_noise() {
	has_noise_flag = false;
	if(is_complete()) {
		noised_input = input_nodes->network_values;
		switch (policy->noising_method()) {
		case NN_ZERO_OUT_METHOD:
			if (policy->noise_sigma() < 0) {
				_noise_gen.RandomZeroOut(noised_input, training_policy::default_zero_out_pct);
			} else {
				_noise_gen.RandomZeroOut(noised_input, policy->noise_sigma());
			}
			break;
		case NN_GAUSSIAN_METHOD:
		default:
			if (policy->noise_sigma() < 0) {
				_noise_gen.AddGaussianNoise(noised_input, training_policy::default_gauss_std_dev);
			} else {
				_noise_gen.AddGaussianNoise(noised_input, policy->noise_sigma());
			}
			break;
		}
		has_noise_flag = true;
	}
}
void hidden_layer::set_target() {
	has_targets_flag = false;
	if (is_complete()) {
		output_nodes->network_targets.resize(input_nodes->network_values.rows(), input_nodes->network_values.cols());
		output_nodes->network_targets = input_nodes->network_values;
		has_targets_flag = true;
	}
}

void hidden_layer::dim_links() {
	dim_links_flag = false;
	if (is_complete()) {
		if (policy->hidden_layer_dims() > 0) {
			incoming_links.reset(input_nodes->network_values.cols(), policy->hidden_layer_dims());
			outgoing_links.reset(policy->hidden_layer_dims(), output_nodes->network_values.cols());
			resize(input_nodes->network_values.rows(), policy->hidden_layer_dims());
			dim_links_flag = true;
		}
	}
}
//void hidden_layer::self_diagnostic() {}

void hidden_layer::print_layer_status_warnings(const char* additional_info) const {
	if(additional_info != nullptr)
		std::cerr << additional_info << std::endl;
	if (!has_targets_flag) {
		std::cerr << "warning: hidden_layer - output_nodes target matrix is not set." << std::endl;
	}
	if (!has_noise_flag) {
		std::cerr << "warning: hidden_layer - noised_input matrix is not set." << std::endl;
	}
	if (!dim_links_flag) {
		std::cerr << "warning: hidden_layer - incoming and/or outgoing links may not have valid dimension." << std::endl;
	}
}

void hidden_layer::print_layer_status_errors(const char* additional_info) const {
	if (additional_info != nullptr)
		std::cerr << additional_info << std::endl;

	if (!has_targets_flag) {
		std::cerr << "error: hidden layer - output_nodes target matrix is not set." << std::endl;
	}
	if (!has_noise_flag) {
		std::cerr << "error: hidden_layer - noised_input matrix is not set." << std::endl;
	}
	if (!dim_links_flag) {
		std::cerr << "error: hidden_layer - incoming and/or outgoing links may not have valid dimension." << std::endl;
	}
}

training_assistant::training_assistant() {}
training_assistant::training_assistant(const training_assistant& copy_assistant) {}
training_assistant::training_assistant(training_assistant&& move_assistant) {}




auto_encoder::auto_encoder() {}
auto_encoder::auto_encoder(const auto_encoder& copy_encoder) {}
auto_encoder::auto_encoder(auto_encoder&& move_encoder) {}
auto_encoder::auto_encoder(const char* filename) :
	_input(filename),
	_output(_input.network_values.rows(), _input.network_values.cols()),
	_hidden(nullptr),
	_policy_set_ind(nullptr),
	_policy(training_policy()),
	_trainer(training_assistant()),
	_status(nn::env::uninitialized),
	_need_to_load_data(false) {

}
auto_encoder::auto_encoder(std::istream& data_input_stream) {}
auto_encoder::auto_encoder(mat& data_input, int input_type) {}


//copies policy
void auto_encoder::set_policy(const training_policy& init_policy) {
	_policy = init_policy;
	_policy_set_ind = &_policy;
	_hidden = new hidden_layer(&_input, &_output, &_policy);
	_trainer.network = _hidden;

}
//will use default policy.
//if hidden dims <=0 will set hidden dims = to incoming dims
void auto_encoder::set_policy(int init_hidden_dims, int init_noise_method) {}
//construct using policy info. if hidden dims <= 0 will set hidden dims = to incoming dims
void auto_encoder::set_policy(const training_policy_info&, int init_hidden_dims, int init_noise_method) {}

void auto_encoder::initialize_environment() {}
