#include "mission/goal.hpp"

#include "mission/action.hpp"

Goal::Goal(FILE* config) : fails(0)
{
	fscanf(config, "%f", &m_value);
	fscanf(config, "%f", &m_time);
	fscanf(config, "%f", &m_certainty);
	fscanf(config, "%i", &m_offset);
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

State Goal::location(const Matrix& model) const
{
	return State(model.get(m_offset), model.get(m_offset+1), model.get(m_offset+2));
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
	return (fails > 0) ? 0.001 : m_certainty;
}

