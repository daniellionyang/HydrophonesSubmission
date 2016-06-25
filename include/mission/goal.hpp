#ifndef MISSION_GOAL_HPP
#define MISSION_GOAL_HPP

#include <vector>

#include "common/matrix.hpp"
#include "common/state.hpp"
#include "mission/action.hpp"

class Goal
{
public:
	Goal(float, float, int, int, int, float, float, float, float, std::vector<Action>);

	Goal(FILE*);

	size_t write(FILE*);

	float value() const;
	float time() const;
	float mindist() const;

	State location(const Matrix& model) const;

	bool run(FILE*, FILE*);

private:
	float m_value;
	float m_time;
	float m_mindist;

	int   m_xi, m_yi, m_di;
	float m_xo, m_yo, m_do;

	std::vector<Action> m_actions;
};

#endif

