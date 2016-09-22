#if !defined(__JEL_NODE_HEADER__)
#define __JEL_NODE_HEADER__

#include<istream>

namespace jel {
	template<typename T>
	class node {
	private:
		virtual void _out(std::ostream& s) const = 0;
	public:
		T info;
		node() {}
		node(T& init_info) : info(init_info) {}
	};

}

#endif
