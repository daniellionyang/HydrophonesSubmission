#include <vector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv.h>

#include "vision/vision.hpp"

#include "common/defs.hpp"
#include "vision/config.hpp"
#include "image/image.hpp"

//Turns the mat into a diffmap (make each pixel the difference between it and its neighbors)
//Useful because the water near the top usually looks like the green buoys near the bottom
cv::Mat generateDiffMap(cv::Mat& img, int diff, bool bigger)
{
	cv::Mat diffMap = cv::Mat(img.size(), CV_32F, cv::Scalar(0));

	float* ip = img.ptr<float>();
	float* op = diffMap.ptr<float>();

	for (int c = diff; c < img.cols - diff; c++)
	{
		for (int r = diff; r < img.rows - diff; r++)
		{
			// make the value equal to how much it stands out from its\
				horizontal or vertical neighbors, whichever is less
			float vert = (2*ip[(r*img.cols+c)]-ip[((r-diff)*img.cols+c)]-ip[((r+diff)*img.cols+c)]);
			float hori = (2*ip[(r*img.cols+c)]-ip[(r*img.cols+c+diff)]-ip[(r*img.cols+c-diff)]);
			float weak = (std::abs(vert) < std::abs(hori)) ? vert : hori;
			float strong = (std::abs(vert) > std::abs(hori)) ? vert : hori;
			if(bigger)
			{
				op[r*img.cols+c] = strong;
			}
			else
			{
				op[r*img.cols+c] = weak;
			}
		}
	}
 
	return diffMap;
}

cv::Mat scaleIntensity(const cv::Mat& img)
{
	const float* iptr = img.ptr<float>();

	cv::Mat res(img.size(), CV_32F);
	float* rptr = res.ptr<float>();

	float min = 9999999, max = -9999999;
	for (size_t i = 0; i < img.rows * img.cols; i++)
	{
		if (iptr[i] < min) min = iptr[i];
		if (iptr[i] > max) max = iptr[i];
	}

	float range = max - min;

	for (size_t i = 0; i < img.rows * img.cols; i++)
		rptr[i] = (iptr[i] - min) / range;

	return res;
}

cv::Mat colorize(cv::Mat& img, std::function<float(int, int, int)> func)
{
	cv::Mat output(img.rows, img.cols, CV_32F);

	uchar* ptr = img.ptr();
	float* out = output.ptr<float>();
	
	for(int r = 0; r < img.rows; r++)
	{
		for(int c = 0; c < img.cols; c++)
		{
			out[r*img.cols+c] = func(
							ptr[3*(r*img.cols+c)],
							ptr[3*(r*img.cols+c)+1],
							ptr[3*(r*img.cols+c)+2]);
		}
	}
	return output;
}
