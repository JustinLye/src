#include<iostream>
#include<thread>
#include<string>


class functor {
public:
	void operator()(std::string* s) {
		std::cout << "from functor " << *s << std::endl;
		*s = "let's go pokes";
	}
};

int main(int argc, char* argv[]) {
	std::string s = "boomer sooner";
	std::thread t1((functor()),&s);
	t1.join();
	std::cout << "from main: " << s << std::endl;


	return 0;
}