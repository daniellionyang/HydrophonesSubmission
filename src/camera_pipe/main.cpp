#include <cstdio>
#include <thread>
#include <chrono>
#include <mutex>

#include "image/image.hpp"

int main(int argc, char** argv)
{
	if (argc < 2) return fprintf(stderr, "error: no pipe specified\n"), 1;

	FILE* camera = fopen(argv[1], "r");

	std::mutex lock;
	cv::Mat image;

	// read images
	auto r = std::thread([](FILE* camera, cv::Mat* image, std::mutex* lock)
	{
		bool quit = false;

		while (!quit)
		{
			auto img = imageRead(camera);
			lock->lock();
				*image = std::move(img);
			lock->unlock();
		}
	}, camera, &image, &lock);

	// send image on request
	auto w = std::thread([](FILE* in, FILE* out, cv::Mat* image)
	{
		bool quit = false;
		while (!quit)
		{
			// wait for image request
			int c = fgetc(in);
			switch (c)
			{
				case 'i':
					imageWrite(out, *image);
					break;
				case 'q':
				case EOF:
					quit = true;
					break;
			}

			// wait a bit
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}, stdin, stdout, &image);

	r.join();
	w.join();

	return 0;
}

