#if !defined(__JEL_STATE_QUEUE_HEADER__)
#define __JEL_STATE_QUEUE_HEADER__

#include"..\..\tools\queue.h"
#include "state.h"
namespace jel {
	class state_queue : public jel::queue<jel::state> {
	public:
		jel::queue<jel::state> _garbage;
		jel::state pop() {
			if (_head != nullptr) {
				jel::state ret = _head->info;
				_garbage.insert(_head->info);
				_head = _head->next;
				return ret;
			}
		}
	};
}

#endif
