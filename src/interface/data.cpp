#include "interface/data.hpp"

bool Data::lock()
{
	mutex.lock();
	return true;
}

bool Data::unlock()
{
	mutex.unlock();
	return true;
}

