#include "interface/data.hpp"

#include "interface/config.hpp"

Data::Data() :
	stateID(0),
	imageFrontID(0),
	imageDownID(0),
	modelID(0),
	setState(false),
	drop(false),
	grab(false),
	release(false),
	shoot(false),
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

