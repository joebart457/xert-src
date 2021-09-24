#include "OperatorHandler.h"


#include "exceptions.h"

void OperatorHandler::registerOperator(std::shared_ptr<callable> op, const std::string& signatureOverride)
{
	if (op == nullptr) return;
	if (signatureOverride.empty()) {
		m_operators[op->getSignature()] = op;
	}
	else {
		m_operators[signatureOverride] = op;

	}
}

std::shared_ptr<callable> OperatorHandler::getOperator(std::string szName)
{
	if (m_operators.count(szName)) {
		return m_operators[szName];
	}
	throw ExceptionBuilder().Build(ExceptionTypes().UNRESOLVED_SYMBOL(), "Undefined operator '" + szName + "'", Severity().CRITICAL());
}


void OperatorHandler::output()
{
	for (auto it = m_operators.begin(); it != m_operators.end(); it++) {
		std::cout << it->first << ":=" << (it->second == nullptr ? "<null>" : it->second->getSignature()) << std::endl;
	}
}