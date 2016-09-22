#include "graph.h"

void graph_search::graph::expand() {
	state current_state = this->dequeue();
	if (&current_state == nullptr) {
		//do some stuff
		return;
	} else if (current_state._regval == this->_search_target) {
		//do some stuff
		return;
	}
	if (current_state._op == ROOT) {
		this->queue_state(current_state._regval * 2, DUB, &current_state);
		return;
	}
	this->queue_state(current_state._regval * 2, DUB, &current_state);
	this->queue_state(current_state._regval + 1, ADD, &current_state);
	if(current_state._regval > 1)
		this->queue_state(current_state._regval - 1, SUB, &current_state);
	if(current_state._regval % 3 == 0)
		this->queue_state(current_state._regval / 3, DIV, &current_state);

}

void graph_search::graph::queue_state(int _regval, op operation, state* _parent) {
	state* new_state = new state(_regval, operation, _parent);
	this->insert(new_state);

}