#ifndef MISSION_GOAL_HPP
#define MISSION_GOAL_HPP

#include <functional>
#include <vector>

#include "common/matrix.hpp"
#include "common/state.hpp"
#include "mission/action.hpp"

class Goal
{
public:
	Goal(FILE*);

	void write(FILE*);

	State location(const Matrix&) const;

	float value() const;
	float time() const;
	float certainty() const;
	void failed() {fails++;};

	bool run(FILE*, FILE*);

private:
	float m_value;
	float m_time;
	float m_certainty;

	float m_time_limit;
	int fails;

	int m_offset;

	std::vector<Action*> m_actions;
};

#endif

