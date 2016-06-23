#ifndef COMMON_STATE_HPP
#define COMMON_STATE_HPP

#include <cstddef>
#include <cstdio>

#include "common/matrix.hpp"

struct SubState
{
	SubState(float, float, float, float, float, float);
	SubState(FILE* in);
	
	void write(FILE* out) const;
	
	float x, y, depth, yaw, pitch, roll;
};

class State
{
public:
	State() noexcept;
	State(FILE*) noexcept;
	State(float, float, float, float yaw = 0, float pitch = 0, float roll = 0) noexcept;
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

	float distanceTo(const State&) const;

private:
	float
		m_x,   m_y,     m_depth,
		m_yaw, m_pitch, m_roll
	;
};

#endif

