
#if !defined(__JEL_REGISTER_OPS_HEADER__)
#define __JEL_REGISTER_OPS_HEADER__
#include<iostream>
namespace jel {
#if !defined(__JEL_REGISTER_OPS__)
#define __JEL_REGISTER_OPS__
	//enumeration of possible register operations
	enum op { NONE, ROOT, ADD, SUB, DUB, DIV };
#endif
	std::ostream& operator<<(std::ostream& s, op oper) {
		switch (oper) {
		case NONE:
			s << "NO OP";
			break;
		case ROOT:
			s << "ROOT";
			break;
		case ADD:
			s << "ADD";
			break;
		case SUB:
			s << "SUB";
			break;
		case DUB:
			s << "DOUBLE";
			break;
		case DIV:
			s << "DIVIDE";
			break;
		}
	}
}



#endif