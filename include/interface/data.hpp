#ifndef INTERFACE_DATA_HPP
#define INTERFACE_DATA_HPP

#include <mutex>
#include <cv.h>
#include <cstdint>

class Data
{
public:
	bool lock();
	bool unlock();

	cv::Mat image;
	uint32_t imageID = 0;

private:
	std::mutex mutex;
};

#endif

