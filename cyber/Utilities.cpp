#include "Utilities.h"

#include <sstream>

#include "callable.h"
#include "klass_instance.h"
#include "interpreter.h"
#include "context.h"
#include "BuildDefinitions.h"

void Utilities::check_context(std::shared_ptr<interpreter> i)
{
	if (i == nullptr) {
		throw ExceptionBuilder().Build(ExceptionTypes().SYSTEM(), "cannot execute code using null interpreter", Severity().FATAL());
	}
}

std::shared_ptr<execution_context> Utilities::fetch_context(std::shared_ptr<interpreter> i)
{
	std::shared_ptr<execution_context> context_ptr = nullptr;
	if (i != nullptr) {
		context_ptr = i->get_context();
	}
	if (i == nullptr || context_ptr == nullptr) {
		throw ExceptionBuilder().Build(ExceptionTypes().SYSTEM(), "cannot execute code using null context", Severity().FATAL());
	}
	return context_ptr;
}


std::string Utilities::stringify(const std::any& obj)
{
	std::ostringstream oss;
	if (obj.type() == typeid(int)) {
		oss << std::any_cast<int>(obj);
	}
	else if (obj.type() == typeid(int8_t)) {
		oss << std::any_cast<int8_t>(obj);
	}
	else if (obj.type() == typeid(int16_t)) {
		oss << std::any_cast<int16_t>(obj);
	}
	else if (obj.type() == typeid(int32_t)) {
		oss << std::any_cast<int32_t>(obj);
	}
	else if (obj.type() == typeid(int64_t)) {
		oss << std::any_cast<int64_t>(obj);
	}
	else if (obj.type() == typeid(uint8_t)) {
		oss << std::any_cast<uint8_t>(obj);
	}
	else if (obj.type() == typeid(uint16_t)) {
		oss << std::any_cast<uint16_t>(obj);
	}
	else if (obj.type() == typeid(uint32_t)) {
		oss << std::any_cast<uint32_t>(obj);
	}
	else if (obj.type() == typeid(uint64_t)) {
		oss << std::any_cast<uint64_t>(obj);
	}
	else if (obj.type() == typeid(bool)) {
		oss << std::boolalpha << std::any_cast<bool>(obj);
	}
	else if (obj.type() == typeid(float)) {
		oss << std::any_cast<float>(obj);
	}
	else if (obj.type() == typeid(double)) {
		oss << std::any_cast<double>(obj);
	}
	else if (obj.type() == typeid(unsigned long)) {
		oss << std::any_cast<unsigned long>(obj);
	}
	else if (obj.type() == typeid(long long)) {
		oss << std::any_cast<long long>(obj);
	}
	else if (obj.type() == typeid(long double)) {
		oss << std::any_cast<long double>(obj);
	}
	else if (obj.type() == typeid(std::string)) {
		oss << std::any_cast<std::string>(obj);
	}
	// TODO: do this better
	else if (obj.type() == typeid(std::shared_ptr<native_fn>)) {
		oss << (std::any_cast<std::shared_ptr<native_fn>>(obj) == nullptr ? "<null>" : std::any_cast<std::shared_ptr<native_fn>>(obj)->getSignature());
	}
#ifdef BUILD_WINDOWS
	else if (obj.type() == typeid(std::shared_ptr<loaded_native_fn>)) {
		oss << (std::any_cast<std::shared_ptr<loaded_native_fn>>(obj) == nullptr ? "<null>" : std::any_cast<std::shared_ptr<loaded_native_fn>>(obj)->getSignature());
	}
#endif
	else if (obj.type() == typeid(std::shared_ptr<binary_fn>)) {
		oss << (std::any_cast<std::shared_ptr<binary_fn>>(obj) == nullptr ? "<null>" : std::any_cast<std::shared_ptr<binary_fn>>(obj)->getSignature());
	}
	else if (obj.type() == typeid(std::shared_ptr<custom_fn>)) {
		oss << (std::any_cast<std::shared_ptr<custom_fn>>(obj) == nullptr ? "<null>" : std::any_cast<std::shared_ptr<custom_fn>>(obj)->getSignature());
	}
	else if (obj.type() == typeid(std::shared_ptr<unary_fn>)) {
		oss << (std::any_cast<std::shared_ptr<unary_fn>>(obj) == nullptr ? "<null>" : std::any_cast<std::shared_ptr<unary_fn>>(obj)->getSignature());
	}
	else if (obj.type() == typeid(std::shared_ptr<callable>)) {
		oss << (std::any_cast<std::shared_ptr<callable>>(obj) == nullptr ? "<null>" : std::any_cast<std::shared_ptr<callable>>(obj)->getSignature());
	}
	else if (obj.type() == typeid(std::shared_ptr<klass_definition>)) {
		oss << (std::any_cast<std::shared_ptr<klass_definition>>(obj) == nullptr ? "<null>" : std::any_cast<std::shared_ptr<klass_definition>>(obj)->toString());
	}
	else if (obj.type() == typeid(klass_instance)) {
		oss << std::any_cast<klass_instance>(obj).toString();
	}
	else if (obj.type() == typeid(nullptr)) {
		oss << "<null>";
	}
	else {
		oss << "<object>";
	}
	return oss.str();
}



