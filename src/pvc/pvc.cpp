#include <vector>
#include <algorithm>
#include <functional>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv.h>

#include "common/defs.hpp"
#include "common/config.hpp"
#include "vision/config.hpp"
#include "vision/vision.hpp"
#include "image/image.hpp"

const float pvcWidth = 2;
const float minDist = 30;

std::vector<cv::Point2f> flatten(cv::Mat& img)
{
	std::vector<cv::Point2f> points;

	float* ptr = img.ptr<float>();
	int i = 1;

	for(int c = 0; c < img.cols; c++)
	{
		double sum = 0;
		for(int r = 0; r < img.rows; r++)
		{
			sum += ptr[r*img.cols + c];
		}
		points.push_back(cv::Point2f(i, sum/img.rows));
		i++;
	}

	return points;
}

float getYellow(float b, float g, float r)
{
	return (g - b) * 5 + r;
}

bool comparePoints(cv::Point2f& a, cv::Point2f& b)
{
	return a.y > b.y;
}

std::vector<cv::Point2f> bestPoints(std::vector<cv::Point2f> points, int num)
{
	std::vector<cv::Point2f> top;
	std::sort(points.begin(), points.end(), comparePoints);

	top.push_back(points[0]);
	int j = 1;
	while(top.size() < num)
	{
		bool fail = false;
		for(int k = 0; k < top.size(); k++)
		{
			if(points[j].x - top[k].x < minDist && points[j].x - top[k].x > -minDist)
			{
				j++; fail = true;
				if(j >= points.size()) return top;
				break;
			}
		}
		if(!fail) {top.push_back(points[j]); j++;}
	}
	
	return top;
}

cv::Mat dispPoints(cv::Mat img, std::vector<cv::Point2f> pts, int cwidth)
{
	cv::Mat disp(img);
	for(cv::Point2f p : pts)
	{
		cv::ellipse(disp, cv::Point(p.x, cwidth), cv::Size(cwidth, cwidth), 0, 0, 360, cv::Scalar(0, 0, 255));
	}
	return disp;
}

void pResults(FILE* in, FILE* out, std::vector<cv::Point2f>& pts, int cols)
{
	fprintf(out, "%i\n", pts.size() == 2 ? 1 : 0);

	if(pts.size() != 2) {return;}

	float theta = fhFOV * (pts[0].x + pts[1].x - cols) / (2*cols);
	float dist = pvcWidth/2 / std::tan((pts[0].x - pts[1].x)/cols * fhFOV / 2 * 2*M_PI);

	fprintf(out, "%zu %zu -1\n%f %f %f\n",
		M_GATE_X, M_GATE_Y,
		theta, constants.get(C_PVC_D), dist);
}

int main(int argc, char** argv)
{
	FILE* in = stdin;
	FILE* out = stdout;
	FILE* err = stderr;

	while(true)
	{
		cv::Mat img = imageRead(in); //Read image

		cv::Mat diff = generateDiffMap(img, 8, true);

		cv::Mat yellower = colorize(diff, getYellow); //Enhance to make pvc show up
		
		std::vector<cv::Point2f> pts = bestPoints(flatten(yellower), 2);
		
		imageWrite(err, dispPoints(scaleIntensity(diff), pts, 5));
		pResults(in, out, pts, img.cols);
	}
}
