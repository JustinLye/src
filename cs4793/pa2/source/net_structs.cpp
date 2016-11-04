#include"net_structs.h"

ai::Node_Linkage::Node_Linkage(ai::mat_ptr weights_matrix, ai::vec_ptr bias_vector) : weights(weights_matrix), bias(bias_vector) {}


ai::Node_Linkage::Node_Linkage(const Node_Linkage& n) : weights(n.weights), bias(n.bias) {}

std::ostream& ai::operator<<(std::ostream& s, const ai::Node_Linkage& n) {
	s << "Weights:\n" << *n.weights << "\nBias:\n" << *n.bias << '\n';
	return s;
}

ai::Node_Layer::Node_Layer(ai::mat_ptr value_matrix) : node_values(value_matrix) {}

ai::Node_Layer::Node_Layer(const Node_Layer& n) : node_values(n.node_values) {}

std::ostream& ai::operator<<(std::ostream& s, const ai::Node_Layer& n) {
	s << "Node Values:\n" << *n.node_values << '\n';
	return s;
}

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