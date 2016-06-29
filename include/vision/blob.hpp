#ifndef VISION_BLOB_HPP
#define VISION_BLOB_HPP

#include <set>

#include <cv.h>

struct Blob
{
public:
	Blob(int color, int channels, std::vector<cv::Point> blobPoints, std::vector<cv::Point> perimeter, cv::Mat src);
	// combine two blobs
	Blob(Blob* a, Blob* b, int channels);
	// create from CBlob
	Blob(int color, int channels);
	Blob(const Blob &b);
	
	~Blob();
	int min_x, max_x, min_y, max_y;
	unsigned int area, perimeter;
	float bounding_box_fill;
	int num_channels;
	
	long moment[16];
	long moment_x[16];
	long moment_y[16];	// first moments with respect to x and y axes (y = 0  and x = 0)
	
	int getColor();
	cv::Point getCentroid(int color);
	cv::Point getCentroid();
	float getDensity(int channel);
	float getDensity();
	
	bool overlapsWith(Blob* b);
	void addToThis(Blob* b);
	// does not scale internal points; only use after combing blobs
	void scale(int n);
	
	void drawBlob(cv::Mat img, cv::Scalar color);
	void drawContour(cv::Mat img, cv::Scalar color);
	void drawRotatedRect(cv::Mat img, cv::Scalar color);
	
	std::vector<cv::Point> convexHull;
	cv::RotatedRect minSurroundingRect();
	
	float getConvexHullPerimeter();
	float getConvexHullArea();
	float getHullCircularity();
private:

	void calculateConvexHull(std::vector<cv::Point> points);
	
	std::vector<cv::Vec<float, 2> > rotatePoints(std::vector<cv::Vec<float, 2> > points, cv::Vec<float, 2> unitVec, cv::Vec<float, 2> orthoVec);
	int findNextSide(std::vector<cv::Vec<float, 2> >points, int sidesIndeces[4]);
	float dot(cv::Vec<float, 2> a, cv::Vec<float, 2> b);
	cv::Vec<float, 2> unitVector(cv::Vec<float, 2> v);	
	float magnitude(float x, float y);
};

#endif
