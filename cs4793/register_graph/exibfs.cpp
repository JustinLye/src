#include<iostream>

#include"graph.h"
int main(int argc, char* argv[]) {
	std::cout << "init g\n";
	jel::graph g;
	std::cout << "expand 1\n";
	g.Expand();
	std::cout << "expand 2\n";
	g.Expand();
	std::cout << g._queue << '\n';
	return 0;
}