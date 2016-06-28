#include "image/image.hpp"

#include <thread>
#include <chrono>
#include <regex>
#include <string>
#include <sstream>

cv::Mat imageRead(FILE* in)
{
	std::regex header(R"regex(i\s+(\d+)\s+(\d+)\s+\\)regex", std::regex::optimize);

	std::string buffer = "";
	while (true)
	{
		if (buffer.length() > 64) buffer = buffer.substr(32); // keep buffer relatively small
		int c = fgetc(in);
		if (c == EOF)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			continue;
		}
		buffer += static_cast<char>(c);

		std::smatch match;
		if (std::regex_search(buffer, match, header))
		{
			int rows, cols;
			std::stringstream str;
			str << match[1] << ' ' << match[2];
			str >> rows >> cols;
			cv::Mat image(rows, cols, CV_8UC3);
			fread(image.ptr(), sizeof(char), 3 * rows * cols, in);
			return image;
		}
	}
	return cv::Mat(32, 32, CV_8UC3); // should never get here
}

void imageWrite(FILE* out, const cv::Mat& image)
{
	fprintf(out, "i %i %i\n\\", image.rows, image.cols);
	fwrite(image.ptr(), sizeof(char), 3 * image.rows * image.cols, out);
	fprintf(out, "\n");
	fflush(out);
}

