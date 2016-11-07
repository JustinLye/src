#include "nn_structs.h"


//input layer defs
//default constructor network_values matrix initialized to size(1,1)
nn::input_layer::input_layer() : network_values(1,1) {}

nn::input_layer::input_layer(const input_layer& copy_layer) {
	network_values.resize(copy_layer.network_values.rows(), copy_layer.network_values.cols());
	network_values = copy_layer.network_values;
}
nn::input_layer::input_layer(input_layer&& move_layer) : network_values(std::move(move_layer.network_values)) {}
nn::input_layer::input_layer(const char* filename) {
	mat raw_data;
	if (!nn::read_raw_data(filename, raw_data)) {
		std::cerr << "error: input layer could not be constructed because of failure to read raw data from file: " << filename << std::endl;
		throw std::runtime_error("error: could not read file");
	}
	network_values.resize(raw_data.rows(), raw_data.cols()-1);
	network_values.block(0,0, network_values.rows(), network_values.cols()) = raw_data.block(0,1,network_values.rows(), network_values.cols());
}
nn::input_layer::input_layer(std::istream& in) {
	if (!nn::read_raw_data(in, network_values)) {
		std::cerr << "error: input layer could not be constructed because of failure to read raw data from input stream" << std::endl;
		throw std::runtime_error("error: could not read from input stream");
	}
}

//if input type is raw data (i.e. all input from a given input stream) then it is assumed to input values will begin in column 1
nn::input_layer::input_layer(nn::mat& data, int input_type) : network_values(data) {
	switch (input_type) {
	case NN_RAW_INPUT_VALUES:
		network_values.resize(data.rows(), data.cols()-1);
		network_values.block(0,0,network_values.rows(), network_values.cols()) = data.block(0,1,network_values.rows(), network_values.cols());
		break;
	case NN_PREPARED_INPUT_VALUES:
	default:
		break;
	}
}
//--input layer defs


//output layer defs
//default constructor all member matrices initialized to size(1,1)
nn::output_layer::output_layer() :
	network_values(1, 1),
	network_activation(1, 1),
	network_error(1, 1),
	network_activation_prime(1, 1),
	network_sensitivity(1, 1),
	network_targets(1, 1) {}

nn::output_layer::output_layer(const output_layer& copy_layer) :
	network_values(copy_layer.network_values),
	network_activation(copy_layer.network_activation),
	network_error(copy_layer.network_error),
	network_activation_prime(copy_layer.network_activation_prime),
	network_sensitivity(copy_layer.network_sensitivity),
	network_targets(copy_layer.network_targets) {}

nn::output_layer::output_layer(output_layer&& move_layer) :
	network_values(std::move(move_layer.network_values)),
	network_activation(std::move(move_layer.network_activation)),
	network_error(std::move(move_layer.network_error)),
	network_activation_prime(std::move(move_layer.network_activation_prime)),
	network_sensitivity(std::move(move_layer.network_sensitivity)),
	network_targets(std::move(move_layer.network_targets)) {}

nn::output_layer::output_layer(mat& target_data) :
	network_values(target_data.rows(), target_data.cols()),
	network_activation(target_data.rows(), target_data.cols()),
	network_error(target_data.rows(), target_data.cols()),
	network_activation_prime(target_data.rows(), target_data.cols()),
	network_sensitivity(target_data.rows(), target_data.cols()),
	network_targets(target_data.rows(), target_data.cols()) {}

nn::output_layer::output_layer(int data_rows, int output_dims) :
	network_values(data_rows, output_dims),
	network_activation(data_rows, output_dims),
	network_error(data_rows, output_dims),
	network_activation_prime(data_rows, output_dims),
	network_sensitivity(data_rows, output_dims),
	network_targets(data_rows, output_dims) {}

void nn::output_layer::clear_delta() {
	network_error.setZero();
	network_sensitivity.setZero();
}


void nn::output_layer::resize(int data_rows, int output_dims) {
	network_values.resize(data_rows, output_dims);
	network_activation.resize(data_rows, output_dims);
	network_error.resize(data_rows, output_dims);
	network_activation_prime.resize(data_rows, output_dims);
	network_sensitivity.resize(data_rows, output_dims);
	network_targets.resize(data_rows, output_dims);
}

