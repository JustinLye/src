#include<iostream>
#include"graph.h"

int prompt();
void setvalue(int);
int main(int argc, char* argv[]) {
	int val = prompt();
	while (val >= 0) {
		setvalue(val);
		val = prompt();
	}
	
	return 0;
}

void setvalue(int val) {
	jel::graph g;
	jel::state s = g.Find(val);
	//std::cout << "Nodes Expanded:\t" << g.NodesExpanded() << "\n\n";
	std::cout << "Goal:\n" << s << "\n\n" << "Path:\n";
	s.PrintHistory();
	std::cout << "\n\nCurrent Queue:\nState(value) : { path cost, parent op }\n\n" << g._queue << '\n';
	
}


int prompt() {
	int val = 0;
	std::cout << "Enter desired register value: ";
	std::cin >> val;
	return val;
}

