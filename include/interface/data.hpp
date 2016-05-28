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
	Data();

	bool lock();
	bool unlock();

	State state;
	uint32_t stateID;

	cv::Mat imageFront;
	uint32_t imageFrontID;
	cv::Mat imageDown;
	uint32_t imageDownID;

	Matrix model;
	uint32_t modelID;

	std::queue<Evidence> evidence;

	State desiredState;
	bool setState;
	bool drop;
	bool grab;
	bool release;
	char shoot;

private:
	std::mutex mutex;
};

#endif

