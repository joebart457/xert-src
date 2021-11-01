#pragma once

#include "callable.h"

#include <map>
#include <string>
#include <memory>


class operator_handler
{
public:
	operator_handler(){}
	~operator_handler(){}

	void registerOperator(std::shared_ptr<callable> op, const std::string& signatureOverride = "");
	std::shared_ptr<callable> getOperator(const std::string& szName);
	bool exists(const std::string& szName);
	void output();

private:
	std::map<std::string, std::shared_ptr<callable>> m_operators;
};

