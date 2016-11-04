#include <cv.h>
#include<highgui.h>
#include<imgproc.hpp>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <stdexcept>
#if !defined(__JEL_GAUSSIAN_HEADER__)
#define __JEL_GAUSSIAN_HEADER__


namespace jel {
	const double PI = 3.1415926535897932385;
	__declspec(dllexport) void gausssian_kernel(cv::Mat&, int, double);

}

#endif