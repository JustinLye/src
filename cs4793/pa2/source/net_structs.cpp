#include"net_structs.h"

nn::Node_Linkage::Node_Linkage(nn::mat_ptr weights_matrix, nn::vec_ptr bias_vector) : weights(weights_matrix), bias(bias_vector) {}


nn::Node_Linkage::Node_Linkage(const Node_Linkage& n) : weights(n.weights), bias(n.bias) {}

std::ostream& nn::operator<<(std::ostream& s, const nn::Node_Linkage& n) {
	s << "Weights:\n" << *n.weights << "\nBias:\n" << *n.bias << '\n';
	return s;
}

nn::Node_Layer::Node_Layer(nn::mat_ptr value_matrix) : network_value(value_matrix) {}

nn::Node_Layer::Node_Layer(const Node_Layer& n) : network_value(n.network_value) {}

std::ostream& nn::operator<<(std::ostream& s, const nn::Node_Layer& n) {
	s << "Node Values:\n" << *n.network_value << '\n';
	return s;
}

nn::Output_Node_Layer::Output_Node_Layer(nn::mat_ptr input_matrix, nn::mat_ptr activation_matrix, nn::mat_ptr derivative_matrix) :
	Node_Layer(input_matrix),
	network_activation(activation_matrix),
	network_activation_prime(derivative_matrix) {}

nn::Output_Node_Layer::Output_Node_Layer(const nn::Output_Node_Layer& o) :
	Node_Layer(o.network_value),
	network_activation(o.network_activation),
	network_activation_prime(o.network_activation_prime) {}

std::ostream& nn::operator<<(std::ostream& s, const nn::Output_Node_Layer& o) {
	s << "Network Values\n" << *o.network_value << "\nNetwork Activation\n" << *o.network_activation << "\nNetwork Activation Derivative\n" << *o.network_activation_prime << '\n';
	return s;
}

nn::Node_Linkage_Delta::Node_Linkage_Delta(nn::mat_ptr weights_matrix, nn::vec_ptr bias_vector, nn::mat_ptr weights_delta_matrix, nn::vec_ptr bias_delta_vector) :
	Node_Linkage(weights_matrix, bias_vector),
	weights_delta(weights_delta_matrix),
	bias_delta(bias_delta_vector) {}

nn::Node_Linkage_Delta::Node_Linkage_Delta(const Node_Linkage& linkage, mat_ptr weights_delta_matrix, vec_ptr bias_delta_vector) :
	Node_Linkage(linkage),
	weights_delta(weights_delta_matrix),
	bias_delta(bias_delta_vector) {}

nn::Node_Linkage_Delta::Node_Linkage_Delta(const Node_Linkage_Delta& linkage) :
	Node_Linkage(linkage.weights, linkage.bias),
	weights_delta(linkage.weights_delta),
	bias_delta(linkage.bias_delta) {}

nn::Network_Layer::Network_Layer(nn::Node_Linkage* node_linkage, nn::Node_Layer* input_layer_ptr, nn::Node_Layer* output_layer_ptr) :
	layer_links(node_linkage),
	input_layer(input_layer_ptr),
	output_layer(output_layer_ptr) {}

nn::Network_Layer::Network_Layer(const nn::Network_Layer& n) :
	layer_links(n.layer_links),
	input_layer(n.input_layer),
	output_layer(n.output_layer) {}

std::ostream& nn::operator<<(std::ostream& s, const nn::Network_Layer& n) {
	s << "Network Layer\n\n" << "Input Layer\n" << *n.input_layer << "\nLinks\n" << *n.layer_links << "\nOutput Layer\n" << *n.output_layer << '\n';
	return s;
}

nn::Layer_Info::Layer_Info(const nn::Layer_Info& l) :
	input_rows(l.input_rows),
	input_dims(l.input_dims),
	output_dims(l.output_dims),
	weights(l.weights),
	bias(l.bias),
	input(l.input),
	output(l.output) {}

nn::Layer_Info::Layer_Info(int rows, int in_dims, int out_dims, const nn::mat& layer_weights, const nn::vec& layer_bias, const nn::mat& layer_input, const nn::mat& layer_output) :
	input_rows(rows),
	input_dims(in_dims),
	output_dims(out_dims),
	weights(layer_weights),
	bias(layer_bias),
	input(layer_input),
	output(layer_output) {}

nn::Training_Info::Training_Info(const Layer_Info& layer_info, int tar_dims, double true_target, double false_target, const nn::mat& layer_targets, const nn::mat& layer_errors) :
	Layer_Info(layer_info),
	target_dims(tar_dims),
	in_target(true_target),
	out_target(false_target),
	targets(layer_targets),
	errors(layer_errors) {}

nn::Training_Info::Training_Info(
	int rows, int in_dims, int out_dims,
	const nn::mat& layer_weights, const nn::vec& layer_bias, const nn::mat& layer_input,
	const nn::mat& layer_output, int tar_dims, double true_target,
	double false_target, const nn::mat& layer_targets, const nn::mat& layer_errors) :
	Layer_Info(rows, in_dims, out_dims, layer_weights, layer_bias, layer_input, layer_output),
	target_dims(tar_dims),
	in_target(true_target),
	out_target(false_target),
	targets(layer_targets),
	errors(layer_errors) {}