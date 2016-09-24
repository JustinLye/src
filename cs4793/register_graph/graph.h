#if !defined(__JEL_GRAPH_HEADER__)
#define __JEL_GRAPH_HEADER__

#include"..\..\tools\queue.h"
#include"state.h"

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
		jel::queue<jel::state> _queue;
		jel::queue<jel::state> _searched_queue;
		jel::state _current_state;
		graph() : _root(1, 0, nullptr) {
			_queue.insert(_root);
		}

		void Expand() {
			jel::state state_node = _queue.pop();

#ifdef JELDEBUG
			std::cout << "Popping: " << state_node << '\n';
			_searched_queue.insert(state_node);
			_current_state = state_node;
#endif
			if (state_node._regval == 1) {
				_queue.insert(GenerateState(state_node, jel::ADD));
			} else {
				_queue.insert(GenerateState(state_node, jel::DUB));
				_queue.insert(GenerateState(state_node, jel::ADD));
				_queue.insert(GenerateState(state_node, jel::SUB));
				if (state_node._regval % 3 == 0) {
					_queue.insert(GenerateState(state_node, jel::DIV));
				}
			}
#ifdef JELDEBUG
			std::cout << "Expanding: " << _queue << '\n';
#endif
		}
		jel::state Dequeue() {
			return _queue.pop();
		}
		jel::state GenerateState(jel::state& parent, jel::op operation) {
			switch (operation) {
			case ADD:
				return jel::state(parent._regval + 1, parent._path_cost + 1, &parent);
				break;
			case SUB:
				return jel::state(parent._regval - 1, parent._path_cost + 1, &parent);
				break;
			case DUB:
				return jel::state(parent._regval * 2, parent._path_cost + parent._regval, &parent);
				break;
			case DIV:
				return jel::state(parent._regval / 3, parent._path_cost + ((2 / 3)*parent._regval), &parent);
				break;
			}
		}
	};
}

#endif
