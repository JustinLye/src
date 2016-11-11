#include<Eigen/Core>
#include<iostream>
#include<vector>
#include<random>
#include<time.h>
#include"nn_auto_encoder.h"

using namespace nn;
const char* outfile = "../output.txt";

int main(int argc, char* argv[]) {
	encoder e;
	e.init_lrate = 2.0;
	e.lrate = 2.0;
	e.batchsize = 32;
	e.beta = 0.001;
	e.initialize(16, argv[1]);
	std::ofstream outf;
	outf.open(outfile);
	for (int i = 0; i < 10; i++) {
		e.train_step();
		e.update_lrate();
		outf << "Step: " << i << std::endl << std::endl;
		outf << e;
	}
	outf.close();

	return 0;
}



