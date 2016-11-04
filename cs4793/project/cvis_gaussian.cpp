#include "cvis_gaussian.h"
//
void jel::gausssian_kernel(cv::Mat& output_mat, int mat_size, double sigma) {
	output_mat.release();
	output_mat.create(cv::Size(mat_size,mat_size), CV_64F);
	double sigma_sqrd = std::pow(sigma,2);
	double constant_multiplier = (1.0/(2.0 * jel::PI * sigma_sqrd));
	int split = std::floor(mat_size/2);
	int row = 0;
	int col = 0;
	std::cout << output_mat.elemSize() << '\n';
	std::cout << sizeof(double) << '\n';
	cv::MatIterator_<double> it = output_mat.begin<double>();
	for (int x = -1 * split; x < split + 1; x++,row++) {
		for (int y = -1 * split; y < split + 1; y++,col++) {
			(*it) = constant_multiplier * std::exp(-1.0*((std::pow(x,2.0)+std::pow(y,2.0))/(2.0 * sigma_sqrd)));
			it++;
		}
	}
}