#include<iostream>
#include<fstream>

#include"auto_encoder.h"


int main(int argc, char* argv[]) {
	nn::encoder::training_policy tpolicy;
	tpolicy.batch_size(100);
	tpolicy.max_epoch(1000);
	tpolicy.hidden_layer_dims(70);
	tpolicy.noise_sigma(0.004);
	tpolicy.noising_method(NN_GAUSSIAN_METHOD);
	std::cout << tpolicy << std::endl;
	if (argc > 1) {
		nn::encoder::auto_encoder a(argv[1]);
		a.set_policy(tpolicy);
		std::cout << a._input.network_values << std::endl;
		std::cout << "(" << a._hidden->incoming_links.weights.rows() << "," << a._hidden->incoming_links.weights.cols() << ")" << std::endl;

	}

	return 0;

}