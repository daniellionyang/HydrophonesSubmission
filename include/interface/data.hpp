#ifndef INTERFACE_DATA_HPP
#define INTERFACE_DATA_HPP

#include <queue>
#include <mutex>

#include <cv.h>
#include <cstdint>

#include "common/matrix.hpp"
#include "common/state.hpp"
#include "model/evidence.hpp"

class Data
{
public:
	bool lock();
	bool unlock();

	State state;
	uint32_t stateID = 0;

	cv::Mat imageFront;
	uint32_t imageFrontID = 0;
	cv::Mat imageDown;
	uint32_t imageDownID = 0;

	Matrix model;
	uint32_t modelID = 0;

	std::queue<Evidence> evidence;

	State desiredState;
	bool setState = false;
	bool drop = false;
	bool grab = false;
	bool release = false;
	char shoot = 0;

private:
	std::mutex mutex;
};

#endif

