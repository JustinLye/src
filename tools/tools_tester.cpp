#include<iostream>
#include<thread>
#include<ctime>
#include"random.h"
#include"sort.h"

namespace jel {
	template<typename T>
	class node {
	public:
		node() : _payload(0) { std::cout << "default constructor\n"; }
		node(T& init_payload) : _payload(init_payload) { std::cout << "default T constructor\n"; }
		node(const T& init_payload) : _payload(init_payload) { std::cout << "copy T constructor\n"; }
		node(node& n) : _payload(n._payload) { std::cout << "copy constructor\n"; }
		node(const node& n) : _payload(n._payload) { std::cout << "copy pr_value constructor\n"; }
		node(node&& n) : _payload(std::move(n._payload)) { std::cout << "move constructor\n"; }
		
		//inline node& operator=(node n) { _payload = n._payload; return (*this); }
		inline node& operator=(node& n) { _payload = n._payload; return (*this); }
		inline node& operator=(node&& n) { _payload = std::move(n._payload); return (*this); }
		
		inline bool operator<(const node& n) { return (this->_payload < n._payload); }
		inline bool operator<=(const node& n) { return (this->_payload <= n._payload); }
		inline bool operator>(const node& n) { return (this->_payload > n._payload); }
		inline bool operator>=(const node& n) { return (this->_payload >= n._payload); }
		inline bool operator==(const node& n) { return (this->_payload == n._payload); }
		inline bool operator!=(const node& n) { return (this->_payload != n._payload); }

		inline bool operator<(const T& t) { return (this->_payload < t); }
		inline bool operator<=(const T& t) { return (this->_payload <= t); }
		inline bool operator>(const T& t) { return (this->_payload > t); }
		inline bool operator>=(const T& t) { return (this->_payload >= t); }
		inline bool operator==(const T& t) { return (this->_payload == t); }
		inline bool operator!=(const T& t) { return (this->_payload != t); }

		inline friend bool operator<(const T& t, const node& n) { return (t < n._payload); }
		inline friend bool operator<=(const T& t, const node& n) { return (t <= n._payload); }
		inline friend bool operator>(const T& t, const node& n) { return (t > n._payload); }
		inline friend bool operator>=(const T& t, const node& n) { return (t >= n._payload); }
		inline friend bool operator==(const T& t, const node& n) { return (t == n._payload); }
		inline friend bool operator!=(const T& t, const node& n) { return (t != n._payload); }

		inline int payload() const { return _payload; }

		inline friend std::ostream& operator<<(std::ostream& s, const node& n) {
			n._print(s);
			return s;
		}
	private:
		T _payload;
		inline void _print(std::ostream& s) const { s << this->_payload; }

	};

	class tuple {
	public:
		int* arg1;
		int size;
		tuple() : arg1(nullptr), size(0) {}
		tuple(int init_size) : arg1(nullptr), size(init_size) {
			arg1 = new int[init_size];
		}
		tuple(const tuple& t) : arg1(t.arg1), size(t.size) {}
		~tuple() {
			if (arg1 != nullptr) {
				delete[] arg1;
			}
		}
		void print() {
			for (int i = 0; i < size; i += 2) {
				std::cout << "(" << arg1[i] << ", " << arg1[i+1] << ") ";
			}
		}
	};

	tuple* spliter(int size, int cores) {
		tuple* t = new tuple(cores*2);
		int sub_size = ceil((size-1)/cores);
		int i = 0;
		int j = 0;
		for (i = 0; i < (cores - 1) * 2; i += 2) {
			t->arg1[i] = j;
			t->arg1[i+1] = j+sub_size;
			j+=sub_size+1;
		}
		t->arg1[i] = j;
		(j < (size - 1)) ? t->arg1[i + 1] = j + ((size - 1) - j) : t->arg1[i + 1] = j;
		return t;
	}

	int* copy_array(int* A, int s, int e) {
		int* a = new int[e-s];
		for(int i = s; i < e; i++)
			a[i] = A[i];
		return a;
	}

}




int main(int argc, char* argv[]) {
	//int size = atoi(argv[1]);
	int quit_app = 0;
	jel::sort<int> sorter;
	while (!quit_app) {
		int size = 0;
		int thread_it = 0;
		std::cout << "size: ";
		std::cin >> size;
		std::cout << "thread it: ";
		std::cin >> thread_it;

		int* x = jel::random_array(size, 0, 100000);
		int* xc = jel::copy_array(x, 0, size);
		
		std::cout << "starting...\n";
		std::clock_t start = clock();
		std::clock_t end = 0;
		jel::tuple* t = jel::spliter(size, std::thread::hardware_concurrency());
	
		if (thread_it) {


			std::thread t1(&jel::sort<int>::sort_array, &sorter, x, t->arg1[0], t->arg1[1]);
			std::thread t2(&jel::sort<int>::sort_array, &sorter, x, t->arg1[2], t->arg1[3]);
			std::thread t3(&jel::sort<int>::sort_array, &sorter, x, t->arg1[4], t->arg1[5]);
			std::thread t4(&jel::sort<int>::sort_array, &sorter, x, t->arg1[6], t->arg1[7]);
			std::thread t5(&jel::sort<int>::sort_array, &sorter, x, t->arg1[8], t->arg1[9]);
			std::thread t6(&jel::sort<int>::sort_array, &sorter, x, t->arg1[9], t->arg1[10]);


			t1.join();
			t2.join();
			t3.join();
			t4.join();
			t5.join();
			t6.join();
			end = clock();
		} else {
			sorter.sort_array(x, t->arg1[0], t->arg1[1]);
			sorter.sort_array(x, t->arg1[2], t->arg1[3]);
			sorter.sort_array(x, t->arg1[4], t->arg1[5]);
			sorter.sort_array(x, t->arg1[6], t->arg1[7]);
			sorter.sort_array(x, t->arg1[8], t->arg1[9]);
			sorter.sort_array(x, t->arg1[9], t->arg1[10]);
			end = clock();
		}
		std::cout << "runtime: " << (double(end - start) / CLOCKS_PER_SEC) << '\n';
		std::cout << "done...\n";
		std::cout << "enter 1 to exit and 0 to continue...\n";
		delete t;
		delete[] x;
		delete[] xc;
		std::cin >> quit_app;
	}
		
	//std::cout << "original\n";
	//jel::array_print(xc,0,size);

	//std::cout << "\n\nmodified\n";
	//jel::array_print(x, 0, size);



	return 0;
}