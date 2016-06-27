#include <vector>
#include <functional>
#include <algorithm>
#include <thread>
#include <chrono>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv.h>

#include "common/defs.hpp"
#include "vision/config.hpp"
#include "vision/vision.hpp"
#include "image/image.hpp"

struct Buoy
{
	size_t x_idx, y_idx, d_idx;
	float color[3];
	std::function<float(float, float, float)> filter;
};

std::vector<Buoy> buoys =
{
	{
		M_RBUOY_X, M_RBUOY_Y, M_RBUOY_D, {0,0,1},
		[](float r, float g, float b){ return .7*r/(g+.001) - 1.20*g/(b+.001)-(g+b)*0.01; }
//		[](float r, float g, float b){ return r; }
	},
	{
		M_GBUOY_X, M_GBUOY_Y, M_GBUOY_D, {0,1,0},
		[](float r, float g, float b){ return (g+0.4*r)/(b+0.7*r+3.01)-0.004*r; }
//		[](float r, float g, float b){ return g; }
	},
	{
		M_YBUOY_X, M_YBUOY_Y, M_YBUOY_D, {0,1,1},
		[](float r, float g, float b){ return .5+(r+g-b)/4; }
//		[](float r, float g, float b){ return b; }
	},
};

const float cropx = 1.0;
const float cropy = 1.0;
const float offset = 0.9 * (1 - cropy);
const float scalex = 0.2;
const float scaley = 0.2;
const int diffDist = 8;
const float buoyWidth = .2;

//Creates an equalized distribution of certain colors
//Read more at http://docs.opencv.org/2.4/doc/tutorials/imgproc/histograms/histogram_equalization/histogram_equalization.html
cv::Mat equalColorHist(cv::Mat& img, bool red, bool green, bool blue)
{
	std::vector<cv::Mat> channels;
	cv::split(img, channels);

	if(blue)
	{
		cv::equalizeHist(channels[0], channels[0]);
	}
	if(green)
	{
		cv::equalizeHist(channels[1], channels[1]);
	}
	if(red)
	{
		cv::equalizeHist(channels[2], channels[2]);
	}

	cv::Mat result;
	cv::merge(channels, result);
	return result;
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

int main(int argc, char** argv)
{
	FILE* in = stdin;
	FILE* out = stdout;
	FILE* log = stderr;

	while(true)
	{
		//Obtain image from the front camera.
		cv::Mat image = imageRead(in);

		if(!image.data)
		{
			fprintf(out, "0\n");
			continue;
		}

		//Crop and resize image
		cv::resize(image(cv::Rect(image.cols*(1-cropx)/2, image.rows*(1-cropy-offset)/2, 
			image.cols*cropx, image.rows*cropy)), image, 
			cv::Size(image.cols*cropx*scalex, image.rows*cropy*scaley));
		size_t rows = image.rows;
		size_t cols = image.cols;
		unsigned char* ptr = image.ptr();

		fprintf(out, "%u\n", buoys.size());

		cv::Mat imgP;
		image.copyTo(imgP);

		for (auto b : buoys)
		{
			cv::Mat imgF;
			imgF.create(rows, cols, CV_32F);
			float* fptr = imgF.ptr<float>();

			for (size_t i = 0; i < rows * cols; i++)
				fptr[i] = b.filter(ptr[3*i+2]/256.f, ptr[3*i+1]/256.f, ptr[3*i+0]/256.f);

			auto imgD = generateDiffMap(imgF, diffDist);

			cv::Mat imgB = cv::Mat(imgD.size(), CV_32F, cv::Scalar(0));
			cv::blur(imgD, imgB, cv::Size(3, 3));

			cv::Mat imgS = scaleIntensity(imgD);

			auto img = imgS;

			/*
			auto imgPB = img;
			cv::Mat imgP(imgPB.size(), CV_8UC3);
			for (size_t i = 0; i < imgPB.rows*imgPB.cols; i++)
			{
				int value = imgPB.ptr<float>()[i] * 255;
				imgP.ptr()[3*i] = b.color[0]*value;
				imgP.ptr()[3*i+1] = b.color[1]*value;
				imgP.ptr()[3*i+2] = b.color[2]*value;
			}
			imageWrite(log, imgP);
			*/

			float max = -1000000;
			int mr = 0;
			int mc = 0;
			for (int r = 0; r < rows; r++)
				for (int c = 0; c < cols; c++)
					if (img.at<float>(r, c) > max)
					{
						max = img.at<float>(r, c);
						mr = r;
						mc = c;
					}

			auto visited = std::vector<std::vector<bool> >(img.rows, std::vector<bool>(img.cols, false));
			float size = std::sqrt(floodFill(img, visited, mr, mc, .9 * max));

			float theta = fhFOV * static_cast<float>(mc - img.cols/2) / img.cols;
			float phi = fvFOV * static_cast<float>(mr - img.rows/2) / img.rows;
			float dist = buoyWidth/2 / std::tan(size/img.cols * fhFOV / 2 * 2*M_PI);

			fprintf(out, "%zu %zu %zu\n%f %f %f\n",
				b.x_idx, b.y_idx, b.d_idx,
				theta,   phi,     dist
			);

			cv::ellipse(imgP, cv::Point(mr, mc), cv::Size(4, 4), 0, 0, 360, cv::Scalar(255*b.color[0], 255*b.color[1], 255*b.color[2]));
		}

		imageWrite(log, imgP);
	}
		 
	return 0;
}
