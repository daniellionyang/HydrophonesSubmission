#include "mission/goal.hpp"

#include "mission/action.hpp"

Goal::Goal(FILE* in)
{
}

void Goal::write(FILE* out)
{
}

bool Goal::run(FILE* in, FILE* out)
{
	for (auto a : m_actions)
		if (!a(in, out))
			return false;
	return true;
}

State Goal::location(const Matrix& model) const
{
	auto loc = m_loc_transform * model + m_loc_offset;
	return State(loc.get(0), loc.get(1), loc.get(2));
}

float Goal::value() const
{
	return m_value;
}

float Goal::time() const
{
	return m_time;
}

float Goal::certainty() const
{
	return m_certainty;
}

