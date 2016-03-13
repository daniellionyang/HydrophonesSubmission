#include "connection.hpp"

Connection::Connection(FILE* in, FILE* out, std::function<void(FILE*, FILE*, Data*)> function) :
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

