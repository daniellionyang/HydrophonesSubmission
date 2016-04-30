#include "model/hypothesis.hpp"

Hypothesis::Hypothesis()
{
}

Hypothesis::Hypothesis(FILE* in)
{
	fscanf(in, " %f", &m_weight);
	m_values = Matrix(in);
	m_variance = Matrix(in);
}

size_t Hypothesis::write(FILE* out) const
{
	size_t bytes = 0;
	bytes += fprintf(out, "%f\n", m_weight);
	bytes += m_values.write(out);
	bytes += m_variance.write(out);
	return bytes;
}

float Hypothesis::weight() const
{
	float w = m_weight;
	for (size_t i = 0; i < m_variance.size(); i++)
		w /= m_variance.get(i);
	return w;
}

Matrix Hypothesis::mode() const
{
	return m_values;
}

void Hypothesis::add(Evidence evidence)
{
	for (auto v : evidence.variables)
	{
		// kalman filter update step
		// no prediction step because the objects don't move
		size_t i = v.index;

		auto x = m_values.get(i);
		auto p = m_variance.get(i);

		float k = p / (p + v.variance);

		m_values.set(i, x + k * (v.value - x));
		m_variance.set(i, (1 - k) * p);
	}
}

void Hypothesis::scale(float scalar)
{
	m_weight *= scalar;
}

