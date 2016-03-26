#include "image/image.hpp"

#include <iostream>

#include <opencv2/highgui/highgui.hpp>

int process(std::istream& in, FILE* out, std::ostream& err)
{
	bool quit = false;
	while (!quit)
	{
		std::string filename;
		in >> filename;
		auto img = cv::imread(filename);
		if (img.data != NULL) imageWrite(out, img);
		else err << "error: failed to open file '" << filename << "'\n";

		int c = in.peek();
		if (c == EOF) quit = true;
	}
	return 0;
}

int main()
{
	return process(std::cin, stdout, std::cerr);
}

