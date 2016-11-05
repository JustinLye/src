#include"net_structs.h"

ai::Node_Linkage::Node_Linkage(ai::mat_ptr weights_matrix, ai::vec_ptr bias_vector) : weights(weights_matrix), bias(bias_vector) {}


ai::Node_Linkage::Node_Linkage(const Node_Linkage& n) : weights(n.weights), bias(n.bias) {}

std::ostream& ai::operator<<(std::ostream& s, const ai::Node_Linkage& n) {
	s << "Weights:\n" << *n.weights << "\nBias:\n" << *n.bias << '\n';
	return s;
}

ai::Node_Layer::Node_Layer(ai::mat_ptr value_matrix) : network_value(value_matrix) {}

ai::Node_Layer::Node_Layer(const Node_Layer& n) : network_value(n.network_value) {}

std::ostream& ai::operator<<(std::ostream& s, const ai::Node_Layer& n) {
	s << "Node Values:\n" << *n.network_value << '\n';
	return s;
}

ai::Output_Node_Layer::Output_Node_Layer(ai::mat_ptr input_matrix, ai::mat_ptr activation_matrix, ai::mat_ptr derivative_matrix) :
	Node_Layer(input_matrix),
	network_activation(activation_matrix),
	network_activation_prime(derivative_matrix) {}

ai::Output_Node_Layer::Output_Node_Layer(const ai::Output_Node_Layer& o) :
	Node_Layer(o.network_value),
	network_activation(o.network_activation),
	network_activation_prime(o.network_activation_prime) {}

std::ostream& ai::operator<<(std::ostream& s, const ai::Output_Node_Layer& o) {
	s << "Network Values\n" << *o.network_value << "\nNetwork Activation\n" << *o.network_activation << "\nNetwork Activation Derivative\n" << *o.network_activation_prime << '\n';
	return s;
}

ai::Node_Linkage_Delta::Node_Linkage_Delta(ai::mat_ptr weights_matrix, ai::vec_ptr bias_vector, ai::mat_ptr weights_delta_matrix, ai::vec_ptr bias_delta_vector) :
	Node_Linkage(weights_matrix, bias_vector),
	weights_delta(weights_delta_matrix),
	bias_delta(bias_delta_vector) {}

ai::Node_Linkage_Delta::Node_Linkage_Delta(const Node_Linkage& linkage, mat_ptr weights_delta_matrix, vec_ptr bias_delta_vector) :
	Node_Linkage(linkage),
	weights_delta(weights_delta_matrix),
	bias_delta(bias_delta_vector) {}

ai::Node_Linkage_Delta::Node_Linkage_Delta(const Node_Linkage_Delta& linkage) :
	Node_Linkage(linkage.weights, linkage.bias),
	weights_delta(linkage.weights_delta),
	bias_delta(linkage.bias_delta) {}

ai::Network_Layer::Network_Layer(ai::Node_Linkage* node_linkage, ai::Node_Layer* input_layer_ptr, ai::Node_Layer* output_layer_ptr) :
	layer_links(node_linkage),
	input_layer(input_layer_ptr),
	output_layer(output_layer_ptr) {}

ai::Network_Layer::Network_Layer(const ai::Network_Layer& n) :
	layer_links(n.layer_links),
	input_layer(n.input_layer),
	output_layer(n.output_layer) {}

std::ostream& ai::operator<<(std::ostream& s, const ai::Network_Layer& n) {
	s << "Network Layer\n\n" << "Input Layer\n" << *n.input_layer << "\nLinks\n" << *n.layer_links << "\nOutput Layer\n" << *n.output_layer << '\n';
	return s;
}

ai::Layer_Info::Layer_Info(int rows, int in_dims, int out_dims, const ai::mat& layer_weights, const ai::vec& layer_bias, const ai::mat& layer_input, const ai::mat& layer_output) :
	input_rows(rows),
	input_dims(in_dims),
	output_dims(out_dims),
	weights(layer_weights),
	bias(layer_bias),
	input(layer_input),
	output(layer_output) {}