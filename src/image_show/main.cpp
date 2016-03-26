#include "image/image.hpp"

#include <iostream>

#include <opencv2/highgui/highgui.hpp>

int process(FILE* in, FILE* out, FILE* err)
{
	bool quit = false;
	while (!quit)
	{
		auto img = imageRead(in);
		cv::imshow("image_show", img);
		cv::waitKey(10);

		int c = fgetc(in);
		if (c == EOF) quit = true;
		else ungetc(c, in);
	}
	return 0;
}

int main()
{
	return process(stdin, stdout, stderr);
}

