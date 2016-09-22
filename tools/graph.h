#if !defined(__GRAPH_SEARCH_HEADER__)
#define __GRAPH_SEARCH_HEADER__

#include "state.h"

namespace graph_search {
	class graph : public queue {
	private:
		state _root;
		int _search_target;
		//queue _dequeued;
	public:
		graph() : _root(1,ROOT, &_root), _search_target(-1) {
			this->insert(&_root);
		}
		void expand();
		void queue_state(int _regval, op operation, state* _parent);

	};

}

#endif