bool Utilities::isTruthy(const std::any& obj)
{
	if (obj.type() == typeid(int)) {
		return std::any_cast<int>(obj);
	}
	else if (obj.type() == typeid(unsigned long)) {
		return std::any_cast<unsigned long>(obj);
	}
	else if (obj.type() == typeid(bool)) {
		return std::any_cast<bool>(obj);
	}
	else if (obj.type() == typeid(float)) {
		return std::any_cast<float>(obj);
	}
	else if (obj.type() == typeid(int8_t)) {
		return std::any_cast<int8_t>(obj);
	}
	else if (obj.type() == typeid(int16_t)) {
		return std::any_cast<int16_t>(obj);
	}
	else if (obj.type() == typeid(int32_t)) {
		return std::any_cast<int32_t>(obj);
	}
	else if (obj.type() == typeid(int64_t)) {
		return std::any_cast<int64_t>(obj);
	}
	else if (obj.type() == typeid(uint8_t)) {
		return std::any_cast<uint8_t>(obj);
	}
	else if (obj.type() == typeid(uint16_t)) {
		return std::any_cast<uint16_t>(obj);
	}
	else if (obj.type() == typeid(uint32_t)) {
		return std::any_cast<uint32_t>(obj);
	}
	else if (obj.type() == typeid(uint64_t)) {
		return std::any_cast<uint64_t>(obj);
	}
	else if (obj.type() == typeid(double)) {
		return std::any_cast<double>(obj);
	}
	else if (obj.type() == typeid(long double)) {
		return std::any_cast<long double>(obj);
	}
	else if (obj.type() == typeid(long long)) {
		return std::any_cast<long long>(obj);
	}
	else if (obj.type() == typeid(std::string)) {
		return std::any_cast<std::string>(obj).size() > 0;
	}

	throw ExceptionBuilder().Build(ExceptionTypes().RUNTIME(), "Unsupported object type '" + std::string(obj.type().name()), Severity().LOW());
}


std::string Utilities::createOperatorSignature(const std::string& szName, std::vector<std::any> args)
{
	std::ostringstream oss;
	oss << szName << "(";
	if (args.size() > 0) {
		std::string type_name = getTypeString(args.at(0));
		oss << type_name;
	}
	for (unsigned int i{ 1 }; i < args.size(); i++) {
		std::string type_name = getTypeString(args.at(i));
		oss << "," << type_name;
	}
	oss << ")";
	return oss.str();
}

std::string Utilities::createOperatorSignature(const std::string& szName, std::any arg, const std::string& szTypeName)
{
	std::ostringstream oss;
	oss << szName << "(" << getTypeString(arg)<<"," <<szTypeName << ")";
	return oss.str();
}


