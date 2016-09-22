#include<iostream>

#include"graph.h"

int main(int argc, char* argv[]) {
	graph_search::graph q;
	q.expand();
	q.expand();
	//q.expand();
	//q.expand();
	std::cout << q << '\n';
	return 0;

}