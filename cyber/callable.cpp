#include "callable.h"

#include <vector>
#include <sstream>
#include <string>

#include "context.h"
#include "interpreter.h"
#include "exceptions.hpp"
#include "Utilities.h"


std::string callable::getSignature()
{
	std::ostringstream oss;
	oss << m_szName << "(";

	if (m_params.size() >= 1) {
		oss << (m_params.at(0).szCustomType.empty()? m_params.at(0).szNativeType : m_params.at(0).szCustomType);
	}

	for (unsigned int i{ 1 }; i < m_params.size(); i++) {
		oss << "," << (m_params.at(0).szCustomType.empty() ? m_params.at(0).szNativeType : m_params.at(0).szCustomType);
	}
	oss << ")";
	return oss.str();
}



std::any native_fn::call(std::shared_ptr<interpreter> c, _args args)
{
	std::scoped_lock(m_mtx);
	std::shared_ptr<execution_context> context = Utilities().fetch_context(c);
	
	std::any ret = nullptr;
	context->push_ar(m_enclosing);

	try {
		std::vector<std::any> cleanedArgs;
		if (!m_variadic) {
			if (args.size() != m_params.size()) {
				throw ExceptionBuilder().Build(ExceptionTypes().PROGRAM(), "parity_mismatch, expected " + std::to_string(m_params.size())
					+ " arguments but got " + std::to_string(args.size()), Severity().MEDIUM());
			}

			for (unsigned int i{ 0 }; i < m_params.size(); i++) {
				std::any arg = c->assert_or_convert_type(m_params.at(i), args.at(i), location());
				cleanedArgs.push_back(arg);
			}
		}
		else {

			if (args.size() < m_variadic_after) {
				throw ExceptionBuilder().Build(ExceptionTypes().PROGRAM(), "parity_mismatch, expected at least " + std::to_string(m_params.size())
					+ " arguments but got " + std::to_string(args.size()), Severity().MEDIUM());
			}

			unsigned int i{ 0 };
			for (i; i < m_variadic_after; i++) {
				std::any arg = c->assert_or_convert_type(m_params.at(i), args.at(i), location());
				cleanedArgs.push_back(arg);
			}

			for (unsigned int j{ i }; j < args.size(); j++) {
				cleanedArgs.push_back(args.at(j));
			}

		}

		ret = m_hFn(c, _args(cleanedArgs));
	}
	catch (ReturnException ret) {
		// Reset environment
		context->pop_ar();
		
		throw ret;
	}
	catch (PanicException pe) {
		// Reset environment
		context->pop_ar();

		throw pe;
	}
	catch (ProgramException pe) {
		// Reset environment
		context->pop_ar();

		// throw error
		throw pe;
	}

	context->pop_ar();
	return c->assert_or_convert_type(m_retType, ret, location());

}

void native_fn::setEnclosing(std::shared_ptr<activation_record> ar)
{
	m_enclosing = ar;
}

std::shared_ptr<native_fn> native_fn::setVariadic()
{
	m_variadic = true;
	return std::static_pointer_cast<native_fn>(shared_from_this());
}

std::shared_ptr<native_fn> native_fn::setVariadicAfter(unsigned int index)
{
	if (!m_variadic) throw ExceptionBuilder().Build(ExceptionTypes().PRECOMPILE(), "cannot set variadic index of non-variadic function", Severity().FATAL());
	if (index > m_params.size()) throw ExceptionBuilder().Build(ExceptionTypes().PRECOMPILE(), "variadic index must be less than parameter size", Severity().FATAL());

	return std::static_pointer_cast<native_fn>(shared_from_this());
}

std::shared_ptr<native_fn> native_fn::registerParameter(const param& p)
{
	m_params.push_back(p);
	return std::static_pointer_cast<native_fn>(shared_from_this());
}

std::any custom_fn::call(std::shared_ptr<interpreter> c, _args arguments)
{
	std::scoped_lock(m_mtx);

	std::shared_ptr<execution_context> context = Utilities().fetch_context(c); // Also checks that c is not nullptr


	// Create closure
	context->push_ar(m_enclosing);
	context->push_ar(m_szName);

	std::any retVal = nullptr;
	bool bReturnCaught = false;

	try {

		// Check parity
		if (arguments.size() != m_params.size()) {
			throw ExceptionBuilder().Build(ExceptionTypes().PROGRAM(), "parity_mismatch, expected " + std::to_string(m_params.size())
				+ " arguments but got " + std::to_string(arguments.size()), Severity().MEDIUM(), m_loc);
		}
		// Clean arguments and define parameters in this scope
		for (unsigned int i{ 0 }; i < m_params.size(); i++) {
			std::any cleanedObject = c->assert_or_convert_type(m_params.at(i), arguments.at(i), m_loc);
			context->define(m_params.at(i).szName, cleanedObject, false, m_loc);
		}

		// Execute function body
		c->interpret(m_body);
	}
	catch (ReturnException ret) {

		// Reset environment
		context->pop_ar();
		context->pop_ar();

		// Return value
		retVal = ret.value();
		bReturnCaught = true;
	}
	catch (PanicException pe) {

		// Reset environment
		context->pop_ar();
		context->pop_ar();

		// Return value
		throw pe;
	}
	catch (ProgramException pe) {
		// Reset environment
		context->pop_ar();
		context->pop_ar();

		// throw error
		throw pe;
	}

	if (!bReturnCaught) {
		//Reset Environment
		context->pop_ar();
		context->pop_ar();
		// We would normally do this in the try{} block
		// but pop_ar itself may throw
	}

	// If there are no errors and no return has been caught
	// just return null value
	return c->assert_or_convert_type(m_retType, retVal, m_loc);
}


