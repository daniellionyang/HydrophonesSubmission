#include "mission/task.hpp"

Task::Task(FILE* in)
{
}

void Task::write(FILE* out)
{
}

bool Task::run()
{
	return true;
}

Matrix Task::location(const Matrix& model) const
{
	return m_loc_transform * model + m_loc_offset;
}

float Task::value() const
{
	return m_value;
}

float Task::time() const
{
	return m_time;
}

float Task::certainty() const
{
	return m_certainty;
}

