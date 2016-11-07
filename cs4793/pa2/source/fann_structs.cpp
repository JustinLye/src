#include "fann_structs.h"

nn::input_layer::input_layer() {}

nn::input_layer::input_layer(const input_layer& copy_layer) {}

nn::input_layer::input_layer(input_layer&& move_layer) {}

nn::input_layer::input_layer(const char* filename) {}

nn::input_layer::input_layer(std::istream& in) {}

nn::input_layer::input_layer(nn::mat& data, int input_type) {}



nn::output_layer::output_layer() {}

nn::output_layer::output_layer(const output_layer& copy_layer) {}

nn::output_layer::output_layer(output_layer&& move_layer) {}

nn::output_layer::output_layer(mat& target_data) {}

nn::output_layer::output_layer(int data_rows, int output_dims) {}



nn::layer_link::layer_link() {}

nn::layer_link::layer_link(const layer_link& copy_link) {}

nn::layer_link::layer_link(layer_link&& move_link) {}

nn::layer_link::layer_link(int init_dimensions) {}

nn::layer_link::layer_link(int init_incoming_dims, int init_outgoing_dims) {}

nn::layer_link::layer_link(mat& init_weights) {}

nn::layer_link::layer_link(mat& init_weights, vec& init_bias) {}

void nn::layer_link::initialize() {}

void nn::layer_link::reset() {}

void nn::layer_link::reset(int init_incoming_dims, int init_outgoing_dims) {}

nn::base_hidden_layer::base_hidden_layer() {}

nn::base_hidden_layer::base_hidden_layer(const base_hidden_layer& copy_layer) {}

nn::base_hidden_layer::base_hidden_layer(base_hidden_layer&& move_layer) {}

nn::base_hidden_layer::base_hidden_layer(mat& target_data) {}

nn::base_hidden_layer::base_hidden_layer(int data_rows, int output_dims) {}

nn::base_hidden_layer::base_hidden_layer(nn::input_layer* incoming_layer, nn::output_layer* output_layer) {}

