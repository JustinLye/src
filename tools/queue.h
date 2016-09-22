//20160922 - Justin Lye: created file
#if !defined(__JEL_QUEUE_HEADER__)
#define __JEL_QUEUE_HEADER__

#include<iostream>
#include"node.h"

/*

simple queue structure

*/

namespace jel {
	template<typename T>
	class queue {
	private:
		jel::node<T>* _head;
		jel::node<T>* _tail;
		virtual void _out(std::ostream& s) const = 0;
	public:
		queue() : _head(nullptr), _tail(nullptr) {}
		virtual void insert(jel::node<T>& n) = 0;
		virtual jel::node<T> pop() = 0;
	};
}

#endif


