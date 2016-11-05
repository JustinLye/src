#include<iostream>
#include<string>
#include"..\tools\sort.h"

void print_fun(int x) { std::cout << x << '\n'; }
void wait(int seconds) {
	clock_t end = seconds * CLOCKS_PER_SEC;
	while (clock() < end) {

	}
	std::cout << "done waiting for " << seconds << " seconds...\n";
}
void prompt() { std::cout << "u no wat 2 dew\t"; }


int main(int argc, char* argv[]) {
	jel::handler h(wait,4);
	std::cout << "waitin...waitin on the world to change...\n";
	std::cout << "are we there yet\n\n";
	
}