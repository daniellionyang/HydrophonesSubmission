#include "image/image.hpp"

cv::Mat imageRead(FILE* in)
{
	char c;
	fscanf(in, "%c", %c);
	if(c == 'i')
	{
		int rows, cols;
		fscanf(in, "%i %i", &rows, &cols);
		cv::Mat image(rows, cols, CV_8UC3);
		fscanf(in, " \\");
		fread(image.ptr(), sizeof(char), 3 * rows * cols, in);
		return image;
	}	
	return cv::Mat(32, 32, CV_8UC3);
}

void imageWrite(FILE* out, const cv::Mat& image)
{
	fprintf(out, "i %i %i\n\\", image.rows, image.cols);
	fwrite(image.ptr(), sizeof(char), 3 * image.rows * image.cols, out);
}

