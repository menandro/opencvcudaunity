#pragma once
#include <opencv2/opencv.hpp>
#include <cuda_runtime.h>
#include <helper_cuda.h>
#include <device_launch_parameters.h>

#define CUDA_LIB_PATH "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.1/lib/x64/"
#pragma comment(lib, CUDA_LIB_PATH "cudart.lib")

#define CV_LIB_PATH "D:/dev/lib64/"
#define LIB_EXT ".lib"

#define CV_VER_NUM CVAUX_STR(CV_MAJOR_VERSION) CVAUX_STR(CV_MINOR_VERSION) CVAUX_STR(CV_SUBMINOR_VERSION)
#pragma comment(lib, CV_LIB_PATH "opencv_core" CV_VER_NUM LIB_EXT)
#pragma comment(lib, CV_LIB_PATH "opencv_highgui" CV_VER_NUM LIB_EXT)
#pragma comment(lib, CV_LIB_PATH "opencv_videoio" CV_VER_NUM LIB_EXT)
#pragma comment(lib, CV_LIB_PATH "opencv_imgproc" CV_VER_NUM LIB_EXT)

class Ocu {
public:
	Ocu() {};
	~Ocu() {};

	int BlockWidth = 32;
	int BlockHeight = 12;
	int StrideAlignment = 32;
	int width;
	int height;
	int channels;
	int stride;
	int dataSize;
	uchar4* d_input;
	uchar4* d_output;
	int initCuda(int width, int height, int channels);
	int blurCuda(unsigned char *input, unsigned char * output);

	// Kernel Function Calls
	void Blur(uchar4 * input, uchar4* output, int w, int h, int s);
};