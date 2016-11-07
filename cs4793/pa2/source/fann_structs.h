#if !defined(__NN_FANN_STRUCTS_HEADER__)
#define __NN_FANN_STRUCTS_HEADER__

#include"fann_util.h"

namespace nn {

#define NN_PREPARED_INPUT_VALUES 0x0000
#define NN_RAW_INPUT_VALUES 0x0001

	class input_layer {
	public:
		input_layer();
		input_layer(const char*);
		input_layer(std::istream&);
		input_layer(mat&, int = NN_PREPARED_INPUT_VALUES);
		mat network_values;
	};

	class output_layer {
	public:
		output_layer();
		output_layer(mat&);
		output_layer(int, int);

		mat network_values;
		mat network_activation;
		mat network_error;
		mat network_activation_prime;
		mat network_sensitivity;
		mat network_targets;
	};

	class layer_link {
	public:
		layer_link();
		layer_link(int);
		layer_link(int, int);
		layer_link(mat&);
		layer_link(mat&, vec&);

		int incoming_dims;
		int outgoing_dims;

		mat weights;
		vec bias;
		mat weights_delta;
		vec bias_delta;		

		virtual void initialize();
	};

	//pure virtual class. 
	class base_hidden_layer : public output_layer {
	public:
		base_hidden_layer();
		base_hidden_layer(input_layer*, output_layer*);

		input_layer* input_nodes;
		output_layer* output_nodes;
		layer_link incoming_links;
		layer_link outgoing_links;

		virtual void initialize_layer() = 0;
		virtual void feed_forward() = 0;
		virtual void back_propogate() =0;
	};



};

#endif