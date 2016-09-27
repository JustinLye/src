
#if !defined(__JEL_HEAP_HEADER__)
#define __JEL_HEAP_HEADER__

#include"obj_array.h"

namespace jel {
	template<typename T>
	class priority_queue {
	public:
		jel::obj_array<T> A;
		priority_queue() {}
	};
}

#endif