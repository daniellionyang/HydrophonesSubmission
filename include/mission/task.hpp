#ifndef MISSION_TASK_HPP
#define MISSION_TASK_HPP

#include "model/matrix.hpp"

class Task
{
public:
	Task(FILE*);

	void write(FILE*);

	Matrix location(const Matrix&) const;

	float value() const;
	float time() const;
	float certainty() const;

	bool run();

private:
	float m_value;
	float m_time;
	float m_certainty;

	float m_time_limit;

	Matrix m_loc_transform;
	Matrix m_loc_offset;
};

#endif

