#include "interface/data.hpp"

#include "interface/config.hpp"

Data::Data() :
	stateID(0),
	imageID({}),
	modelID(0),
	alive(false),
	setState(false),
	send_line(std::queue<Line>{}),
	drop(false),
	grab(false),
	release(false),
	shoot(false),
	flags({}),
	model(initialModel)
{
}

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

