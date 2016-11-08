#include<fstream>
#include "pa_util.h"

#if !defined(__NN_FANN_UTIL_HEADER__)
#define __NN_FANN_UTIL_HEADER__


namespace nn {

#define NN_PREPARED_INPUT_VALUES 0x0000
#define NN_RAW_INPUT_VALUES 0x0001

#define NN_ZERO_OUT_METHOD 0x2010
#define NN_GAUSSIAN_METHOD 0x2011
#define NN_INPUT_TYPE_STREAM 0x0020
#define NN_INPUT_TYPE_FILENAME 0x0021
#define NN_INPUT_TYPE_MATRIX 0x0022

#define NN_ENVIRO_STATUS_START 0x0100
#define NN_ENVRIO_STATUS_READY 0x0101
#define NN_EVIRIO_STATUS_BAD 0x0102
#define NN_EVIRIO_STATUS_UNINITIALIZED 0x0103
#define NN_ENVIRO_STATUS_POLICY_NOT_SET 0x0104
#define NN_ENVIRO_STATUS_END 0x0105
#define NN_ENVIRO_STATUS_INVAILD 0x0110

#define NN_ERROR_FLAG_START 0x1000
#define NN_ERROR_FLAG_DATA_LOAD 0x1010
#define NN_ERROR_FLAG_DATA_LOAD_READ_FAILURE 0x1001
#define NN_ERROR_FLAG_DATA_LOAD_BAD_FILENAME 0x1002
#define NN_ERROR_FLAG_DATA_LOAD_NOT_ENOUGH_DATA 0x1003
#define NN_ERROR_FLAG_DATA_LOAD_INVALID_DIMS 0x1004
#define NN_ERROR_FLAG_END 0x1005
#define NN_ERROR_FLAG_INVALID 0x1100

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

	bool read_raw_data(std::istream& in, mat& raw_data);
	bool read_raw_data(const char* filename, mat& raw_data);
	void copy_from_stdvector(std::vector<std::vector<double> >& data_vector, mat& data_matrix);
	};
};

#endif