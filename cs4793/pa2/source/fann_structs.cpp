#include "fann_structs.h"

nn::input_layer::input_layer() {}

nn::input_layer::input_layer(const char* filename) {}

nn::input_layer::input_layer(std::istream& in) {}

nn::input_layer::input_layer(nn::mat& data, int input_type) {}

nn::output_layer::output_layer() {}

nn::output_layer::output_layer(mat& target_data) {}

nn::output_layer::output_layer(int data_rows, int output_dims) {}

nn::base_hidden_layer::base_hidden_layer() {}

nn::base_hidden_layer::base_hidden_layer(nn::input_layer* incoming_layer, nn::output_layer* output_layer) {}

nn::layer_link::layer_link() {}

nn::layer_link::layer_link(int) {}

nn::layer_link::layer_link(int, int) {}

nn::layer_link::layer_link(mat&) {}

nn::layer_link::layer_link(mat&, vec&) {}

void nn::layer_link::initialize() {}

nn::base_training_policy::base_training_policy(bool use_default) {}
