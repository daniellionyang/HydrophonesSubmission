#include "mission/action.hpp"

std::function<bool(FILE*, FILE*)> getaction(FILE* config)
{
	int action;
	fscanf(config, "%i", &action);
	switch(action)
	{
	default:	
		return [&] (FILE* a, FILE* b){return false;};
	}
}

