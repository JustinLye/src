#include<iostream>
#include"..\..\tools\node.h"
#include"state.h"
#include"state_queue.h"
//#include"graph.h"

namespace jel {
#if !defined(__JEL_REGISTER_OPS__)
#define __JEL_REGISTER_OPS__
	//enumeration of possible register operations
	enum op { NONE, ROOT, ADD, SUB, DUB, DIV };
#endif
}
jel::state& GenerateState(jel::state&, jel::op);
void message(int line, const char* msg);
int main(int argc, char* argv[]) {
	message(__LINE__, "");
	jel::state s = jel::state(1, 0);
	message(__LINE__, "");
	jel::state_queue q;
	message(__LINE__, "");
	q.insert(s._regval, s._path_cost, s._parent);
	message(__LINE__, "");
	jel::state s0 = q.pop();
	message(__LINE__, "");
	q.insert(s0._regval + 1, 1, &s0);
	message(__LINE__, "");
	jel::state s1 = q.pop();
	message(__LINE__, "");
	q.insert(s1._regval + 1, s1._path_cost + 1, &s1);
	message(__LINE__, "");
	q.insert(s1._regval - 1, s1._path_cost + 1, &s1);
	message(__LINE__, "");
	q.insert(s1._regval * 2, s1._path_cost + s1._regval, &s1);
	message(__LINE__, "");
	std::cout << *s1._parent << '\n';
	std::cout << &s1 << '\n';
	message(__LINE__, "");
	std::cout << q << '\n';
	std::cout << q._garbage << '\n'; 

	
	return 0;
}

void message(int line, const char* msg) {
	std::cout << line << ' ' << msg << '\n';
}

jel::state& GenerateState(jel::state& parent, jel::op operation) {
	jel::state* temp = nullptr;
	switch (operation) {
	case jel::ADD:
#if defined(JELMEMTRACK)
		std::cout << "generate state (ADD) creating temp\n";
#endif
		temp = new jel::state(parent._regval + 1, parent._path_cost + 1, parent);
		return *temp;
		break;
	case jel::SUB:
		temp = new jel::state(parent._regval - 1, parent._path_cost + 1, parent);
		return *temp;
		break;
	case jel::DUB:
		temp = new jel::state(parent._regval * 2, parent._path_cost + parent._regval, parent);
		return *temp;
		break;
	case jel::DIV:
		temp = new jel::state(parent._regval / 3, parent._path_cost + ((2 / 3)*parent._regval), parent);
		return *temp;
		break;
	}
}