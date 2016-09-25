/**
* An image handling class. Writes from an image to a file stream.
*/


#include "image/image.hpp"

#include <iostream>

#include <opencv2/highgui/highgui.hpp>

/**
* Method that writes to a file from an input. Prints error message if the input stream is not found.
* @param in the stream to read from
* @param out the file stream to write to
* @param the stream to write user output to
* @return 0 upon finishing
*/

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

