#include<iostream>
#include"input.h"
#include"sort.h"

int main(int argc, char* argv[]) {
	char x[100];
	
	jel::get_console_input(x, 100, '\n');
	std::cout << "\nyou wrote " << x << '\n';
	return 0;
}