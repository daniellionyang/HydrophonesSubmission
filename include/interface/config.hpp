#ifndef INTERFACE_CONFIG_HPP
#define INTERFACE_CONFIG_HPP

#include <vector>

#include "interface/data.hpp"
#include "interface/functions.hpp"

struct Connection
{
	const std::function<bool(const std::string, const std::string, Data*)> function;
	const std::string in_name;
	const std::string out_name;
};

std::vector<Connection> defaultConnections();

Matrix initialModel();
Matrix initialVariance();

#endif

