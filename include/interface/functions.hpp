#ifndef INTERFACE_FUNCTIONS_HPP
#define INTERFACE_FUNCTIONS_HPP

#include <string>

#include "interface/data.hpp"

bool hydrophones(Data*, const std::string, const std::string);

bool buoys(Data*, const std::string, const std::string);
bool bins(Data*, const std::string, const std::string);

bool camera(Data*, const std::string, const std::string, int);

bool mission(Data*, const std::string, const std::string);
bool modeling(Data*, const std::string, const std::string);
bool control(Data*, const std::string, const std::string);

#endif

