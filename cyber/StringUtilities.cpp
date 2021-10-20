#include "StringUtilities.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>

bool StringUtilities::startsWith(const std::string& s, const std::string& match)
{
	return s.find(match) == 0;
}


bool StringUtilities::contains(const std::string& s, const std::string& match)
{
	return s.find(match) != std::string::npos;
}

std::vector<std::string> StringUtilities::split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

std::string StringUtilities::lower(const std::string& s)
{
	std::string data = s;
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}

std::vector<std::string> StringUtilities::split(const std::string& src, const std::string& delimiter)
{
	size_t pos_start = 0;
	size_t pos_end = 0;
	size_t delim_len = delimiter.length();
	std::string token{ "" };
	std::vector<std::string> res;

	while ((pos_end = src.find(delimiter, pos_start)) != std::string::npos) {
		token = src.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(src.substr(pos_start));
	return res;
}


// trim from end of string (right)
std::string& StringUtilities::rtrim(std::string& s, const char* t)
{
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

// trim from beginning of string (left)
std::string& StringUtilities::ltrim(std::string& s, const char* t)
{
	s.erase(0, s.find_first_not_of(t));
	return s;
}

// trim from both ends of string (right then left)
std::string& StringUtilities::trim(std::string& s, const char* t)
{
	return ltrim(rtrim(s, t), t);
}

long long StringUtilities::find(const std::string& src, const std::string& search)
{
	std::size_t found = src.find(search);
	if (found == std::string::npos) {
		return -1;
	}
	return found;
}

std::string StringUtilities::substr(const std::string& src, uint64_t start, uint64_t end)
{
	if (start > src.size() || end > src.size()) {
		return "";
	}
	return src.substr(start, end);
}

std::string StringUtilities::pad(const std::string& src, char fill, int64_t width)
{
	std::ostringstream oss;
	oss << std::setw(width) << std::internal << std::setfill(fill) << src;
	return oss.str();
}
