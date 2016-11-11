#if !defined(__NN_FANN_STRUCTS_HEADER__)
#define __NN_FANN_STRUCTS_HEADER__

#include"nn_util.h"

namespace nn {

	class input_layer {
	public:
		input_layer();
		input_layer(const input_layer&);
		input_layer(input_layer&&);
		input_layer(const char*);
		input_layer(std::istream&);
		input_layer(mat&, int = NN_PREPARED_INPUT_VALUES);
		mat network_values;
	};

	class output_layer {
	public:
		output_layer();
		output_layer(const output_layer&);
		output_layer(output_layer&&);
		output_layer(mat&);
		output_layer(int, int);

		mat network_values;
		mat network_activation;
		mat network_error;
		mat network_activation_prime;
		mat network_sensitivity;
		mat network_targets;
		void clear_delta();
	protected:
		void resize(int, int);
		
	};

	class layer_link {
	public:
		//constructors
		layer_link();
		layer_link(const layer_link&);
		layer_link(layer_link&&);
		layer_link(int);
		layer_link(int, int);
		layer_link(mat&);
		layer_link(mat&, row_vec&);

		//public members
		mat weights;
		row_vec bias;
		mat weights_delta;
		row_vec bias_delta;

		//getters
		inline virtual int incoming_dims() const { return weights.rows(); }
		inline virtual int outgoing_dims() const { return weights.cols(); }

		//added delta to weights and bias
		inline virtual void update() {
			weights += weights_delta;
			bias += bias_delta;
		}

		//public "bookkeeping" methods
		//clears weights and bias delta accumulator
		inline virtual void clear_delta() { weights_delta.setZero(); bias_delta.setZero(); }
		//reset weights and bias to random values, then scale weight and bias elements by (1.0 / (1.0 + sqrt(weights.rows()))
		inline virtual void randomize_weights() { weights.setRandom() *= (1.0 / (1.0 + sqrt(weights.rows()))); bias.setRandom() *= (1.0 / (1.0 + sqrt(weights.rows()))); }
		//clears weights and bias
		inline virtual void clear_info() { weights.setZero(), bias.setZero(); }
		//resize matrix and vector members to appropriate dimensions. If incoming/outgoing dims are unknown, size(1,1) & size(1) are used by default
		virtual void initialize();
		//a couple methods to reset/resize the data
		virtual void reset();
		virtual void reset(int, int);
		virtual void resize(int, int);
	};

	//pure virtual class. 
	class base_hidden_layer : public output_layer {
	public:
		base_hidden_layer();
		base_hidden_layer(const base_hidden_layer&);
		base_hidden_layer(base_hidden_layer&&);
		base_hidden_layer(mat&);
		base_hidden_layer(int, int);
		base_hidden_layer(input_layer*, output_layer*);

		input_layer* input_nodes;
		output_layer* output_nodes;
		layer_link incoming_links;
		layer_link outgoing_links;

		virtual void initialize() = 0;
		virtual void feed_forward() = 0;
		virtual void back_propogate() =0;
	};



};

#endif