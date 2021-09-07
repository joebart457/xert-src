#pragma once

#ifndef __STRING_UTIL_H
#define __STRING_UTIL_H

#include <string>
#include <vector>

class StringUtilities {
public:
	static bool contains(const std::string& s, const std::string& match);
	static std::vector<std::string> split(const std::string& s, char delimiter);
	static std::string lower(const std::string& s);
	static std::vector<std::string> split(const std::string& src, const std::string& delimeter);
};

#endif