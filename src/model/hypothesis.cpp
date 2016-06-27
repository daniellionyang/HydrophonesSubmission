#include "model/hypothesis.hpp"

#include <cmath>

Hypothesis::Hypothesis()
{
}

Hypothesis::Hypothesis(float _weight, Matrix _values, Matrix _variance) :
	m_weight(_weight),
	m_values(_values),
	m_variance(_variance)
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
	fflush(out);
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

void Hypothesis::addVariance(size_t idx, float value)
{
	if (idx < m_variance.size())
		m_variance.set(idx, m_variance.get(idx) + value);
}

void Hypothesis::add(Evidence evidence)
{
	for (auto v : evidence.variables)
	{
		size_t i = v.index;

		// kalman filter update step
		// no prediction step because the objects don't move
		// and process each variable independently
		// 
		// Given two Gaussian distributions with means (u1, u2) and variance
		// (v1, v2) their product has mean
		// 
		//   u1*v2 + u2*v1
		//   -------------
		//      v1 + v2
		//
		// and variance
		// 
		//   v1 * v2
		//   -------
		//   v1 + v2
		//
		// It mimics another Gaussian distribution, but the maximum value of
		// the exponent is not 0, but
		// 
		//   - (u1 - u2)^2
		//   -------------
		//   2 * (v1 + v2)
		// 
		// Therefore, the maximum height (which we use as the weight instead of
		// the integral, because who wants to calculate the integral?) is the
		// product of the original two distributions' heights (ie weights) and
		// e to the power of the above value.

		auto u1 = m_values.get(i);
		auto v1 = m_variance.get(i);

		auto u2 = v.value;
		auto v2 = v.variance;

		m_values.set(i, (u1*v2 + u2*v1) / (v1 + v2));
		m_variance.set(i, (v1 * v2) / (v1 + v2));
		m_weight *= std::exp(-std::pow(u1 - u2, 2) / (2 * (v1 + v2)));
	}
}

void Hypothesis::scale(float scalar)
{
	m_weight *= scalar;
}

