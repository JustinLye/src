#if !defined(__JEL_NODE_HEADER__)
#define __JEL_NODE_HEADER__

namespace jel {
	template<typename T>
	class node {
	public:
		T info;
		node<T>* next;
		node() : next(nullptr) {
#if defined(JELMEMTRACK)
			std::cout << "creating node<T> " << __LINE__ << ": " << this << '\n';
#endif
		}
		node(const T& n) : info(n), next(nullptr) {
#if defined(JELMEMTRACK)
			std::cout << "creating node<T> " << __LINE__ << ": " << this << '\n';
#endif
		}

		~node() {
#if defined(JELMEMTRACK)
			std::cout << "deleting node<T>: " << this << '\n';
#endif
		}

	};

}

#endif