//end output defs

//layer_link defs

//default constructor weights and bias initialized to size (1,1) and (1)
nn::layer_link::layer_link() :
	weights(1, 1),
	bias(1),
	weights_delta(1, 1),
	bias_delta(1) {}

nn::layer_link::layer_link(const layer_link& copy_link) :
	weights(copy_link.weights),
	bias(copy_link.bias),
	weights_delta(copy_link.weights_delta),
	bias_delta(copy_link.bias_delta) {}

nn::layer_link::layer_link(layer_link&& move_link) :
	weights(std::move(move_link.weights)),
	bias(std::move(move_link.bias)),
	weights_delta(std::move(move_link.weights_delta)),
	bias_delta(std::move(move_link.bias_delta)) {}

//constructor assumes incoming dimensions are equal to outgoing dimensions
nn::layer_link::layer_link(int init_dimensions) :
	weights(init_dimensions, init_dimensions),
	bias(init_dimensions),
	weights_delta(init_dimensions, init_dimensions),
	bias_delta(init_dimensions) {}

nn::layer_link::layer_link(int init_incoming_dims, int init_outgoing_dims) :
	weights(init_incoming_dims, init_outgoing_dims),
	bias(init_outgoing_dims),
	weights_delta(init_incoming_dims, init_outgoing_dims),
	bias_delta(init_outgoing_dims) {}


nn::layer_link::layer_link(mat& init_weights) :
	weights(init_weights),
	bias(init_weights.cols()),
	weights_delta(init_weights.rows(), init_weights.cols()),
	bias_delta(init_weights.cols()) {}

nn::layer_link::layer_link(mat& init_weights, vec& init_bias) :
	weights(init_weights),
	bias(init_bias),
	weights_delta(init_weights.rows(), init_weights.cols()),
	bias_delta(init_weights.cols()) {
	assert(init_bias.size() == init_weights.cols());
}

void nn::layer_link::initialize() {
	clear_delta();
	randomize_weights();
}

void nn::layer_link::reset() {
	clear_delta();
	clear_info();
}

void nn::layer_link::reset(int init_incoming_dims, int init_outgoing_dims) {
	reset();
	resize(init_incoming_dims, init_outgoing_dims);
}

void nn::layer_link::resize(int init_incoming_dims, int init_outgoing_dims) {
	weights.resize(init_incoming_dims, init_outgoing_dims);
	bias.resize(init_outgoing_dims);
	weights_delta.resize(init_incoming_dims, init_outgoing_dims);
	bias_delta.resize(init_outgoing_dims);
}

//end layer_link defs

//base_hidden_layer defs

nn::base_hidden_layer::base_hidden_layer() :
	output_layer(),
	input_nodes(nullptr),
	output_nodes(nullptr) {}

nn::base_hidden_layer::base_hidden_layer(const base_hidden_layer& copy_layer) :
	output_layer(copy_layer),
	input_nodes(copy_layer.input_nodes),
	output_nodes(copy_layer.output_nodes),
	incoming_links(copy_layer.incoming_links),
	outgoing_links(copy_layer.outgoing_links) {}

nn::base_hidden_layer::base_hidden_layer(base_hidden_layer&& move_layer) :
	output_layer(std::move(move_layer)),
	input_nodes(std::move(move_layer.input_nodes)),
	output_nodes(std::move(move_layer.output_nodes)),
	incoming_links(std::move(move_layer.incoming_links)),
	outgoing_links(std::move(move_layer.outgoing_links)) {}

nn::base_hidden_layer::base_hidden_layer(mat& target_data) :
	output_layer(target_data),
	input_nodes(nullptr),
	output_nodes(nullptr) {}

nn::base_hidden_layer::base_hidden_layer(int data_rows, int output_dims) :
	output_layer(data_rows, output_dims),
	input_nodes(nullptr),
	output_nodes(nullptr) {}

nn::base_hidden_layer::base_hidden_layer(nn::input_layer* incoming_layer, nn::output_layer* outgoing_layer) :
	output_layer(),
	input_nodes(incoming_layer),
	output_nodes(outgoing_layer) {}

//end base_hidden_layer_defs