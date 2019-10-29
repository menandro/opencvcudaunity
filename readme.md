# Template for C++ Plugin (with OpenCV and CUDA) for Unity

## Requirements
* Tested on OpenCV 4.1.1
* CUDA 10.1
* Unity 2019.2.10f1

## Building Instructions
This repository contains:
* Unity/UnityProject - Sample Unity project with simple script, which reads the plugin (DllTest.cs). The script opens a webcam texture and displayed on one of the cubes in scene. It then processes the image (BlurCuda) and displays the output on the other cube.
http://b2.cvl.iis.u-tokyo.ac.jp/~roxas/opencvcudaunity.png)

* dllhook - .dll project, which hooks the needed functions from opencvcudaunity to Unity.
* opencvcudaunity - .lib project, where all the functions are defined. 
* test_opencvcudaunity - Win32 project to test the opencvcudaunity

OpenCV library paths are defined opencvcudaunity.h. The default location is in "D:/dev/lib64". Modify this to point to your OpenCV installation.

CUDA library path is also defined in opencvcudaunity.h. The default installation from NVIDIA installer is "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.1/lib/x64/".

## License
This project is licensed under the MIT license

## Author
Menandro Roxas, 3D Vision Laboratory (Oishi Laboratory), Institute of Industrial Science, The University of Tokyo