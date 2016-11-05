#include<iostream>
#include<thread>
#include<chrono>
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

		inline unsigned int payload() const { return _payload; }

		inline friend std::ostream& operator<<(std::ostream& s, const node& n) {
			n.print(s);
			return s;
		}
	private:
		T _payload;
		inline void print(std::ostream& s) const { s << this->_payload; }

	};



	unsigned int* copy_array(unsigned int* A, unsigned int s, unsigned int e) {
		unsigned int* a = new unsigned int[e-s];
		for(unsigned int i = s; i < e; i++)
			a[i] = A[i];
		return a;
	}

}




int main(int argc, char* argv[]) {
	//int size = atoi(argv[1]);
	int quit_app = 0;
	jel::sort<unsigned int> sorter;
	while (!quit_app) {
		unsigned int size = 0;
		int thread_it = 0;
		std::cout << "size: ";
		std::cin >> size;
		std::cout << "thread it: ";
		std::cin >> thread_it;
		unsigned int a = 0;
		unsigned int b = 1000000;
		unsigned int* x = jel::random_array(size, a, b);
		unsigned int* xc = jel::copy_array(x, a, size);

		jel::tuple* t = jel::spliter(size, std::thread::hardware_concurrency());
		std::cout << "starting...\n";
		

		auto start = std::chrono::high_resolution_clock::now();
		if (thread_it) {
			std::thread t1(&jel::sort<unsigned int>::sort_array, &sorter, x, t->arg1[0], t->arg1[1]);
			std::thread t2(&jel::sort<unsigned int>::sort_array, &sorter, x, t->arg1[2], t->arg1[3]);
			std::thread t3(&jel::sort<unsigned int>::sort_array, &sorter, x, t->arg1[4], t->arg1[5]);
			std::thread t4(&jel::sort<unsigned int>::sort_array, &sorter, x, t->arg1[6], t->arg1[7]);
			std::thread t5(&jel::sort<unsigned int>::sort_array, &sorter, x, t->arg1[8], t->arg1[9]);
			std::thread t6(&jel::sort<unsigned int>::sort_array, &sorter, x, t->arg1[10], t->arg1[11]);

			t1.join();
			t2.join();
			t3.join();
			t4.join();
			t5.join();
			t6.join();

		} else {
			sorter.sort_array(x, t->arg1[0], t->arg1[1]);
			sorter.sort_array(x, t->arg1[2], t->arg1[3]);
			sorter.sort_array(x, t->arg1[4], t->arg1[5]);
			sorter.sort_array(x, t->arg1[6], t->arg1[7]);
			sorter.sort_array(x, t->arg1[8], t->arg1[9]);
			sorter.sort_array(x, t->arg1[10], t->arg1[11]);
		}
		auto elapsed = std::chrono::high_resolution_clock::now() - start;
		long long seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed).count();
		std::cout << "runtime: " << seconds << " seconds\n";
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