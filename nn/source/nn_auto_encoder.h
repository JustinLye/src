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
	};

	struct layer_links {
		mat weights;
		row_vec bias;
		mat weights_delta;
		row_vec bias_delta;
		int indims;
		int outdims;
		const char* name;
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

		void clear_accumulators();
		void initialize(int hdims, const char* filename);

protected:
	void zero_out(ln& n);
	void zero_out(ll& l);
	void resize(ln& n, int r, int d);
	void resize(ll& l, int i, int o);
	void randomize(ll& l);
	void clear_accumulators(ln& n);
	void clear_accumulators(ll& l);




};


#endif