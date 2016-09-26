

namespace jel {
	class trash {
	public:
		void* house_number;
		trash* next;
		trash() {}
		trash(void* location) : house_number(location) {}
	};
	class discard_queue {
	public:
		trash* trail_head;
		discard_queue() {
			trail_head = new trash();
			trail_head->next = nullptr;
		}
		~discard_queue() {
			trash* temp = nullptr;
			while (trail_head != nullptr) {
				temp = trail_head;
				trail_head = trail_head->next;
				delete temp->house_number;
				delete temp;
			}
		}
		void insert(void* location) {
			trash* temp = trail_head;
			trail_head = new trash(location);
			trail_head->next = temp;
		}
	};
}
