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
	//target(1, 1),
	noised_input(1, 1),
	targets_are_set(false),
	input_has_noise(false),
	is_complete(false) {
	
	std::cerr << "error: this hidden_layer constructor is currently not supported. please use hidden_layer(input_layer*, output_layer*, const training_policy*)\n";
	throw std::runtime_error("unsupported constructor call\n");
}

hidden_layer::hidden_layer(const hidden_layer& copy_layer) :
	base_hidden_layer(copy_layer),
	policy(nullptr),
	//target(copy_layer.target),
	noised_input(copy_layer.noised_input),
	targets_are_set(copy_layer.targets_are_set),
	input_has_noise(copy_layer.input_has_noise),
	is_complete(copy_layer.is_complete) {}


hidden_layer::hidden_layer(hidden_layer&& move_layer) :
	base_hidden_layer(move_layer),
	policy(nullptr),
	//target(std::move(move_layer.target)),
	noised_input(std::move(move_layer.noised_input)),
	targets_are_set(std::move(move_layer.targets_are_set)),
	input_has_noise(std::move(move_layer.input_has_noise)),
	is_complete(std::move(move_layer.is_complete)) {}

hidden_layer::hidden_layer(nn::input_layer* init_input_layer, nn::output_layer* init_output_layer, const training_policy* init_training_policy) :
	base_hidden_layer(init_input_layer, init_output_layer),
	policy(init_training_policy),
	//target(1, 1),
	noised_input(1, 1),
	targets_are_set(false),
	input_has_noise(false),
	is_complete(false) {
	try {
		if (input_nodes != nullptr && output_nodes != nullptr && policy != nullptr) {
			//can probably get rid of target. should store target in the output_nodes layer network_targets matrix
			//target = input_nodes->network_values;
			output_nodes->network_targets.resize(input_nodes->network_values.rows(), input_nodes->network_values.cols());
			output_nodes->network_targets = input_nodes->network_values;
			targets_are_set = true;
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
			input_has_noise = true;
			if (policy->hidden_layer_dims() > 0) {
				hidden_dims_are_set = true;
				incoming_links.reset(input_nodes->network_values.cols(), policy->hidden_layer_dims());
				incoming_links_are_set = true;
				outgoing_links.reset(policy->hidden_layer_dims(), output_nodes->network_values.cols());
				outgoing_links_are_set = true;
				resize(input_nodes->network_values.rows(), policy->hidden_layer_dims());
			} else {
				throw std::runtime_error("error: hidden_layer construction failed. layer and/or policy information is incomplete");
			}


		} else {
			throw std::runtime_error("error: hidden_layer construction failed. layer and/or policy information is incomplete");
		}
	} catch (std::exception& e) {
		std::cerr << "error: input_layer, output_layer, and the training policy must be complete. Will allow pointers to incomplete layers or policies at a later date.\n Please USE hidden_layer(input_layer*, output_layer*, const training_policy*)\n";
		throw e;
	}
}

void hidden_layer::initialize() {}
void hidden_layer::clear_delta() {}
void hidden_layer::randomize_weights() {}
void hidden_layer::feed_forward(int sample_size) {}
void hidden_layer::back_propogate(int sample_size) {}
void hidden_layer::add_noise() {}
void hidden_layer::self_diagnostic() {}

training_assistant::training_assistant() :
	policy(nullptr),
	network(nullptr) {}
training_assistant::training_assistant(const training_assistant& copy_assistant) {}
training_assistant::training_assistant(training_assistant&& move_assistant) {}
training_assistant::training_assistant(training_policy* init_policy, hidden_layer* init_network) {}
void training_assistant::train() {}
void training_assistant::prep_for_training() {}
void training_assistant::prep_for_batch() {}
void training_assistant::training_step() {}
void training_assistant::initialize_delta_accumulators() {}
void training_assistant::randomize_weights() {}


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
	_trainer.policy = &_policy;
	
	_trainer.network = _hidden;

}
//will use default policy.
//if hidden dims <=0 will set hidden dims = to incoming dims
void auto_encoder::set_policy(int init_hidden_dims, int init_noise_method) {}
//construct using policy info. if hidden dims <= 0 will set hidden dims = to incoming dims
void auto_encoder::set_policy(const training_policy_info&, int init_hidden_dims, int init_noise_method) {}

void auto_encoder::initialize_environment() {}
