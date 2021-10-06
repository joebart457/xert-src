#pragma once


#ifndef __INCLUDE__PRELIM__UNIVERSAL_FILE_HANDLE_H
#define __INCLUDE__PRELIM__UNIVERSAL_FILE_HANDLE_H

#include <string>
#include <vector>
#include <stdint.h>
#include <fstream>
#include <filesystem>

#include "exceptions.hpp"

class FileHandle
{
public:

	FileHandle()
	{
	}


	~FileHandle()
	{
	}

	static void copyFile(const std::string& source, const std::string& dest) {
		const auto copyOptions = std::filesystem::copy_options::update_existing
			| std::filesystem::copy_options::recursive;
		std::filesystem::copy(source, dest, copyOptions);
	}

	static uint64_t removeAll(const std::string& source) {
		return std::filesystem::remove_all(source);
	}


	static std::vector<std::string> readFile(const std::string& filepath) {
		std::vector<std::string> fileData;
		std::ifstream f(filepath);
		if (f.is_open()) {
			std::string line;
			while (std::getline(f, line)) {
				fileData.push_back(line);
			}
			f.close();
			return fileData;
		}
		else {
			throw BuildException("unable to perform io operation on file '" + filepath + "'; file not found or unable to open");
		}
	}

	static std::string readLine(const std::string& filepath, uint64_t lineNumber) {
		std::string fileData;
		std::ifstream f(filepath);
		if (f.is_open()) {
			std::string line;
			uint64_t counter = 0;
			while (std::getline(f, line)) {
				if (counter == lineNumber) {
					fileData = line;
					break;
				}
				counter++;
			}
			f.close();
			return fileData;
		}
		else {
			throw BuildException("unable to perform io operation on file '" + filepath + "'; file not found or unable to open");
		}
	}

	static uint64_t countLines(const std::string& filepath) {
		std::ifstream f(filepath);
		if (f.is_open()) {
			std::string line;
			unsigned int counter = 0;
			while (std::getline(f, line)) {
				counter++;
			}
			f.close();
			return counter;
		}
		else {
			throw BuildException("unable to perform io operation on file '" + filepath + "'; file not found or unable to open");
		}
	}

	static std::string readFileAsString(const std::string& filepath)
	{
		std::string fileData{ "" };
		std::ifstream f(filepath);
		if (f.is_open()) {
			std::string line;
			while (std::getline(f, line)) {
				fileData += line + "\n";
			}
			f.close();
			return fileData;
		}
		else {
			throw BuildException("unable to perform io operation on file '" + filepath + "'; file not found or unable to open");
		}
	}


	static void writeToFile(const std::string& filepath, std::vector<std::string> data, bool overwriteContents) {
		std::ofstream f(filepath, overwriteContents ? std::ofstream::out : std::ofstream::out | std::ofstream::app);
		if (f.is_open()) {
			for (unsigned int i{ 0 }; i < data.size(); i++) {
				f << data[i] << "\n";
			}
			f.close();
			return;
		}
		else {
			throw BuildException("unable to perform io operation on file '" + filepath + "'; file not found or unable to open");
		}
	}

	static void writeLine(const std::string& filepath, std::string data, bool overwriteContents) {
		std::ofstream f(filepath, overwriteContents ? std::ofstream::out : std::ofstream::out | std::ofstream::app);
		if (f.is_open()) {
			f << data;
			f.close();
			return;
		}
		else {
			throw BuildException("unable to perform io operation on file '" + filepath + "'; file not found or unable to open");
		}
	}


	static std::string current_path()
	{
		return std::filesystem::current_path().string();
	}

	static std::string parent_path(const std::string& szFilePath)
	{
		std::filesystem::path fp(szFilePath);
		return fp.parent_path().string();
	}

	static std::string absolute_path(const std::string& szFilePath)
	{
		return std::filesystem::absolute(szFilePath).string();
	}


	static void rename(const std::string& szSource, const std::string& szRename)
	{
		std::filesystem::rename(szSource, szRename);
	}

	static uint64_t file_size(const std::string& szFilePath)
	{
		return std::filesystem::file_size(szFilePath);
	}

	static bool exists(const std::string& szFilePath)
	{
		return std::filesystem::exists(szFilePath);
	}

	static PanicException BuildException(const std::string& msg)
	{
		return ExceptionBuilder().Build(ExceptionTypes().IO(), msg, Severity().MEDIUM());
	}


	static bool replaceLine(const std::string& szFile, const std::string& newLine, uint64_t lineNumber)
	{
		if (countLines(szFile) < lineNumber) {
			return false;
		}
		std::string szOutFile = getUniqueName(szFile, 100);
		std::ifstream inFile(szFile, std::ifstream::in);
		std::ofstream outFile(szOutFile, std::ofstream::out);
		if (inFile.is_open() && outFile.is_open()) {
			std::string line;
			uint64_t counter = 0;
			while (std::getline(inFile, line)) {
				if (counter == lineNumber) {
					outFile << newLine << "\n";
				}
				else {
					outFile << line << "\n";
				}
				counter++;
			}
			inFile.close();
			outFile.close();

			removeAll(szFile);
			rename(szOutFile, szFile);
			return true;
		}
		else {
			throw BuildException("unable to perform io operation on file '" + szFile + "'; file not found or unable to open");
		}

	}

	static std::string getUniqueName(const std::string& base, uint32_t tries = 1000)
	{
		std::filesystem::path p(base);
		std::string fName = p.filename().string();
		for (unsigned int i{ 0 }; i < tries; i++) {
			auto uniqueFile = p.replace_filename("tmp" + std::to_string(i) + "__" + fName);
			if (!std::filesystem::exists(uniqueFile)) {
				std::ofstream f(uniqueFile.string());
				f.close();
				return uniqueFile.string();
			}
		}
		throw BuildException("unable to create unique file '" + p.string() + "'");
	}

};




#endif