#include "interface/data.hpp"

#include "interface/config.hpp"

Data::Data() :
	stateID(0),
	imageID({}),
	modelID(0),
	setState(false),
	drop(false),
	grab(false),
	release(false),
	shoot(false),
	flags({}),
	model(initialModel())
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

