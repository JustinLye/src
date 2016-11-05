#include<iostream>
#include<fstream>
#include"fann_structs.h"


int main(int argc, char* argv[]) {
	
	if (argc > 1) {
		int o = -1;
		if (argc > 2)
			o = std::atoi(argv[2]);
		nn::Layer_Data l(argv[1], o);
		std::cout << l << std::endl;
	}

	return 0;

}