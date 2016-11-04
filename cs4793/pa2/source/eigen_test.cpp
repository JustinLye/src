#include<iostream>
#include"eigen_test.h"

int main(int argc, char* argv[]) {
	
	Eigen::MatrixXd m(3,3);
	m.fill(1);
	test::eigen_test e;
	e.mat_ptr = &m;
	std::cout << "orig\n" << m << '\n';
	std::cout << "class orig\n" << e << '\n';
	e.update(0,0,100);
	std::cout << "mod\n" << m << '\n';
	std::cout << "class\n" << e << '\n';
	return 0;
}