#include <iostream>
#include <thread>

#include "interface/functions.hpp"

int process(std::istream& in, std::ostream& out)
{
	std::function<bool(const std::string, const std::string, Data*)> functions[] = {
		control,
		mission,
		modeling,
		camera_f,
		camera_d
	};

	Data data;

	std::thread threads[256];
	size_t numThreads = 0;

	bool quit = false;
	while (!quit)
	{
		std::string in_name, out_name;
		int func_idx;

		in >> in_name >> out_name >> func_idx;

		if (func_idx < 0) break;

		if (!in.good())
		{
			out << "failed to parse\n";
			continue;
		}

		if (func_idx > sizeof(functions) / sizeof(functions[0]))
		{
			out << "function index too high\n";
			continue;
		}

		threads[numThreads++] = std::thread(functions[func_idx], in_name, out_name, &data);
		out << "opened thread\n";
	}

	for (size_t i = 0; i < numThreads; i++)
	{
		threads[i].join();
	}

	return 0;
}

int main()
{
	return process(std::cin, std::cout);
}

