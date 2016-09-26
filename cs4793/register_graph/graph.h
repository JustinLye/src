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
	private:
		//int _expanded_nodes;
	public:
		jel::state _root;
		jel::state_queue _queue;
		graph() : _root(1,0,jel::ROOT,nullptr) {
			_queue.insert(1,0,jel::ROOT,nullptr);
		}

		void Expand() {
			//_expanded_nodes++;
			jel::state* current_node = &_queue.pop_ref();
			_queue.insert(current_node->_regval + 1, current_node->_path_cost + 1, jel::ADD, current_node);
			if (current_node->_regval >= 1) {
				_queue.insert(current_node->_regval * 2, current_node->_path_cost + current_node->_regval, jel::DUB, current_node);
				_queue.insert(current_node->_regval - 1, current_node->_path_cost + 1, jel::SUB, current_node);
				
				if (current_node->_regval % 3 == 0) {
					_queue.insert(current_node->_regval / 3, current_node->_path_cost + (2/3)*current_node->_regval,jel::DIV, current_node);
				}
			}
		}
		//int NodesExpanded() const {
//			return this->_expanded_nodes;
	//	}
		jel::state& Find(int target) {
			if (target == _queue.peek()._regval) {
				return _queue.pop_ref();
			} else {
				Expand();
				this->Find(target);
			}
		}

	};
}

#endif