std::shared_ptr<callable> Utilities::getCallable(std::any callee) {
	if (callee.type() == typeid(std::shared_ptr<callable>)) {
		return std::any_cast<std::shared_ptr<callable>>(callee);
	}
	else if (callee.type() == typeid(std::shared_ptr<native_fn>)) {
		return std::any_cast<std::shared_ptr<native_fn>>(callee);
	}
#ifdef BUILD_WINDOWS
	else if (callee.type() == typeid(std::shared_ptr<loaded_native_fn>)) {
		return std::any_cast<std::shared_ptr<loaded_native_fn>>(callee);
	}
#endif
	else if (callee.type() == typeid(std::shared_ptr<binary_fn>)) {
		return std::any_cast<std::shared_ptr<binary_fn>>(callee);
	}
	else if (callee.type() == typeid(std::shared_ptr<unary_fn>)) {
		return std::any_cast<std::shared_ptr<unary_fn>>(callee);
	}
	else if (callee.type() == typeid(std::shared_ptr<custom_fn>)) {
		return std::any_cast<std::shared_ptr<custom_fn>>(callee);
	}
	else {
		throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "unable to convert type " + std::string(callee.type().name()) + " to callable type", Severity().MEDIUM());
	}
}


std::string Utilities::getTypeString(std::any obj)
{
	if (obj.type() == typeid(klass_instance)) {
		return std::any_cast<klass_instance>(obj).getType();
	}
	return obj.type().name();
}


std::shared_ptr<activation_record> Utilities::extractScope(std::any& obj)
{
	if (obj.type() == typeid(klass_instance)) {
		return std::any_cast<klass_instance>(obj).ar();
	}
	if (obj.type() == typeid(std::shared_ptr<klass_definition>)) {
		return std::any_cast<std::shared_ptr<klass_definition>>(obj)->ar();
	}
	return nullptr;
}



std::shared_ptr<klass_definition> Utilities::BuildErrorObject(const std::string szType, const std::string szMsg, const std::string& szSeverity)
{
	std::shared_ptr<activation_record> err_env_ar = std::make_shared<activation_record>();
	err_env_ar->szAlias = "Err";
	err_env_ar->environment = std::make_shared<scope<std::any>>();

	err_env_ar->environment->define("type", szType, true);
	err_env_ar->environment->define("msg", szMsg, true);
	err_env_ar->environment->define("severity", szSeverity, true);

	return std::make_shared<klass_definition>("Err", err_env_ar);
}

std::any Utilities::strToAppropriateInt(const std::string& src)
{
	try {
		long long int v = std::stoll(src);
		if (v <= INT8_MAX) {
			return static_cast<int8_t>(v);
		}
		if (v <= INT16_MAX) {
			return static_cast<int16_t>(v);
		}
		if (v <= INT32_MAX) {
			return static_cast<int32_t>(v);
		}
		return static_cast<int64_t>(v);
	}
	catch (std::invalid_argument) {
		throw ExceptionBuilder().Build(ExceptionTypes().PARSING(), "unable to parse value to integer " + src, Severity().HIGH());
	}
	catch (std::out_of_range) {
		throw ExceptionBuilder().Build(ExceptionTypes().PARSING(), "unable to parse value to integer " + src, Severity().HIGH());
	}
}

std::any Utilities::strToAppropriateUInt(const std::string& src)
{
	try {
		unsigned long long int v = std::stoull(src);
		if (v <= UINT8_MAX) {
			return static_cast<uint8_t>(v);
		}
		if (v <= UINT16_MAX) {
			return static_cast<uint16_t>(v);
		}
		if (v <= UINT32_MAX) {
			return static_cast<uint32_t>(v);
		}
		return static_cast<uint64_t>(v);
	}
	catch (std::invalid_argument) {
		throw ExceptionBuilder().Build(ExceptionTypes().PARSING(), "unable to parse value to unsigned integer " + src, Severity().HIGH());
	}
	catch (std::out_of_range) {
		throw ExceptionBuilder().Build(ExceptionTypes().PARSING(), "unable to parse value to unsigned integer " + src, Severity().HIGH());
	}
}