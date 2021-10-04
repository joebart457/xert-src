#pragma once

#ifndef __INCLUDE_UTILITIES_H
#define __INCLUDE_UTILITIES_H

#include <any>
#include <memory>
#include <vector>
#include <string>

class callable;
class execution_context;
class interpreter;
struct activation_record;
class klass_definition;

class Utilities
{
public:
	static void check_context(std::shared_ptr<interpreter> c);
	static std::shared_ptr<execution_context> fetch_context(std::shared_ptr<interpreter> i);
	static std::string stringify(const std::any& obj);
	static bool isTruthy(const std::any& obj);
	static bool isTruthyNoThrow(const std::any& obj);
	static std::string createOperatorSignature(const std::string& szName, std::vector<std::any> args);
	static std::string createOperatorSignature(const std::string& szName, std::any arg, const std::string& szTypeName);
	static std::shared_ptr<callable> getCallable(std::any callee);
	static std::string getTypeString(std::any obj);
	static std::shared_ptr<activation_record> extractScope(std::any& obj);
	static std::shared_ptr<klass_definition> BuildErrorObject(const std::string szType, const std::string szMsg, const std::string& szSeverity);
	static std::any strToAppropriateInt(const std::string& src);
	static std::any strToAppropriateUInt(const std::string& src);

};

#endif