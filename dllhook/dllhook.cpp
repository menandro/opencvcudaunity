#include "dllhook.h"

extern "C" __declspec(dllexport) Ocu* Create() {
	Ocu* ocu = new Ocu();
	return ocu;
}

extern "C" __declspec(dllexport) void Init(Ocu* ocu, int width, int height, int channels) {
	ocu->initCuda(width, height, channels);
}

extern "C" __declspec(dllexport) void BlurCuda(Ocu* ocu, unsigned char * input, unsigned char * output) {
	ocu->blurCuda(input, output);
}