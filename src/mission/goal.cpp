#include "mission/goal.hpp"

#include "mission/action.hpp"

Goal::Goal(FILE* config)
{
	fscanf(config, "%f", &m_value);
	fscanf(config, "%f", &m_time);
	fscanf(config, "%f", &m_certainty);
	int n;
	fscanf(config, "%i", &n);
	for(int i = 0; i < n; i++)
	{
		m_actions.push_back(getaction(config));
	}
}

void Goal::write(FILE* out)
{
}

bool Goal::run(FILE* in, FILE* out)
{
	for (auto a : m_actions)
		if (!a->run(in, out))
			return false;
	return true;
}

Matrix Goal::location(const Matrix& model) const
{
	return m_loc_transform * model + m_loc_offset;
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

