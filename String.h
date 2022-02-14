#pragma once
#include <string>
#include <vector>

class String
{
public:
	static std::vector<std::string> split(const std::string& string, const char& separator);
};
