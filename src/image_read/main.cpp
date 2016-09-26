/**
* An image handling class. Writes from cin to stdout, stopping upon end-of-file. 
* Used to convert an image (piped in) to a binary file stream (to be piped out).
*/


#include "image/image.hpp"

#include <iostream>

#include <opencv2/highgui/highgui.hpp>

/**
* Method that writes to a file from an input. Prints user message to err if the input stream is not found.
* @param in the stream to read from
* @param out the file stream to write to
* @param err the stream to write user message to
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

/**
* Calls the process() method with 
* cin for the input stream,
* stdout for the output file stream, 
* cerr for error reporting
* @return 0 upon finishing
* @see process();
*/

int main()
{
	return process(std::cin, stdout, std::cerr);
}

