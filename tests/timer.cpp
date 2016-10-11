#include<iostream>
#include<thread>
#include<chrono>
void foo(int id) {
	std::this_thread::sleep_for(std::chrono::seconds(10));
	std::cout << "Timer: " << id << "\n\n";
}

int main(int argc, char* argv[]) {
	std::thread t1(foo,1);
	std::thread t2(foo,2);
	std::thread t3(foo,3);
	std::thread t4(foo,4);
	std::thread t5(foo,5);
	std::thread t6(foo,6);
	std::thread t7(foo,7);
	std::thread t8(foo,8);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	return 0;
}