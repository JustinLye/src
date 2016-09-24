#include<iostream>

#include"graph.h"

int main(int argc, char* argv[]) {
	jel::queue<jel::state> q;
	q.insert(jel::state(1, 0));
	q.insert(jel::state(2, 0));
	jel::state s = q.pop();
	std::cout << s << '\n';
	q.insert(jel::state(3, 0, &s));
	q.pop();
	std::cout << q.pop()._parent << '\n';
	
	return 0;
}