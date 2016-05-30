#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv.h>
#include <iostream>
#include <vector>
#include <typeinfo>

enum BouyIndices
{
	RX = 0,
	RY,
	RZ,
	GX,
	GY,
	GZ,
	YX,
	YY,
	YZ,
};

const float cropx = 1.0;
const float cropy = 1.0;
const float offset = 0.9 * (1 - cropy);
const float scalex = 0.2;
const float scaley = 0.2;
const int diffDist = 8;
