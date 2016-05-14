#ifndef INTERFACE_FUNCTIONS_HPP
#define INTERFACE_FUNCTIONS_HPP

#include <string>

#include "interface/data.hpp"

bool camera_f(const std::string, const std::string, Data*);
bool camera_d(const std::string, const std::string, Data*);

bool mission(const std::string, const std::string, Data*);
bool modeling(const std::string, const std::string, Data*);
bool control(const std::string, const std::string, Data*);

#endif

