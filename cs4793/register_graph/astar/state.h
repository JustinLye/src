//20160922 - Justin Lye: Created File
#if !defined(__JEL_STATE_NODE_HEADER__)
#define __JEL_STATE_NODE_HEADER__

/* data structure to represent state nodes in graph search
   using operations as arcs and cost as n for op DUB
   (2/3) * n for DIV and 1 for others
*/

#include<iostream>
#include"register_ops.h"

namespace jel {
	class state {
	protected:
		//private members
		int register_value;
		int path_cost;
		int* heap_key;
		operation parent_op;
		state* parent_state;
		state* next; //for queue
		void print_function(std::ostream& s) const {
			s << parent_op << "[" << register_value << "/" << path_cost << "] ";
		}
		void _PrintHistory(state* s) {
			if (s == nullptr) {
				return;
			} else {
				_PrintHistory(s->parent_state);
				std::cout << *s;
			}
		}
	public:
		//constructor
		state() : register_value(0), path_cost(0), heap_key(&path_cost), parent_op(NONE), next(nullptr) {}
		state(int register_val, int cost, operation par_op, state* parent) :
			register_value(register_val), path_cost(cost), heap_key(&path_cost), parent_op(par_op), parent_state(parent), next(nullptr) {}
		
		//getters
		inline int RegisterValue() const { return register_value; }
		inline int PathCost() const { return path_cost; }
		inline operation ParentOp() const { return parent_op; }
		inline const state* Parent() const { return parent_state; }
		inline const state* Next() const { return next; }
		inline int* HeapKey() { return heap_key; }
		//setters
		inline void SetRegisterValue(int val) { register_value = val; }
		inline void SetPathCost(int val) { path_cost = val; }
		inline void SetParentOp(operation& ops) { parent_op = ops; }
		inline void SetParent(state* paren) { parent_state = paren; }
		inline void SetNext(state* nxt) { next = nxt; }

		//functions
		void PrintHistory() {
			this->_PrintHistory(this);
		}

		//comparision operators (path_cost is evaluated)
		bool operator<(const state& s) { return (this->path_cost < s.path_cost); }
		bool operator<=(const state& s) { return (this->path_cost <= s.path_cost); }
		bool operator>(const state& s) { return (this->path_cost > s.path_cost); }
		bool operator>=(const state& s) { return (this->path_cost >= s.path_cost); }
		bool operator<(const state* s) { return (s->path_cost < this->path_cost); }
		bool operator<=(const state* s) { return (s->path_cost <= this->path_cost); }
		bool operator>(const state* s) { return (s->path_cost > this->path_cost); }
		bool operator>=(const state* s) { return (s->path_cost >= this->path_cost); }

		//friends
		friend std::ostream& operator<<(std::ostream& s, const state& st) {
			st.print_function(s);
			return s;
		}
		friend class state_queue;
		friend class graph;
		friend class priority_queue;
	};

}

#endif


