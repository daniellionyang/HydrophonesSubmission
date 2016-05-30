#include <thread>

#include "interface/config.hpp"
#include "interface/functions.hpp"
#include "interface/data.hpp"

int main()
{
	Data data;

	std::thread threads[256];
	size_t numThreads = 0;

	for (auto c : defaultConnections())
		threads[numThreads++] = std::thread(c.function, &data);

	for (size_t i = 0; i < numThreads; i++)
		threads[i].join();

	return 0;
}

