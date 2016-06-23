#ifndef MISSION_ACTION_HPP
#define MISSION_ACTION_HPP

#include <functional>

#include "common/state.hpp"

class Action
{
public:
	template <typename F, typename... A>
	Action(F _function, A... args) :
		m_function(std::bind(_function, std::placeholders::_1, std::placeholders::_2, args...))
	{
	}

	Action(FILE*);
	size_t write(FILE*);

	bool run(FILE*, FILE*);

private:
	std::function<bool(FILE*, FILE*)> m_function;
};


bool wait(FILE*, FILE*, float);
bool moveAbsolute(FILE*, FILE*, const State&, float);
bool moveRelative(FILE*, FILE*, const State&, float);
bool moveDir(FILE*, FILE*, const State&, float);
bool moveModel(FILE*, FILE*, int, int, int, float, float, float, float);
bool moveModelDir(FILE*, FILE*, int, int, int, float, float, float, float);

bool dropInBin(FILE*, FILE*);
bool uncoverBin(FILE*, FILE*);

bool shootInHole(FILE*, FILE*);
bool uncoverHole(FILE*, FILE*);

bool flag(FILE*, FILE*, size_t, float);

#endif

