#if! defined(__JEL_STATES_HEADER__)
#define __JEL_STATES_HEADER__

#include<iostream>
#include"queue.h"
#include"state.h"

namespace jel {
	class states : public jel::queue<jel::state_node> {
	private:
		void _out(std::ostream& s) const {
			jel::state* print_ptr = this->_head;
			while (print_ptr != nullptr) {
				s << print_ptr;
			}
		}

	public:
		states() {}

		friend std::ostream& operator<<(std::ostream& s, const jel::states& st) {
			st._out(s);
			return s;
		}
	};
}


#endif
