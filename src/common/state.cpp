#include "common/state.hpp"

#include <cmath>

State::State() noexcept
{
}

State::State(FILE* in) noexcept
{
	float x, y, depth, yaw, pitch, roll;
	fscanf(in, " s %f %f %f %f %f %f",
		&x, &y, &depth, &yaw, &pitch, &roll
	);

	setX(x);
	setY(y);
	setDepth(depth);
	setYaw(yaw);
	setPitch(pitch);
	setRoll(roll);
}

State::State(float x, float y, float depth, float yaw, float pitch, float roll) noexcept :
	m_x(x),
	m_y(y),
	m_depth(depth),
	m_yaw(yaw),
	m_pitch(pitch),
	m_roll(roll)
{
}

void State::write(FILE* out) const
{
	fprintf(out, "s %f %f %f %f %f %f\n",
		x(), y(), depth(), yaw(), pitch(), roll()
	);
	fflush(out);
}

float State::x() const
{
	return m_x;
}

float State::y() const
{
	return m_y;
}

float State::depth() const
{
	return m_depth;
}

float State::yaw() const
{
	return m_yaw;
}

float State::pitch() const
{
	return m_pitch;
}

float State::roll() const
{
	return m_roll;
}

float State::setX(float x)
{
	return m_x = x;
}

float State::setY(float y)
{
	return m_y = y;
}

float State::setDepth(float depth)
{
	return m_depth = depth;
}

float State::setYaw(float yaw)
{
	return m_yaw = yaw;
}

float State::setPitch(float pitch)
{
	return m_pitch = pitch;
}

float State::setRoll(float roll)
{
	return m_roll = roll;
}

float State::distanceTo(const State& to) const
{
	return std::sqrt(
		std::pow(x() - to.x(), 2) +
		std::pow(y() - to.y(), 2) +
		std::pow(depth() - to.depth(), 2)
	);
}

