#ifndef MISSION_GOAL_HPP
#define MISSION_GOAL_HPP

#include <functional>
#include <vector>

#include "common/state.hpp"

class Goal
{
public:
	Goal(FILE*);

	void write(FILE*);

	State location(const Matrix&) const;

	float value() const;
	float time() const;
	float certainty() const;

	bool run(FILE*, FILE*);

private:
	float m_value;
	float m_time;
	float m_certainty;

	float m_time_limit;

	Matrix m_loc_transform;
	Matrix m_loc_offset;

	std::vector<std::function<bool(FILE*, FILE*)>> m_actions;
};

#endif

