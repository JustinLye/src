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
#ifdef JELDEBUG
			s << "Address: " << this <<  " {" << this->_regval << ", " << this->_path_cost << "} ";
#else
			s << " {" << this->_regval << ", " << this->_path_cost << "} ";
#endif
		
		}
	public:
		//member variables
		int _regval;      //value in register
		int _path_cost;   //path cost to get to this register
		state* _parent;   //parent state node

		//constructors
		state() : _regval(0), _path_cost(0), _parent(nullptr) {}
		state(const state& s) : _regval(s._regval), _path_cost(s._path_cost), _parent(s._parent) {}
		state(int regval, int path_cost) : _regval(regval), _path_cost(path_cost), _parent(nullptr) {}
		state(int regval, int path_cost, state* path) : _regval(regval), _path_cost(path_cost), _parent(path) {}
		
		bool operator==(const jel::state s) {
			return ((this->_regval == s._regval && this->_path_cost == s._path_cost && this->_parent == s._parent));
		}

		//friends
		friend std::ostream& operator<<(std::ostream& s, const state& st) {
			st._out(s);
			return s;
		}
#if !defined(JELDEBUG)
		friend std::ostream& operator<<(std::ostream& s, const state* st) {
			st->_out(s);
			return s;
		}
#endif
	};

}

#endif


