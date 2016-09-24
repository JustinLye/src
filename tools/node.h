#if !defined(__JEL_NODE_HEADER__)
#define __JEL_NODE_HEADER__

#include<iostream>

namespace jel {
	template<typename T>
	class node {
	public:
		T info;
		node<T>* next;
		node() : next(nullptr) {}
		node(const T& n) : info(n), next(nullptr) {}
		node(T* n) : info(*n), next(nullptr) {}

	};

}

#endif
