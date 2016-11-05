#include<Eigen/Core>
#include<iostream>
namespace test {
	class eigen_test {
	public:
		eigen_test() : mat_ptr(nullptr) {}
		Eigen::MatrixXd* mat_ptr;
		void update(int row, int col, double val) {
			mat_ptr->operator()(row,col) = val;
		}
		friend std::ostream& operator<<(std::ostream& s, const eigen_test& e) {
			s << *e.mat_ptr << '\n';
		}
	};
}