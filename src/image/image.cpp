#include "image/image.hpp"

#include <thread>
#include <chrono>
#include <regex>
#include <string>
#include <sstream>

cv::Mat imageRead(FILE* in)
{
	std::regex header(R"regex(i\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+\\)regex", std::regex::optimize);

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
			int rows, cols, size, mult, type;
			std::stringstream str;
			str << match[1] << ' ' << match[2] << ' ' << match[3] << ' ' << match[4];
			str >> rows >> cols >> size >> mult;
			switch(size + 10*mult)
			{
			case 11:
				type = CV_8UC1;
				break;
			case 12:
				type = CV_16UC1;
				break;
			case 14:
				type = CV_32FC1;
				break;
			case 18:
				type = CV_64FC1;
				break;
			case 31:
				type = CV_8UC3;
				break;
			case 32:
				type = CV_16UC3;
				break;
			case 34:
				type = CV_32FC3;
				break;
			case 38:
				type = CV_64FC3;
				break;
			default:
				type = CV_8UC3;
			}
			cv::Mat image(rows, cols, type);
			fread(image.ptr(), size, mult * rows * cols, in);
			return image;
		}
	}
	return cv::Mat(32, 32, CV_8UC3); // should never get here
}

void imageWrite(FILE* out, const cv::Mat& image)
{
	int size = image.elemSize();
	int mult = image.channels();
	fprintf(out, "i %i %i %i %i\n\\", image.rows, image.cols, size, mult);
	fwrite(image.ptr(), size, mult * image.rows * image.cols, out);
	fprintf(out, "\n");
	fflush(out);
}

