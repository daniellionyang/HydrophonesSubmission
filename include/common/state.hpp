#ifndef COMMON_STATE_HPP
#define COMMON_STATE_HPP

#include <cstddef>
#include <cstdio>

#include "common/matrix.hpp"

class State
{
public:
	State();
	State(FILE*);
	State(float, float, float, float, float, float);
	void write(FILE*) const;

	float x() const;
	float y() const;
	float depth() const;
	float yaw() const;
	float pitch() const;
	float roll() const;

	float setX(float);
	float setY(float);
	float setDepth(float);
	float setYaw(float);
	float setPitch(float);
	float setRoll(float);

private:
	float
		m_x,   m_y,     m_depth,
		m_yaw, m_pitch, m_roll
	;
};

#endif

