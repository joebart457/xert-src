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
	static std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v");
	static std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v");
	static std::string& trim(std::string& s, const char* t = " \t\n\r\f\v");
	static long long find(const std::string& src, const std::string& search);
	static std::string substr(const std::string& src, unsigned long start, unsigned long end);
};

#endif