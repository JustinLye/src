

#if !defined(__JEL_CVIS_UTILITY_CPP__)
#define __JEL_CVIS_UTILITY_CPP__

#if !defined(__JEL_CVIS_UTILITY_HEADER__)
#include "cvis_utility.h"
#endif


__declspec(dllexport) void jel::createAndShow(const char* name, cv::Mat& img, int winType) {
	cv::namedWindow(name, winType);
	cv::imshow(name, img);
}


void jel::writeGrayImg(const char* filename, cv::Mat& img) {
	std::ofstream out;
	out.open(filename);
	cv::MatIterator_<uchar> iter = img.begin<uchar>();
	cv::MatIterator_<uchar> end = img.end<uchar>();
	int col_count = 0;
	int col_max = img.cols;
	for (; iter != end; ++iter) {
		out << std::setw(3) << std::setfill('0') << static_cast<int>(*iter) << " ";
		col_count++;
		if (col_count == col_max) {
			col_count = 0;
			out << std::endl;
		}
	}
	out.close();
}

//taken from http://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html?#houghlinesp
void jel::plotLines(cv::Mat& dst_img, cv::vector<cv::Vec2f>& lines_vec) {
	for (size_t i = 0; i < lines_vec.size(); i++) {
		float rho = lines_vec[i][0];
		float theta = lines_vec[i][1];
		double a = cv::cos(theta);
		double b = cv::sin(theta);
		double x0 = a*rho;
		double y0 = b*rho;
		cv::Point p1 (cvRound(x0 + 1000 * (-b)), cvRound(y0 + 1000 * (a)));
		cv::Point p2 (cvRound(x0 - 1000 * (-b)), cvRound(y0 - 1000 * (a)));
		line(dst_img, p1, p2, cv::Scalar(0,0,255), 3, 8);
	}
}

void jel::printMatrix(cv::Mat& input_mat, int output_precision, int output_width) {
	cv::MatIterator_<double> it = input_mat.begin<double>();
	cv::MatIterator_<double> end = input_mat.end<double>();
	int col_count = 0;
	while (it != end) {
		std::cout << std::setprecision(output_precision) << std::setw(output_width) << (*it);
		col_count++;
		if (col_count >= input_mat.cols) {
			col_count = 0;
			std::cout << '\n';
		} else {
			std::cout << ' ';
		}
		it++;
	}
}

#endif