#include<Eigen/Core>
#include<iostream>
#include<vector>
#include<fstream>
#include"noise.h"
#include"net_layer_manager.h"

int main(int argc, char* argv[]) {
	std::ifstream input_file;
	input_file.open("data/sample_input01.txt");
	if (!input_file) {
		std::cerr << "error occurred during attempt to open input file\n";
		return 1;
	}
	ai::Layer_Manager l(input_file, 10, 1);
	std::cout << *l.layer << '\n';
	return 0;


}

