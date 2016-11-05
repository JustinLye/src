#include<Eigen/Core>
#include<iostream>
#include<vector>
#include<fstream>
#include<random>
#include<ctime>
#include"noise.h"
#include"net_layer_manager.h"

int main(int argc, char* argv[]) {
	srand(time(NULL));
	std::ifstream input_file;
	if(argc < 2)
		input_file.open("data/sample_input01.txt");
	else
		input_file.open(argv[1]);
	if (!input_file) {
		std::cerr << "error occurred during attempt to open input file\n";
		return 1;
	}
	ai::Layer_Manager l(input_file, 9, 1);
	l.initialize_links();
	std::cout << *l.layer << '\n';
	l.add_input_noise();
	std::cout << *l.layer << '\n';
	l.feed_forward();
	std::cout << *l.layer << '\n';
	return 0;


}

