#include<iostream>
#include<thread>
#include<string>
#include<ctime>

void print_int(int p) { std::cout << p << std::endl; }


template<class ...Us> void f(Us... pargs) {}
template<class ...Ts> void g(Ts... args) {
	f(&args...); // “&args...” is a pack expansion
				 // “&args” is its pattern
}


int main(int argc, char* argv[]) {
	g(1, 0.2, "a"); // Ts... args expand to int E1, double E2, const char* E3
					// &args... expands to &E1, &E2, &E3
					// Us... pargs expand to int* E1, double* E2, const char** E3
	g(print_int,10);

	return 0;
}