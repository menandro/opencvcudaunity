#include "opencvcudaunity.h"

// Initialize Cuda containers with specified width, height, and channels
// so that we don't have to allocate memory every call
int Ocu::initCuda(int width, int height, int channels) {
	this->width = width;
	this->height = height;
	this->channels = channels;

	// Compute stride based on width and stride alignment
	int m = this->StrideAlignment;
	int mod = this->width % m;
	if (mod)
		stride = this->width + m - mod;
	else
		stride = this->width;

	this->dataSize = stride * height * channels * sizeof(unsigned char);
	checkCudaErrors(cudaMalloc(&d_input, dataSize));
	checkCudaErrors(cudaMalloc(&d_output, dataSize));
	return 0;
}

int Ocu::blurCuda(unsigned char *input, unsigned char * output) {
	// Copy image from CPU(host) to GPU(device)
	checkCudaErrors(cudaMemcpy(d_input, input, dataSize, cudaMemcpyHostToDevice));

	// Blur
	Blur(d_input, d_output, width, height, stride);

	// Copy results from GPU to CPU
	checkCudaErrors(cudaMemcpy(output, d_output, dataSize, cudaMemcpyDeviceToHost));

	return 0;
}

// *******************************
// Kernel and Kernel Function Call
__global__
void BlurKernel(uchar4* input, uchar4 * output, int width, int height, int stride)
{
	const int ix = threadIdx.x + blockIdx.x * blockDim.x;
	const int iy = threadIdx.y + blockIdx.y * blockDim.y;

	const int pos = ix + iy * stride;

	int4 sum = make_int4(0, 0, 0, 0);
	int total = 0;
	if (ix >= width || iy >= height) return;
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			int col = (ix + i - 2);
			int row = (iy + j - 2);
			if ((col >= 0) && (col < width) && (row >= 0) && (row < height)) {
				sum.w += input[col + stride * row].w;
				sum.x += input[col + stride * row].x;
				sum.y += input[col + stride * row].y;
				sum.z += input[col + stride * row].z;
				total++;
			}
		}
	}
	output[pos].w = (uchar)(sum.w / total);
	output[pos].x = (uchar)(sum.x / total);
	output[pos].y = (uchar)(sum.y / total);
	output[pos].z = (uchar)(sum.z / total);
}

void Ocu::Blur(uchar4* input, uchar4 * output, int w, int h, int s) {
	dim3 threads(BlockWidth, BlockHeight);
	int blocksx = (w + threads.x - 1) / threads.x;
	int blocksy = (h + threads.y - 1) / threads.y;
	dim3 blocks(blocksx, blocksy);

	BlurKernel << <blocks, threads >> > (input, output, w, h, s);
}