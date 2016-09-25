#if !defined(__JEL_GRAPH_HEADER__)
#define __JEL_GRAPH_HEADER__

#include"state_queue.h"

namespace jel {
#if !defined(__JEL_REGISTER_OPS__)
#define __JEL_REGISTER_OPS__
	//enumeration of possible register operations
	enum op { NONE, ROOT, ADD, SUB, DUB, DIV };
#endif
	//will encapsulate later
	class graph {
	public:
		jel::state _root;
		jel::state_queue _queue;
		jel::queue<jel::state> _searched_queue;
		jel::state _current_state;
		graph() : _root(1, 0, nullptr) {
			_queue.insert(_root);
		}

		void Expand() {
			//jel::state* state_node = new jel::state(_queue.pop());
			jel::state state_node = _queue.pop();

#ifdef JELDEBUG
			//std::cout << "Popping: " << state_node << '\n';
			//_searched_queue.insert(state_node);
			//_current_state = state_node;
#endif
			if (state_node._regval == 1) {
				jel::node<jel::state>* temp = &GenerateState(state_node, jel::ADD)->info;
				_queue.insert(*temp);
				////delete temp;
#if defined(JELMEMTRACK)
				std::cout << "after generate state\n";
#endif
			} else {
				jel::node<jel::state>* temp = &GenerateState(state_node, jel::DUB)->info;
				_queue.insert(*temp);
				//delete temp;
				temp = &GenerateState(state_node, jel::ADD);
				_queue.insert(*temp);
				//delete temp;	
				//_queue.insert(GenerateState(state_node, jel::DUB));
#if defined(JELMEMTRACK)
				std::cout << "after generate state\n";
#endif
				jel::node<jel::state>* temp = &GenerateState(state_node, jel::SUB)->info;
				_queue.insert(*temp);
				//delete temp;
				//_queue.insert(GenerateState(state_node, jel::ADD));
#if defined(JELMEMTRACK)
				std::cout << "after generate state\n";
#endif
				//_queue.insert(GenerateState(state_node, jel::SUB));
#if defined(JELMEMTRACK)
				std::cout << "after generate state\n";
#endif
				if (state_node._regval % 3 == 0) {
					jel::node<jel::state>* temp = &GenerateState(state_node, jel::DIV)->info;
					_queue.insert(*temp);
					//delete temp;
					//_queue.insert(GenerateState(state_node, jel::DIV));
#if defined(JELMEMTRACK)
					std::cout << "after generate state\n";
#endif
				}
			}
#ifdef JELDEBUG
			std::cout << "Expanding: " << _queue << '\n';
#endif
		}
		jel::state Dequeue() {
			return _queue.pop();
		}
		jel::node<jel::state>* GenerateState(jel::state& parent, jel::op operation) {
			jel::node<jel::state>* temp = nullptr;
			switch (operation) {
			case ADD:
#if defined(JELMEMTRACK)
				std::cout << "generate state (ADD) creating temp\n";
#endif
				temp = new jel::node<jel::state>(parent._regval + 1, parent._path_cost + 1, &parent);
				return temp;
				break;
			case SUB:
				temp = new jel::node<jel::state>(parent._regval - 1, parent._path_cost + 1, &parent);
				return temp;
				break;
			case DUB:
				temp = new jel::node<jel::state>(parent._regval * 2, parent._path_cost + parent._regval, &parent);
				return temp;
				break;
			case DIV:
				temp = new jel::node<jel::state>(parent._regval / 3, parent._path_cost + ((2 / 3)*parent._regval), &parent);
				return temp;
				break;
			}
		}
	};
}

#endif
