#include "common/state.hpp"

SubState::SubState(float x, float y, float depth, float yaw, float pitch, float roll) :
	x(x), y(y), depth(depth), yaw(yaw), pitch(pitch), roll(roll)
{
}

SubState::SubState(FILE* in)
{
	fscanf(in, "%f %f %f %f %f %f ", &x, &y, &depth, &yaw, &pitch, &roll);
}

void SubState::write(FILE* out) const
{
	fprintf(out, "s\n");
	fprintf(out, "%f %f %f %f %f %f\n", x, y, depth, yaw, pitch, roll);
}

State::State(FILE* in)
{
	fscanf(in, "s");
	m_location = Matrix(in);
	m_direction = Matrix(in);
}

State::State(const Matrix& location, const Matrix& direction) :
	m_location(location),
	m_direction(direction)
{
}

void State::write(FILE* out) const
{
	fprintf(out, "s\n");
	m_location.write(out);
	m_direction.write(out);
}

Matrix State::location() const
{
	return m_location;
}

Matrix State::direction() const
{
	return m_direction;
}

