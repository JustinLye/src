#include<iostream>
#include<fstream>
#include<random>
#include<ctime>

#include "nn_auto_encoder.h"
#include "nn_training_policy.h"

int main(int argc, char* argv[]) {
	srand(time(NULL));
	nn::encoder::training_policy policy;
	policy.batch_size(45);
	policy.max_epoch(2);
	policy.init_lrate(2);
	policy.noise_sigma(0.001);
	policy.noising_method(NN_GAUSSIAN_METHOD);
	policy.hidden_layer_dims(70);
	policy.update_lrate(false);
	policy.use_weight_reg(false);
	policy.use_weight_reg(1.0/(2*4*70));
	//policy.sparsity_rate(1.0/4.0);
	//policy.beta(0.5);
	
	if (argc > 1) {
		nn::encoder::auto_encoder a(argv[1]);
		a.set_policy(policy);
		a.train();
		std::cout << a._hidden->output_nodes->network_values << std::endl << std::endl;
		std::cout << "targets\n" << std::endl;
		std::cout << a._hidden->training_targets << std::endl << std::endl;
		std::cout << "hmean\n";
		std::cout << a._hidden->hmean << std::endl << std::endl;
		std::cout << "kldiv\n";
		std::cout << a._hidden->kldiv << std::endl << std::endl;
		std::cout << a._hidden->outgoing_links.weights << std::endl;
		
	}

	return 0;
}