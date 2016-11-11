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

			void clear_accumulators() {
				clear_accumulators(in_layer);
				clear_accumulators(out_layer);
				clear_accumulators(hidden_layer);
				clear_accumulators(in_links);
				clear_accumulators(out_links);
			}

			void initialize(int hdims, const char* filename) {

				//read input, store in encoder raw_data member
				nn::read_raw_data(filename, raw_data);

				//set encoder examples to raw data rows
				examples = raw_data.rows();
				//input dims = input cols - 1
				features = raw_data.cols() - 1;
				hdims = hdims;

				//resize storage
				resize(in_layer, examples, features);
				resize(out_layer, examples, features);
				resize(hidden_layer, examples, features);
				resize(in_links, features, hdims);
				resize(out_links, hdims, features);
				//input data = raw input data
				orig_data = raw_data.block(0, 1, examples, features);
				//target data = raw input data
				out_layer.target = orig_data;
				//seed standard random num gen
				srand(time(NULL));

				//randomize wieights
				randomize(in_links);
				randomize(out_links);

				srate = 1.0 / double(hdims);
				n_srate = 1.0 - srate;
				in_layer.name = "Input Layer";
				out_layer.name = "Output Layer";
				hidden_layer.name = "Hidden Layer";
				in_links.name = "Incoming Links";
				out_links.name = "Output Links";
			}

		};

		protected:
			void zero_out(ln& n) {
				n.network.setZero();
				n.output.setZero();
				n.oprime.setZero();
				n.error.setZero();
				n.target.setZero();
				n.sensitivity.setZero();
			}


			void zero_out(ll& l) {
				l.weights_delta.setZero();
				l.bias.setZero();
				l.weights_delta.setZero();
				l.bias_delta.setZero();
			}

			void resize(ln& n, int r, int d) {
				n.network.resize(r, d);
				n.output.resize(r, d);
				n.oprime.resize(r, d);
				n.error.resize(r, d);
				n.target.resize(r, d);
				n.sensitivity.resize(r, d);
				n.rows = r;
				n.dims = d;
				zero_out(n);
			}

			void resize(ll& l, int i, int o) {
				l.weights.resize(i, o);
				l.bias.resize(o);
				l.weights_delta.resize(i, o);
				l.bias_delta.resize(o);
				l.indims = i;
				l.outdims = o;
				zero_out(l);
			}

			void randomize(ll& l) {
				l.weights.setRandom();
				l.bias.setRandom();
			}

			void clear_accumulators(ln& n) {
				n.sensitivity.setZero();
			}

			void clear_accumulators(ll& l) {
				l.weights_delta.setZero();
				l.bias_delta.setZero();
			}




};


#endif