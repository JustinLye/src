#if !defined(__GRAPH_STATE_HEADER__)
#define __GRAPH_STATE_HEADER__

#include<iostream>
#include<string>

namespace graph_search {
	enum op { ROOT, ONE, SUB, ADD, DUB, DIV };

	class graph_error {
	private:
		const char* _what;
	public:
		graph_error() : _what("unknown error") {}
		graph_error(const char* err_msg) : _what(err_msg) {}
		graph_error(const std::string& err_msg) : _what(err_msg.c_str()) {}
		graph_error(const graph_error& err) : _what(err._what) {}
		graph_error(const graph_error* err) : _what(err->_what) {}
		const char* what() const {
			return _what;
		}
	};

	class arc {
	private:
		void output(std::ostream& s) const {
			s << " {" << this->_regval << "} ";
		}
		arc() {}
		
	protected:
		int _cost;
	public:
		int _regval;
		op _op;
		arc(const arc& a) {}
		arc(int regval, op operation) : _regval(regval), _cost(0), _op(operation) {
			switch (_op) {
			case ROOT:
				_cost = 0;
			case DUB:
				_cost = _regval;
				break;
			case DIV:
				_cost = (2 / 3) * _regval;
				break;
			default:
				_cost = 1;
				break;
			}
		}
		
		virtual inline int cost() = 0;

		friend std::ostream& operator<<(std::ostream& s, const arc* st) {
			st->output(s);
			return s;
		}
		friend std::ostream& operator<<(std::ostream& s, const arc& st) {
			st.output(s);
			return s;
		}
	};

	class state : public arc {
	private:
		//void output(std::ostream& s) const {
		//	s << this->_info;
		//}
		
		//state(state* s) : arc(s->_regval, s->_op) {}
	public:
		state* _parent;
		state() : arc(1,ROOT), _parent(nullptr) {}
		state(int regval, op operation, state* parent) : arc(regval, operation), _parent(parent) {}
		state(const state* s) : arc(s->_regval, s->_op), _parent(s->_parent) {}
		state(const state& s) : arc(s._regval, s._op) {}
		inline int cost() {
			return this->_cost;
		}
		//friend std::ostream& operator<<(std::ostream& s, const state* n) {
		//	n->output(s);
		//	return s;
		//}
		//friend std::ostream& operator<<(std::ostream& s, const state& n) {
		//	n.output(s);
		//	return s;
		//}

	};

	class state_wrapper {
	private:
		void output(std::ostream& s) const {
			s << this->_info;
		}

	public:
		state* _info;
		state_wrapper* _next;
		state_wrapper() : _info(nullptr), _next(nullptr) {}
		state_wrapper(state* n) : _info(n), _next(nullptr) {}
		state_wrapper(state_wrapper* w) : _info(w->_info), _next(w->_next) {}
		friend std::ostream& operator<<(std::ostream& s, const state_wrapper* st) {
			st->output(s);
			return s;
		}
		friend std::ostream& operator<<(std::ostream& s, const state_wrapper& st) {
			st.output(s);
			return s;
		}

	};


	class queue {
	private:
		state_wrapper* _tail;
		state_wrapper* _head;
		state_wrapper* _dqlist;

		void output(std::ostream& s) const {
			state_wrapper* temp = _head;
			while (temp != nullptr) {
				s << temp->_info;
				temp = temp->_next;
			}
		}
	protected:
		queue() : _tail(nullptr), _head(nullptr) {}
		//void dequeue_insert(state_wrapper* n);
	public:
		virtual void insert(state*);
		state dequeue();
		friend std::ostream& operator<<(std::ostream& s, const queue* q) {
			q->output(s);
			return s;
		}
		friend std::ostream& operator<<(std::ostream& s, const queue& q) {
			q.output(s);
			return s;
		}
	};

}
#endif