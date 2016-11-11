#include"nn_auto_encoder.h"

using namespace nn;

void encoder::initialize(int hiddendims, const char* filename) {

	//read input, store in encoder raw_data member
	nn::read_raw_data(filename, raw_data);

	//set encoder examples to raw data rows
	examples = raw_data.rows();
	//input dims = input cols - 1
	features = raw_data.cols() - 1;
	hdims = hiddendims;

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
	in_layer.output = orig_data;
	//seed standard random num gen
	srand(time(NULL));

	//randomize wieights
	randomize(in_links);
	randomize(out_links);

	srate = 1.0 / double(hdims);
	n_srate = 1.0 - srate;
	weight_beta = 0.1 / (features * hiddendims * 2);

	in_layer.name = "Input Layer";
	out_layer.name = "Output Layer";
	hidden_layer.name = "Hidden Layer";
	in_links.name = "Incoming Links";
	out_links.name = "Output Links";
}

void encoder::feed_forward() {
	//feed input layer to hidden layer
	feed(in_layer, in_links, hidden_layer);
	//feed hidden layer to output
	feed(hidden_layer, out_links, out_layer);
}

void encoder::sigmoid(ln& n) {
	n.output = 1.0 / (Eigen::exp(-1.0 * n.network.array()) + 1.0);
}

void encoder::feed(ln& input, ll& links, ln& output) {
	output.network = (input.output * links.weights).rowwise() + links.bias;
	sigmoid(output);
	get_prime(output);
}

void encoder::get_prime(ln& n) {
	n.oprime = n.output.array() * (1.0 - n.output.array());
}

void encoder::set_error() {
	out_layer.error = out_layer.target - out_layer.output;
	set_penalty();
	in_links.weights_delta = in_links.weights * (-1.0 * weight_beta);
	out_links.weights_delta = out_links.weights * (-1.0 * weight_beta);
}

void encoder::set_penalty() {
	//stores the average activation of each node in the hidden layer as a row vector
	row_vec hmean = hidden_layer.output.colwise().mean();
	//stores the derivative of kl-div for each node as a row vector
	row_vec dkldiv = -srate / hmean.array() + (n_srate / (1.0 - hmean.array()));
	//copies the kl-div into hidden layer error 
	for (int i = 0; i < hidden_layer.rows; i++) {
		hidden_layer.error.row(i) = beta * dkldiv;
	}
}

void encoder::backpropogate() {
	//scal error by sensitivity
	out_layer.sensitivity = out_layer.error.array() * out_layer.oprime.array();
	out_links.weights_delta += lrate * hidden_layer.output.transpose() * out_layer.sensitivity;
	out_links.bias_delta += lrate * out_layer.sensitivity.colwise().sum();

	hidden_layer.sensitivity =
			(hidden_layer.error.array() + (out_layer.sensitivity * out_links.weights.transpose()).array()) * hidden_layer.oprime.array();
	in_links.weights_delta += lrate * in_layer.output.transpose() * hidden_layer.sensitivity;
	in_links.bias_delta += lrate * in_layer.sensitivity.colwise().sum();

}

void encoder::update_weights() {
	in_links.weights += in_links.weights_delta;
	in_links.bias += in_links.bias_delta;
	out_links.weights += out_links.weights_delta;
	out_links.bias += out_links.bias_delta;
}

void encoder::update_lrate() {
	lrate = init_lrate / (1.0 + sqrt(epoch));
}

void encoder::train_step() {
	clear_accumulators();
	noise_input();
	feed_forward();
	set_error();
	backpropogate();
	update_weights();
}

void encoder::noise_input() {
	noise_maker.AddGaussianNoise(orig_data, in_layer.output);
}

void encoder::clear_accumulators() {
	clear_accumulators(in_layer);
	clear_accumulators(out_layer);
	clear_accumulators(hidden_layer);
	clear_accumulators(in_links);
	clear_accumulators(out_links);
}



void encoder::zero_out(ln& n) {
	n.network.setZero();
	n.output.setZero();
	n.oprime.setZero();
	n.error.setZero();
	n.target.setZero();
	n.sensitivity.setZero();
}


void encoder::zero_out(ll& l) {
	l.weights_delta.setZero();
	l.bias.setZero();
	l.weights_delta.setZero();
	l.bias_delta.setZero();
}

void encoder::resize(ln& n, int r, int d) {
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

void encoder::resize(ll& l, int i, int o) {
	l.weights.resize(i, o);
	l.bias.resize(o);
	l.weights_delta.resize(i, o);
	l.bias_delta.resize(o);
	l.indims = i;
	l.outdims = o;
	zero_out(l);
}

void encoder::randomize(ll& l) {
	l.weights.setRandom();
	l.bias.setRandom();
}

void encoder::clear_accumulators(ln& n) {
	n.sensitivity.setZero();
}

void encoder::clear_accumulators(ll& l) {
	l.weights_delta.setZero();
	l.bias_delta.setZero();
}
