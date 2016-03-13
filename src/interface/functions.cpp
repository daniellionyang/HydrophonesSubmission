#include "interface/functions.hpp"

#include <thread>
#include <chrono>

#include "image/image.hpp"

bool camera(FILE* in, FILE* out, Data* data)
{
	fprintf(out, "i\n"); // request image
	auto img = imageRead(in); // read image

	data->lock();
		data->image = img;
		data->imageID++;
	data->unlock();

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	return true;
}

