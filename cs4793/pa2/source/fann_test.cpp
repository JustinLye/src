#include<iostream>
#include<fstream>
#include"fann_util.h"


int main(int argc, char* argv[]) {
	if (argc > 1) {
		nn::mat data;
		nn::mat in_data;
		nn::mat target;
		std::ifstream in;
		in.open(argv[1]);
		if (nn::load_raw_data(in, data)) {
			std::cout << "raw data\n" << data << '\n';
			nn::process_raw_data(data, in_data, target);
			std::cout << "input data\n" << in_data << '\n';
			std::cout << "target data\n" << target << '\n';
		} else {
			std::cerr << "error: load raw data failed\n";
		}
		in.close();

	}

	return 0;

}