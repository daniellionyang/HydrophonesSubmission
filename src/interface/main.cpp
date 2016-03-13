#include <iostream>
#include <thread>

#include "interface/connection.hpp"
#include "interface/functions.hpp"

int process(std::istream& in, std::ostream& out)
{
	std::function<bool(FILE*, FILE*, Data*)> functions[] = {camera};

	Data data;

	std::vector<Connection*> connections;

	bool quit = false;
	while (!quit)
	{
		std::string in_name, out_name;
		int func_idx;

		in >> in_name >> out_name >> func_idx;
		if (!in.good())
		{
			out << "failed to parse\n";
			continue;
		}

		FILE* in_file = fopen(in_name.c_str(), "r");
		if (!in_file)
		{
			out << "failed to open input file\n";
			continue;
		}
		FILE* out_file = fopen(out_name.c_str(), "w");
		if (!in_file)
		{
			out << "failed to open output file\n";
			continue;
		}
		if (func_idx > sizeof(functions))
		{
			out << "failed to open output file\n";
			continue;
		}
		
		connections.push_back(new Connection(in_file, out_file, functions[func_idx], &data));
	}

	for (auto c : connections)
		delete c;

	return 0;
}

int main()
{
	return process(std::cin, std::cout);
}

