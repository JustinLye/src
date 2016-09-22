#include "state.h"

void graph_search::queue::insert(graph_search::state* n) {
	state_wrapper* s = new state_wrapper(n);
	if (_tail == nullptr) {
		_tail = s;
		_head = s;
	} else {
		_tail->_next = s;
		_tail = s;
	}
}

graph_search::state graph_search::queue::dequeue() {
	state_wrapper* temp;
	state* popped = nullptr;
	if (_head != nullptr) {
		popped = _head->_info;
		temp = _head;
		_head = _head->_next;
		delete temp;
		
	}
	return *popped;
}
//
//void graph_search::queue::dequeue_insert(graph_search::state_wrapper* n) {
//	if (this->_dqlist == nullptr) {
//		this->_dqlist = n;
//	} else {
//		_dqlist->_next = n;
//	}
//}