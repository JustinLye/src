//20160922 - Justin Lye: Created File
#if !defined(__JEL_STATE_NODE_HEADER__)
#define __JEL_STATE_NODE_HEADER__

/* data structure to represent state nodes in graph search
   using operations as arcs and cost as n for op DUB
   (2/3) * n for DIV and 1 for others
*/

#include<iostream>

namespace jel {

	//will encapsulate after getting the graph to work properly

	class state {
	private:
		//member functions
		void _out(std::ostream& s) const {
			s << " {" << this->_regval << "} ";
		}
	public:
		//member variables
		int _regval;      //value in register
		int _path_cost;   //path cost to get to this register
		state* _parent;   //parent state node

		//constructors
		state() : _regval(0), _path_cost(0), _parent(nullptr) {}
		state(int regval, int path_cost) : _regval(regval), _path_cost(path_cost), _parent(nullptr) {}
		state(int regval, int path_cost, state* path) : _regval(regval), _path_cost(path_cost), _parent(path) {}
		
		//friends
		friend std::ostream& operator<<(std::ostream& s, const state& st) {
			st._out(s);
			return s;
		}
		friend std::ostream& operator<<(std::ostream& s, const state* st) {
			st->_out(s);
			return s;
		}
	};

}

#endif


