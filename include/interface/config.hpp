#ifndef INTERFACE_CONFIG_HPP
#define INTERFACE_CONFIG_HPP

#include <vector>

#include "common/config.hpp"
#include "interface/data.hpp"
#include "interface/functions.hpp"

struct Connection
{
	template <typename F, typename... A>
	Connection(F _function, A... args) :
		function(std::bind(_function, std::placeholders::_1, args...))
	{
	}

	const std::function<bool(Data*)> function;
};

std::vector<Connection> defaultConnections();

#endif

