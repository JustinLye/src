#include<iostream>
#include<random>
#include<time.h>

#if !defined(__NN_ENCODER_HEADER__)
#define __NN_ENCODER_HEADER__

#include"nn_util.h"
#include"noise.h"

namespace nn {
	struct layer_nodes {
		mat network;
		mat output;
		mat oprime;
		mat error;
		mat target;
		mat sensitivity;
		int rows;
		int dims;
		const char* name;
		friend std::ostream& operator<<(std::ostream& s, const layer_nodes& n) {
			s << n.name << std::endl << std::endl <<
				n.name << " Network: " << std::endl << n.network << std::endl << std::endl <<
				n.name << " Output: " << std::endl << n.output << std::endl << std::endl <<
				n.name << " Prime: " << std::endl << n.oprime << std::endl << std::endl <<
				n.name << " Target: " << std::endl << n.target << std::endl << std::endl <<
				n.name << " Delta: " << std::endl << n.sensitivity << std::endl << std::endl;
		}
	};

	struct layer_links {
		mat weights;
		row_vec bias;
		mat weights_delta;
		row_vec bias_delta;
		int indims;
		int outdims;
		const char* name;
		friend std::ostream& operator<<(std::ostream& s, const layer_links& l) {
			s << l.name << std::endl << std::endl <<
				l.name << " Weights: " << std::endl << l.weights << std::endl << std::endl <<
				l.name << " Bias: " << std::endl << l.bias << std::endl << std::endl <<
				l.name << " Weights Delta: " << std::endl << l.weights_delta << std::endl << std::endl <<
				l.name << " Bias Delta: " << std::endl << l.bias_delta << std::endl << std::endl;
		}
	};
	typedef layer_nodes ln;
	typedef layer_links ll;

	class encoder {
	public:
		ln in_layer;
		ln out_layer;
		ln hidden_layer;
		ll in_links;
		ll out_links;
		mat raw_data;
		mat orig_data;
		noise noise_maker;
		int examples;
		int features;
		int hdims;
		double srate;
		double n_srate;
		double lrate;
		double init_lrate;
		double batchsize;
		int max_epoch;
		int epoch;
		double beta;
		double weight_beta;
		std::vector<int> sample_indices;

		void clear_accumulators();
		void initialize(int hiddendims, const char* filename);
		void feed_forward();
		void set_error();
		void set_penalty();
		void backpropogate();
		void update_weights();
		void train_step();
		void update_lrate();
		friend std::ostream& operator<<(std::ostream& s, const encoder& e) {
			s << e.in_layer << e.in_links << e.hidden_layer << e.out_links << e.out_layer;
		}
	protected:

		void zero_out(ln& n);
		void zero_out(ll& l);
		void resize(ln& n, int r, int d);
		void resize(ll& l, int i, int o);
		void randomize(ll& l);
		void clear_accumulators(ln& n);
		void clear_accumulators(ll& l);
		void sigmoid(ln& n);
		void get_prime(ln& n);
		void feed(ln& input, ll& links, ln& output);
		void noise_input();
	};



};


#endif