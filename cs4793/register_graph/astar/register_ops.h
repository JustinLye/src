
#if !defined(__JEL_REGISTER_OPS_HEADER__)
#define __JEL_REGISTER_OPS_HEADER__
#include<iostream>
namespace jel {
#if !defined(__JEL_REGISTER_OPS__)
#define __JEL_REGISTER_OPS__
	//enumeration of possible register operations
	enum op { NONE, ONE, ADD, SUB, DUB, DIV };
#endif
	class operation {
	public:
		op oper;
		operation(op o) : oper(o) {}
		operation(const int& o) {
			switch (o) {
			case 1:
				oper = ONE;
				break;
			case 2:
				oper = ADD;
				break;
			case 3:
				oper = SUB;
				break;
			case 4:
				oper = DUB;
				break;
			case 5:
				oper = DIV;
				break;
			default:
				oper = NONE;
				break;
			}
		}
		friend std::ostream& operator<<(std::ostream& s, jel::operation o) {
			switch (o.oper) {
			case NONE:
				s << "NO OP";
				break;
			case ONE:
				s << "ONE";
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
			return s;
		}
	};


}



#endif