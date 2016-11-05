#include<iostream>
#include<random>
#include<ctime>
#include<iomanip>

#include "utility.h"

int main(int argc, char* argv[]) {
	char user_input[100];
	jel::uty::ConsoleRFI(user_input, 100,'\n', "enter something: ");
	std::cout << "you typed: " << user_input << "\n\n";
	std::cout << JEL_PRINT_PYTHON_LIKE_FORMAT << '\n';
	std::cout << JEL_STATUS_NOT_OKAY << '\n';
	std::cout << JEL_STATUS_OKAY << '\n';
	std::cout << JEL_STATUS_UNKNOWN << '\n';
	


	return 0;
}