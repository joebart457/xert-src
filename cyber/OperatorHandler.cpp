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
	throw ProgramException("Undefined operator '" + szName + "'", location(), Severity().CRITICAL());
}