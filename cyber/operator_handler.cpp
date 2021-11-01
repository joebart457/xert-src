#include "operator_handler.h"

#include "exceptions.hpp"

void operator_handler::registerOperator(std::shared_ptr<callable> op, const std::string& signatureOverride)
{
	if (op == nullptr) return;
	if (signatureOverride.empty()) {
		m_operators[op->getSignature()] = op;
	}
	else {
		m_operators[signatureOverride] = op;

	}
}

std::shared_ptr<callable> operator_handler::getOperator(const std::string& szName)
{
	if (m_operators.count(szName)) {
		return m_operators[szName];
	}
	throw ExceptionBuilder().Build(ExceptionTypes().UNRESOLVED_SYMBOL(), "Undefined operator '" + szName + "'", Severity().CRITICAL());
}

bool operator_handler::exists(const std::string& szName)
{
	return m_operators.count(szName);
}


void operator_handler::output()
{
	for (auto it = m_operators.begin(); it != m_operators.end(); it++) {
		std::cout << it->first << ":=" << (it->second == nullptr ? "<null>" : it->second->getSignature()) << std::endl;
	}
}