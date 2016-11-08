#include "nn_hidden_layer.h"

using namespace nn::encoder;

encoding_layer::encoding_layer() :
	base_hidden_layer(),
	policy(nullptr),
	noised_input(1, 1),
	has_targets_flag(false),
	has_noise_flag(false),
	dim_links_flag(false) {

	std::cerr << "error: this hidden_layer constructor is currently not supported. please use hidden_layer(input_layer*, output_layer*, const training_policy*)\n";
	throw std::runtime_error("unsupported constructor call\n");
}

encoding_layer::encoding_layer(const encoding_layer& copy_layer) :
	base_hidden_layer(copy_layer),
	policy(nullptr),
	noised_input(copy_layer.noised_input),
	has_targets_flag(copy_layer.has_targets_flag),
	has_noise_flag(copy_layer.has_noise_flag),
	dim_links_flag(copy_layer.dim_links_flag) {}


encoding_layer::encoding_layer(encoding_layer&& move_layer) :
	base_hidden_layer(move_layer),
	policy(nullptr),
	noised_input(std::move(move_layer.noised_input)),
	has_targets_flag(std::move(move_layer.has_targets_flag)),
	has_noise_flag(std::move(move_layer.has_noise_flag)),
	dim_links_flag(std::move(move_layer.dim_links_flag)) {}

encoding_layer::encoding_layer(nn::input_layer* init_input_layer, nn::output_layer* init_output_layer, const training_policy* init_training_policy) :
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

void encoding_layer::initialize() {
	set_target();
	add_noise();
	dim_links();
	if (!can_train()) {
		print_layer_status_warnings("some actions were not completed during hidden_layer initialization");
	}
}

void encoding_layer::clear_delta() {
	incoming_links.clear_delta();
	outgoing_links.clear_delta();
	clear_delta();
	output_nodes->clear_delta();

}
void encoding_layer::randomize_weights() {
	incoming_links.randomize_weights();
	outgoing_links.randomize_weights();
}

//Sets the sample size min(input rows - rows_offset, batchsize). Performs feed forward, set error, backpropogate, and update links. Assumes any booking has been done. 
void encoding_layer::training_step(int rows_offset) {
	set_sample_size(rows_offset);
	feed_forward(rows_offset);
	set_errors(rows_offset);
	back_propogate(rows_offset);
	update_links();
}

//wanted to use topRows(sampleSize) as the example did, but poor planning forced me to use the block method or reorganize the my classes, which I have already done multiple times.

void encoding_layer::feed_forward(int rows_offset) {

	//forward to hidden layer then apply logistic sigmoid activation function to hidden layer
	network_activation.block(rows_offset, 0, sample_size, network_activation.cols()) =
		1.0 / (Eigen::exp(((training_inputs.block(rows_offset, 0, sample_size, training_inputs.cols()) * incoming_links.weights).rowwise() + incoming_links.bias).array() * -1.0) + 1.0);

	//store first derivative
	network_activation_prime.block(rows_offset, 0, sample_size, network_activation_prime.cols()) =
		network_activation_prime.block(rows_offset, 0, sample_size, network_activation_prime.cols()).array() * (1.0 - network_activation_prime.block(rows_offset, 0, sample_size, network_activation_prime.cols()).array());

	//forward to output layer then apply logistic sigmoid activation function to output layer
	output_nodes->network_activation.block(rows_offset, 0, sample_size, output_nodes->network_activation.cols()) =
		1.0 / (Eigen::exp(((network_activation.block(rows_offset, 0, sample_size, network_activation.cols()) * outgoing_links.weights).rowwise() + outgoing_links.bias).array() * -1.0) + 1.0);

	//store first derivative
	output_nodes->network_activation_prime.block(rows_offset, 0, sample_size, output_nodes->network_activation_prime.cols()) =
		output_nodes->network_activation_prime.block(rows_offset, 0, sample_size, output_nodes->network_activation_prime.cols()).array() * (1.0 - output_nodes->network_activation_prime.block(rows_offset, 0, sample_size, output_nodes->network_activation_prime.cols()).array());

}

void encoding_layer::set_errors(int rows_offset) {

	//output layer errors
	output_nodes->network_error.block(rows_offset, 0, sample_size, output_nodes->network_error.cols()) =
		training_targets.block(rows_offset, 0, sample_size, training_targets.cols()) - output_nodes->network_activation.block(rows_offset, 0, sample_size, output_nodes->network_activation.cols());

	//todo: apply sparsity error

	// weight regularization (or decay) : d/dw -(1/2)beta*W_ij^2 --> -beta * W_ij
	if (policy->use_weight_reg()) {
		incoming_links.weights_delta = incoming_links.weights * (-1.0 * policy->weight_reg_scaling());
		outgoing_links.weights_delta = outgoing_links.weights * (-1.0 * policy->weight_reg_scaling());
	}
}

void encoding_layer::back_propogate(int rows_offset) {

	//output layer
	output_nodes->network_sensitivity.block(rows_offset, 0, sample_size, output_nodes->network_sensitivity.cols()) =
		output_nodes->network_error.block(rows_offset, 0, sample_size, output_nodes->network_error.cols()).array() * output_nodes->network_activation_prime.block(rows_offset, 0, sample_size, output_nodes->network_activation_prime.cols()).array();
	outgoing_links.weights_delta +=
		policy->lrate * network_activation.block(rows_offset, 0, sample_size, network_activation.cols()).transpose() * output_nodes->network_sensitivity.block(rows_offset, 0, sample_size, output_nodes->network_sensitivity.cols()) / sample_size;
	outgoing_links.bias_delta +=
		policy->lrate * output_nodes->network_sensitivity.block(rows_offset, 0, sample_size, output_nodes->network_sensitivity.cols()).colwise().sum() / sample_size;

	//todo: add sparsity error term to hidden layer sensitivity

	//add the propogation to the incoming links delta's
	network_sensitivity.block(rows_offset, 0, sample_size, network_sensitivity.cols()) =
		(output_nodes->network_sensitivity.block(rows_offset, 0, sample_size, output_nodes->network_sensitivity.cols()) * outgoing_links.weights.transpose()).array() * network_sensitivity.block(rows_offset, 0, sample_size, network_sensitivity.cols()).array();
	incoming_links.weights_delta +=
		policy->lrate * training_inputs.block(rows_offset, 0, sample_size, training_inputs.cols()).transpose() * network_sensitivity.block(rows_offset, 0, sample_size, network_sensitivity.cols()) / sample_size;
	incoming_links.bias_delta +=
		policy->lrate * network_sensitivity.block(rows_offset, 0, sample_size, network_sensitivity.cols()).colwise().sum() / sample_size;
}


void encoding_layer::add_noise() {
	has_noise_flag = false;
	if (is_complete()) {
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
void encoding_layer::set_target() {
	has_targets_flag = false;
	if (is_complete()) {
		training_targets.resize(input_nodes->network_values.rows(), input_nodes->network_values.cols());
		training_targets = input_nodes->network_values;
		has_targets_flag = true;
	}
}

void encoding_layer::dim_links() {
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

void encoding_layer::print_layer_status_warnings(const char* additional_info) const {
	if (additional_info != nullptr)
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

void encoding_layer::print_layer_status_errors(const char* additional_info) const {
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