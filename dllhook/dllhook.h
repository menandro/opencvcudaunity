#pragma once

#include <opencvcudaunity/opencvcudaunity.h>

// To handle classes, class pointer needs to be initialized and referenced in every call
extern "C" __declspec(dllexport) Ocu* Create();
extern "C" __declspec(dllexport) void Init(Ocu* ocu, int width, int height, int channels);
extern "C" __declspec(dllexport) void BlurCuda(Ocu* ocu, unsigned char* input, unsigned char* output);