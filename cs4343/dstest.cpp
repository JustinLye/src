#include<iostream>
#include"dshash.h"
int main(int argc, char* argv[]) {
	int a = std::atoi(argv[1]);
	int b = std::atoi(argv[2]);
	std::cout << ds::hash::lesser_power_of(a,b) << " is the closest power of " << b << " that is less than " << a << std::endl;
	return 0;
}