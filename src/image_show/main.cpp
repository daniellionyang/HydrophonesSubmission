#include "image/image.hpp"

#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int process(FILE* in, FILE* out, FILE* err, float scale, int wait)
{
	bool quit = false;
	while (!quit)
	{
		auto img = imageRead(in);
		cv::resize(img, img, cv::Size(img.cols * scale, img.rows * scale), 0, 0, cv::INTER_NEAREST);
		cv::imshow("image_show", img);
		cv::waitKey(10);

		int c = fgetc(in);
		if (c == EOF) quit = true;
		else ungetc(c, in);

		std::this_thread::sleep_for(std::chrono::milliseconds(wait));
	}
	return 0;
}

int main(int argc, char** argv)
{
	float scale = 1;
	int wait = 0;
	if (argc >= 2) std::stringstream(argv[1]) >> scale;
	if (argc >= 3) std::stringstream(argv[2]) >> wait;

	return process(stdin, stdout, stderr, scale, wait);
}

