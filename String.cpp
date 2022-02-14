#include <vector>
#include <string>
#include "String.h"

std::vector<std::string> String::split(const std::string& string, const char& separator)
{
	std::vector<std::string> words = {};

	std::string word;
	for (char character : string)
	{
		if (character == separator)
		{
			words.push_back(word);
			word = "";
			continue;;
		}
		word += character;
	}
	if (word != "") words.push_back(word);

	return words;
}