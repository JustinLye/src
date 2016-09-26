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
		int _expanded_nodes;
		int _queue_size;
	public:
		jel::state_queue _queue;
		graph() : _expanded_nodes(0), _queue_size(1) {
			_queue.insert(1,0,jel::ONE,nullptr);
		}

		void Expand() {
			_expanded_nodes++;
			_queue_size--;
			jel::state* current_node = &_queue.pop_ref();
			if (current_node->_regval % 3 == 0) {
				_queue.insert(current_node->_regval / 3, current_node->_path_cost + (2 / 3)*current_node->_regval, jel::DIV, current_node);
				_queue_size ++;
			} else {
				_queue.insert(current_node->_regval + 1, current_node->_path_cost + 1, jel::ADD, current_node);
				_queue_size++;
				if (current_node->_regval >= 1) {
					_queue.insert(current_node->_regval - 1, current_node->_path_cost + 1, jel::SUB, current_node);
					_queue.insert(current_node->_regval * 2, current_node->_path_cost + current_node->_regval, jel::DUB, current_node);
					
					_queue_size += 2;
				}
			}
		}
		int NodesExpanded() const {
			return this->_expanded_nodes;
		}
		int QueueSize() const {
			return this->_queue_size;
		}
		jel::state& Find(int target) {
			//if (_expanded_nodes % 100 == 0) {
				//std::cout << "nodes expanded had reached: " << _expanded_nodes << " nodes\n";
			//}
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
