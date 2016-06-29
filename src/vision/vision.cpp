#include "vision/vision.hpp"

#include "vision/config.hpp"

float hAngle(const cv::Mat& img, float cols)
{
	return fhFOV * cols / img.cols;
}

float vAngle(const cv::Mat& img, float rows)
{
	return fvFOV * rows / img.rows;
}

cv::Mat filter(const cv::Mat& img, std::function<float(float, float, float)> f)
{
	cv::Mat res(img.size(), CV_32F);

	for (size_t row = 0; row < img.rows; row++)
		for (size_t col = 0; col < img.cols; col++)
			res.at<float>(row, col) = f(img.at<cv::Vec3b>(row, col)[2], img.at<cv::Vec3b>(row, col)[1], img.at<cv::Vec3b>(row, col)[0]);

	return res;
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

int floodFill(const cv::Mat& img, std::vector<std::vector<bool> >& visited, int row, int col, float threshold)
{
	if (row < 0 || col < 0 || row >= img.rows || col >= img.cols || visited.at(row).at(col) || img.at<float>(row, col) < threshold)
		return 0;
	else
	{
		visited.at(row).at(col) = true;
		return 1 +
			floodFill(img, visited, row + 1, col, threshold) +
			floodFill(img, visited, row - 1, col, threshold) +
			floodFill(img, visited, row, col + 1, threshold) +
			floodFill(img, visited, row, col - 1, threshold);
	}
}

