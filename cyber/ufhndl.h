#pragma once


#ifndef __INCLUDE__PRELIM__UNIVERSAL_FILE_HANDLE_H
#define __INCLUDE__PRELIM__UNIVERSAL_FILE_HANDLE_H

#include <string>
#include <vector>

#include "exceptions.h"

class FileHandle
{
public:
	FileHandle();
	~FileHandle();

	static void copyFile(const std::string& source, const std::string& dest);
	static uint64_t removeAll(const std::string& source);
	static std::vector<std::string> readFile(const std::string& szFilepath);
	static std::string readFileAsString(const std::string& filepath);
	static void writeToFile(const std::string& filepath, std::vector<std::string> data, bool overwriteContents = true);
	static void writeLine(const std::string& filepath, std::string data, bool overwriteContents = true);
	static std::string readLine(const std::string& filepath, uint64_t lineNumber);
	static uint64_t countLines(const std::string& filepath);
	static std::string current_path();
	static std::string parent_path(const std::string& szFilePath);
	static std::string absolute_path(const std::string& szFilePath);
	static void rename(const std::string& szSource, const std::string& szRename);
	static uint64_t file_size(const std::string& szFilePath);
	static bool exists(const std::string& szFilePath);
	static PanicException BuildException(const std::string& msg);
	static std::string getUniqueName(const std::string& base, unsigned int tries = 100);
	static bool replaceLine(const std::string& szFile, const std::string& newLine, uint64_t lineNumber);

};



#endif