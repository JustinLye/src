#include<Eigen/Core>
#include<iostream>
#include<vector>
#include<random>
#include<time.h>
#include"../source/noise.h"
#include"../source/nn_util.h"
using namespace nn;




};

const char* outfile = "../output.txt";

int main(int argc, char* argv[]) {
	int hdims = 70;
	encoder e;
	initialize(e, hdims, argv[1]);
	e.init_lrate = 2.0;
	e.lrate = 2.0;
	for (int i = 0; i < 700; i++) {
		feed_forward(e);
		set_error(e);
		backpropogate(e);
		update_weights(e);
		clear_accumulators(e);
		e.lrate = e.init_lrate / (1.0 + sqrt(i));
	}


	std::ofstream o;
	o.open(outfile);
	o << e << std::endl;
	o.close();
	return 0;
}



