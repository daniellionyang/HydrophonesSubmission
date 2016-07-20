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
#include "common/observation.hpp"
#include "vision/config.hpp"
#include "vision/vision.hpp"
#include "vision/blob_detection.hpp"
#include "image/image.hpp"

auto yfilter = nnFilter(
{
	{
		{ 38.63473129, -56.2016449 ,  17.81845284},
		{20.76142311, -10.47163677, -32.31459427},
		{0.35822314,  -5.96877956,   0.24339797},
		{0.52314246,   8.56726265,  70.04584503},
	},
	{
		{19.88062477},
		{24.8707695},
		{-3.14199758},
		{-37.13335037},
	},
	{{-69.49597931, -13.72448921,  -0.77971619, -62.5725441}},
	{{62.55046463}},
});

auto ofilter = nnFilter(
{
	{
		{-122.57562256,  -34.30429459,  -58.89888382},
		{8.42154789,  119.62509155,  -31.02238846},
		{-127.1678009 ,  217.79257202, -116.3327179},
		{ 7.98526287,  -99.36182404,   97.6957016 },
	},
	{
		{50.17668533},
		{-58.20920563},
		{-43.98231506},
		{9.47482681},
	},
	{{ -84.03649139,  -51.35709381,  -73.33837128, -110.05463409}},
	{{78.57619476}},
});

const float cropx = 1.0;
const float cropy = 1.0;
const float offset = 0.9 * (1 - cropy);
const float scalex = 256;
const float scaley = 192;
//const float scalex = 0.2;
//const float scaley = 0.2;
const int diffDist = 8;

const float boardHeight = 1;

const float smallHoleHeight = .1778f;
const float largeHoleHeight = .3048f;
const float tlHeight = largeHoleHeight;
const float blHeight = smallHoleHeight;
const float trHeight = smallHoleHeight;
const float brHeight = largeHoleHeight;

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
//			cv::Size(image.cols*cropx*scalex, image.rows*cropy*scaley));
			cv::Size(cropx*scalex, cropy*scaley),
			0, 0,
			cv::INTER_NEAREST
		);
		size_t rows = image.rows;
		size_t cols = image.cols;
		unsigned char* ptr = image.ptr();

		cv::Mat imgB;
		cv::blur(image, imgB, cv::Size(6, 6));

		cv::Mat imgF = filter(imgB, yfilter);

		// fill in gaps
		cv::Mat imgD;
		int dradius = 3;
		cv::dilate(imgF, imgD, cv::getStructuringElement(
			cv::MORPH_RECT,
			cv::Size(2 * dradius + 1, 2 * dradius + 1),
			cv::Point(dradius, dradius)
		));

		cv::Mat imgS = scaleIntensity(imgD);

		auto img = imgS;

		float max = -1000000;
		int mr = 0;
		int mc = 0;
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				if (img.at<float>(r, c) > max)
				{
					max = img.at<float>(r, c);
					mr = r;
					mc = c;
				}
			}
		}

		cv::Mat imgT;
		cv::threshold(imgS, imgT, .5 * max, 1, cv::THRESH_BINARY);
		imgT.convertTo(imgT, CV_8UC1, 255);

		cv::Mat imgO = filter(imgB, ofilter);
		cv::Mat imgE;
		int eradius = 2;
		cv::erode(imgO, imgE, cv::getStructuringElement(
			cv::MORPH_RECT,
			cv::Size(2 * eradius + 1, 2 * eradius + 1),
			cv::Point(eradius, eradius)
		));
		img = imgE;

		float cmax = -1000000;
		int cr = 0;
		int cc = 0;
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				if (img.at<float>(r, c) > cmax)
				{
					cmax = img.at<float>(r, c);
					cr = r;
					cc = c;
				}
			}
		}


/*
		auto imgPB = imgT;
		cv::Mat imgP(imgPB.size(), CV_8UC3);
		for (size_t i = 0; i < imgPB.rows*imgPB.cols; i++)
		{
			int value = imgPB.ptr()[i];
			imgP.ptr()[3*i] = value;
			imgP.ptr()[3*i+1] = value;
			imgP.ptr()[3*i+2] = value;
		}
*/
		cv::Mat imgP;
		image.copyTo(imgP);
//		cv::cvtColor(imgT, imgP, CV_GRAY2BGR);
		cv::circle(imgP, cv::Point(cc, cr), 3, cv::Scalar(0, 127, 255));

		std::vector<Observation> observations;

		// cover
		observations.push_back(
		{
			M_TORP_C_H,
			-1,
			-3,
			static_cast<float>(cc - img.cols/2) / img.cols,
			0,
			.1f
		});
		observations.push_back(
		{
			M_TORP_C_V,
			-1,
			-3,
			static_cast<float>(cr - img.rows/2) / img.rows,
			0,
			.1f
		});

		auto yblobs = blob_detection(imgT);
		// remove blobs not containing highest orange pixel
		yblobs.erase(std::remove_if(yblobs.begin(), yblobs.end(), [=](const Blob b)
		{
			return
				b.max_x < cc ||
				b.min_x > cc ||
				b.max_y < cr ||
				b.min_y > cr ||

				false;
		}), yblobs.end());
		if (yblobs.size() > 0)
		{
			auto board = yblobs.at(0);

			board.drawBlob(imgP, cv::Scalar(0, 255, 255));

			auto points = board.convexHull;
			auto c = board.getCentroid();
			int maxL = board.min_y;
			int maxR = board.min_y;
			int minL = board.max_y;
			int minR = board.max_y;
			for (auto p : points)
			{
				if (p.x > c.x) // right
				{
					if (p.y > maxR) maxR = p.y;
					if (p.y < minR) minR = p.y;
				}
				else // left
				{
					if (p.y > maxL) maxL = p.y;
					if (p.y < minL) minL = p.y;
				}
			}

			float ratio = static_cast<float>(maxR - minR) / (maxL - minL);

			float skew = 0;

			observations.push_back(
			{
				M_TORP_SKEW, -1, -3, skew, 0, .3,
			});

			float theta = fhFOV * static_cast<float>(c.x - img.cols/2) / img.cols;
			float phi = fvFOV * static_cast<float>(c.y - img.rows/2) / img.rows;
			float dist = boardHeight/2 / std::tan(static_cast<float>(board.max_y - board.min_y)/img.rows * fvFOV / 2 * 2*M_PI);

			observations.push_back(
			{
				M_TORP_DIST, 
				-1,
				-3,
				dist,
				0,
				.5,
			});
		}
		else
		{
			observations.push_back(
			{
				M_TORP_DIST, 
				-1,
				-3,
				3,
				0,
				2,
			});
		}
		imageWrite(log, imgP);

		fprintf(out, "%zu\n", observations.size());
		for (auto o : observations)
			o.write(out);
		fflush(out);
	}
		 
	return 0;
}
