#ifndef INTERFACE_DATA_HPP
#define INTERFACE_DATA_HPP

#include <queue>
#include <mutex>

#include <cv.h>
#include <cstdint>

#include "common/defs.hpp"
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

	std::array<cv::Mat, NUM_IMAGES> image;
	std::array<uint32_t, NUM_IMAGES> imageID;

	std::array<bool, NUM_VPIDS> run_vision_process;

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

