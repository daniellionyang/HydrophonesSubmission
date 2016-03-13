#include "interface/connection.hpp"

Connection::Connection(FILE* in, FILE* out, std::function<bool(FILE*, FILE*, Data*)> function, Data* data) :
	in(in),
	out(out),
	function(function),
	data(data),
	thread([&]()
	{
		while (function(in, out, data));
	})
{
}

Connection::~Connection()
{
	thread.join();
}

