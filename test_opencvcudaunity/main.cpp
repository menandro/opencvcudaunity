#include <opencvcudaunity/opencvcudaunity.h>
#include <iostream>

int main() {
	Ocu * ocu = new Ocu();
	ocu->initCuda(640, 480, 4);
	cv::VideoCapture webcam;
	if (!webcam.open(0))
		return 0;

	cv::Mat input, input3;
	cv::Mat output = cv::Mat(480, 640, CV_8UC4);
	
	while (true) {
		char pressed = cv::waitKey(10);
		if (pressed == 27) break;

		webcam >> input3;
		cv::cvtColor(input3, input, cv::COLOR_BGR2BGRA, 4);
		if (input.empty()) break;
		ocu->blurCuda((unsigned char*)input.ptr(), (unsigned char*)output.ptr());
		cv::imshow("input", input);
		cv::imshow("output", output);
	}
	cv::waitKey();
	return 0;
}