
#include "pa_util.h"

#if !defined(__NN_FANN_UTIL_HEADER__)
#define __NN_FANN_UTIL_HEADER__


namespace nn {
	typedef Eigen::MatrixXd mat;
	typedef Eigen::RowVectorXd vec;
	typedef Eigen::MatrixXd* mat_ptr;
	typedef Eigen::RowVectorXd* vec_ptr;

	void process_raw_data(
		mat& raw_data,
		mat& input_data,
		mat& target_data,
		double true_target = 0.9,
		double wrong_target = 0.1);
	bool process_raw_data(
		std::istream& in,
		mat& input_data,
		mat& target_data,
		double true_target = 0.9,
		double wrong_target = 0.1);

	bool load_raw_data(std::istream& in, mat& raw_data);
	void copy_from_stdvector(std::vector<std::vector<double> >& data_vector, mat& data_matrix);
};

#endif