void custom_fn::setEnclosing(std::shared_ptr<activation_record> ar)
{
	m_enclosing = ar;
}


std::any unary_fn::call(std::shared_ptr<interpreter> c, _args args)
{
	std::scoped_lock(m_mtx);

	Utilities().check_context(c);
	if (args.size() != 1) {
		throw ExceptionBuilder().Build(ExceptionTypes().PROGRAM(), "parity_mismatch, expected 1 argument but got " + std::to_string(args.size()), Severity().MEDIUM());
	}


	std::any cleanedArg = c->assert_or_convert_type(m_param, args.at(0), location());

	return c->assert_or_convert_type(m_retType, m_hFn(c, cleanedArg), location());
}


std::shared_ptr<callable> unary_fn::registerParameter(const param& p)
{
	m_param = p;
	return std::static_pointer_cast<callable>(shared_from_this());
}

std::string unary_fn::getSignature()
{
	std::ostringstream oss;
	// TODO: custom typing support
	oss << m_szName << "(" << m_param.szNativeType << ")";
	return oss.str();
}


std::any binary_fn::call(std::shared_ptr<interpreter> c,  _args args)
{
	std::scoped_lock(m_mtx);

	Utilities().check_context(c);
	if (args.size() != m_params.size() || m_params.size() != 2) {
		throw ExceptionBuilder().Build(ExceptionTypes().PROGRAM(), "parity_mismatch, expected 2 arguments but got " + std::to_string(args.size()), Severity().MEDIUM());
	}

	std::vector<std::any> cleanedArgs;
	for (unsigned int i{ 0 }; i < m_params.size(); i++) {
		std::any arg = c->assert_or_convert_type(m_params.at(i), args.at(i), location());
		cleanedArgs.push_back(arg);
	}

	return c->assert_or_convert_type(m_retType, m_hFn(c, cleanedArgs.at(0), cleanedArgs.at(1)), location());
}


std::shared_ptr<binary_fn> binary_fn::registerParameter(const param& p)
{
	m_params.push_back(p);
	return std::static_pointer_cast<binary_fn>(shared_from_this());
}



#ifdef BUILD_WINDOWS

// Loaded native


std::any loaded_native_fn::call(std::shared_ptr<interpreter> c, _args args)
{
	std::scoped_lock(m_mtx);

	std::shared_ptr<execution_context> context = Utilities().fetch_context(c);

	std::any ret = nullptr;
	context->push_ar(m_enclosing);

	try {
		std::vector<std::any> cleanedArgs;
		if (!m_variadic) {
			if (args.size() != m_params.size()) {
				throw ExceptionBuilder().Build(ExceptionTypes().PROGRAM(), "parity_mismatch, expected " + std::to_string(m_params.size())
					+ " arguments but got " + std::to_string(args.size()), Severity().MEDIUM());
			}

			for (unsigned int i{ 0 }; i < m_params.size(); i++) {
				std::any arg = c->assert_or_convert_type(m_params.at(i), args.at(i), location());
				cleanedArgs.push_back(arg);
			}
		}
		else {

			if (args.size() < m_variadic_after) {
				throw ExceptionBuilder().Build(ExceptionTypes().PROGRAM(), "parity_mismatch, expected at least " + std::to_string(m_params.size())
					+ " arguments but got " + std::to_string(args.size()), Severity().MEDIUM());
			}

			unsigned int i{ 0 };
			for (i; i < m_variadic_after; i++) {
				std::any arg = c->assert_or_convert_type(m_params.at(i), args.at(i), location());
				cleanedArgs.push_back(arg);
			}

			for (unsigned int j{ i }; j < args.size(); j++) {
				cleanedArgs.push_back(args.at(j));
			}

		}

		ret = m_hFn(c, _args(cleanedArgs));
	}
	catch (ReturnException ret) {
		// Reset environment
		context->pop_ar();

		throw ret;
	}
	catch (PanicException pe) {
		// Reset environment
		context->pop_ar();

		throw pe;
	}
	catch (ProgramException pe) {
		// Reset environment
		context->pop_ar();

		// throw error
		throw pe;
	}

	context->pop_ar();
	return c->assert_or_convert_type(m_retType, ret, location());

}

void loaded_native_fn::setEnclosing(std::shared_ptr<activation_record> ar)
{
	m_enclosing = ar;
}

std::shared_ptr<loaded_native_fn> loaded_native_fn::setVariadic()
{
	m_variadic = true;
	return std::static_pointer_cast<loaded_native_fn>(shared_from_this());
}

std::shared_ptr<loaded_native_fn> loaded_native_fn::setVariadicAfter(unsigned int index)
{
	if (!m_variadic) throw ExceptionBuilder().Build(ExceptionTypes().PRECOMPILE(), "cannot set variadic index of non-variadic function", Severity().FATAL());
	if (index > m_params.size()) throw ExceptionBuilder().Build(ExceptionTypes().PRECOMPILE(), "variadic index must be less than parameter size", Severity().FATAL());
	m_variadic_after = index;
	return std::static_pointer_cast<loaded_native_fn>(shared_from_this());
}

std::shared_ptr<loaded_native_fn> loaded_native_fn::registerParameter(const param& p)
{
	m_params.push_back(p);
	return std::static_pointer_cast<loaded_native_fn>(shared_from_this());
}

#endif