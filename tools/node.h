#if !defined(__JEL_NODE_HEADER__)
#define __JEL_NODE_HEADER__

namespace jel {
	template<typename T>
	class node {
	public:
		T info;
		node<T>* next;
		node() : next(nullptr) {}
		node(const T& n) : info(n), next(nullptr) {
			std::cout << "creating node<T>: " << this << '\n';
		}
		//node(T* n) : info(*n), next(nullptr) {
		//	std::cout << "creating node<T>: " << this << '\n';
		//}
		~node() {
			std::cout << "deleting node<T>: " << this << '\n';
		}

	};

}

#endif
