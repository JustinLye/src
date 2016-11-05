#include "fann_structs.h"


/*Loads input and target data matrices from given input stream.
Usage: load_data(standard input stream, column offset, true class target, wrong class target)
Returns true if data was successfully load, false otherwise*/
bool nn::input_stream::load_data(std::istream& in, int col_offset, double correct_target, double incorrect_target) {
	//Update members if optional arguments are provided
	//todo: save restore changes to members if load data fails
	//if(col_offset > 0) _column_offset = col_offset;
	//if(correct_target > 0) _true_target = correct_target;
	//if(incorrect_target > 0) _wrong_target = incorrect_target;
	if (!in.good()) {
		std::cerr << "error: failed to load data\n\tinput stream must be in good state\n";
	} else {
		return CS4793::loadDataFile(in, network_input, network_target, column_offset, true_class_target, wrong_class_target);
	}
}

nn::Net_Link::Net_Link() :
	input_dims(1),
	output_dims(1),
	weights(input_dims, output_dims),
	bias(output_dims),
	weights_delta(input_dims, output_dims),
	bias_delta(output_dims) {}

nn::Net_Link::Net_Link(int input_dimensions, int output_dimensions) :
	input_dims(input_dimensions),
	output_dims(output_dimensions),
	weights(input_dims, output_dims),
	bias(output_dims),
	weights_delta(input_dims, output_dims),
	bias_delta(output_dims) {}

void nn::Net_Link::redimensionalize(int input_dimensions, int output_dimensions) {
	//check if arguments are different then current dimensions
	if(same_dimensions(input_dimensions,output_dimensions))
		return;
	//output dims are equal to input dims by default
	if (output_dimensions < 0)
		output_dimensions = input_dimensions;

	//update members
	input_dims = input_dimensions;
	output_dims = output_dimensions;
	weights.resize(input_dims, output_dims);
	bias.resize(output_dims);
	weights_delta.resize(input_dims, output_dims);
	bias_delta.resize(output_dims);
	weights.fill(0.0);
	bias.fill(0.0);
	weights_delta.fill(0.0);
	bias_delta.fill(0.0);
}

nn::Layer_Data::Layer_Data() :
	input_stream(),
	Net_Link(),
	network_output(1, 1),
	network_activation(1, 1),
	activation_derivative(1, 1),
	network_error(1, 1) {}

nn::Layer_Data::Layer_Data(const char* filename) :
	input_stream(),
	Net_Link(),
	network_output(1, 1),
	network_activation(1, 1),
	activation_derivative(1, 1),
	network_error(1, 1) {
	std::ifstream in;
	in.open(filename);
	if (!load_data(in)) {
		std::cerr << "error: could not construct layer data\n\terror caused by failure in the load data routine\n";
	} else {
		redimensionalize(network_input.cols());
	}
	in.close();
}


nn::Layer_Data::Layer_Data(std::istream& in) :
	input_stream(),
	Net_Link(),
	network_output(1, 1),
	network_activation(1, 1),
	activation_derivative(1, 1),
	network_error(1, 1) {
	if (!load_data(in)) {
		std::cerr << "error: could not construct layer data\n\terror caused by failure in the load data routine\n";
	} else {
		redimensionalize(network_input.cols());

	}
}

void nn::Layer_Data::redimensionalize(int input_dimensions, int output_dimensions) {
	if(same_dimensions(input_dimensions, output_dimensions))
		return;
	Net_Link::redimensionalize(input_dimensions, output_dimensions);

	int rows = network_input.rows();
	//update members
	network_output.resize(rows, output_dims);
	network_activation.resize(rows, output_dims);
	activation_derivative.resize(rows, output_dims);
	network_error.resize(rows, output_dims);
	network_output.fill(0.0);
	network_activation.fill(0.0);
	activation_derivative.fill(0.0);
	network_error.fill(0.0);
}

void nn::Layer_Data::print(std::ostream& s) const {
	s << "-------------------------------------" << std::endl;
	s << "Layer Data" << std::endl << std::endl;
	s << "Column Offset:\t" << column_offset << std::endl;
	s << "True Target:\t" << true_class_target << std::endl;
	s << "Wrong Target:\t" << wrong_class_target << std::endl;
	s << "Input Rows:\t" << network_input.rows() << std::endl;
	s << "Input Dims:\t" << input_dims << std::endl;
	s << "Output Dims:\t" << output_dims << std::endl;
	s << "Network Input:\n" << network_input << std::endl;
	s << "Network Target:\n" << network_target << std::endl;
	s << "Weights:\n" << weights << std::endl;
	s << "Bias:\n" << bias << std::endl;
	s << "Weights Delta:\n" << weights_delta << std::endl;
	s << "Bias Delta:\n" << bias_delta << std::endl;
	s << "Network Output:\n" << network_output << std::endl;
	s << "Network Activation:\n" << network_activation << std::endl;
	s << "Activation Derivative:\n" << activation_derivative << std::endl;
	s << "Network Error:\n" << network_error << std::endl;
	s << "-------------------------------------" << std::endl;
}