#ifndef INTERFACE_CONNECTION_HPP
#define INTERFACE_CONNECTION_HPP

#include <functional>
#include <cstdio>
#include <thread>

#include "interface/data.hpp"

class Connection
{
public:
	Connection(FILE*, FILE*, std::function<bool(FILE*, FILE*, Data*)>, Data*);
	~Connection();

private:
	FILE* in;
	FILE* out;
	std::function<bool(FILE*, FILE*, Data*)> function;
	Data* data;
	std::thread thread;
};

#endif

