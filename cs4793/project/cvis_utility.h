#include <cv.h>
#include<highgui.h>
#include<imgproc.hpp>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <stdexcept>
#if !defined(__JEL_CVIS_UTILITY_HEADER__)
#define __JEL_CVIS_UTILITY_HEADER__

namespace jel {
	__declspec(dllexport) void createAndShow(const char*, cv::Mat&, int = 1);
	__declspec(dllexport) void writeGrayImg(const char*, cv::Mat&);
	__declspec(dllexport) void plotLines(cv::Mat&, cv::vector<cv::Vec2f>&);
	__declspec(dllexport) void printMatrix(cv::Mat&, int = 2, int = 5);
}

#if !defined(__JEL_CVIS_UTILITY_CPP__)
//#include "cvis_utility.cpp"
#endif

#endif
