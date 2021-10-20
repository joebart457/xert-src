#pragma once

#include <any>
#include <string>
#include <sstream>

#include "tokenizer.hpp"
#include "BuildDefinitions.hpp"
#include "klass_instance.h"
#include "callable.h"
#include "exceptions.hpp"

class Serializer {
public:

	Serializer(){}
	~Serializer(){}

	template<class _Ty>
	std::string toTypeQualifiedSerial(std::any& obj)
	{
		if (obj.type() != typeid(_Ty)) {
			throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "type mismatch for any_cast", Severity().CRITICAL());
		}
		std::ostringstream oss;
		if (typeid(_Ty) == typeid(std::string)) {
			oss << "\"" << std::any_cast<_Ty>(obj) << "\"";
		} 
		else if (typeid(_Ty) == typeid(unsigned char)) {
			int temp = std::any_cast<unsigned char>(obj);
			oss << temp;
		}
		else if (typeid(_Ty) == typeid(signed char)) {
			int temp = std::any_cast<signed char>(obj);
			oss << temp;
		}
		else {
			oss << std::any_cast<_Ty>(obj);
		}
		oss << "::~" << typeid(_Ty).name() << "~";
		return oss.str();
	}

	std::vector<uint8_t> Serialize(std::any obj)
	{
		std::ostringstream oss;
		if (obj.type() == typeid(int)) {
			oss << toTypeQualifiedSerial<int>(obj);
		}
		else if (obj.type() == typeid(int8_t)) {
			oss << toTypeQualifiedSerial<int8_t>(obj);
		}
		else if (obj.type() == typeid(int16_t)) {
			oss << toTypeQualifiedSerial<int16_t>(obj);
		}
		else if (obj.type() == typeid(int32_t)) {
			oss << toTypeQualifiedSerial<int32_t>(obj);
		}
		else if (obj.type() == typeid(int64_t)) {
			oss << toTypeQualifiedSerial<int64_t>(obj);
		}
		else if (obj.type() == typeid(uint8_t)) {
			oss << toTypeQualifiedSerial<uint8_t>(obj);
		}
		else if (obj.type() == typeid(uint16_t)) {
			oss << toTypeQualifiedSerial<uint16_t>(obj);
		}
		else if (obj.type() == typeid(uint32_t)) {
			oss << toTypeQualifiedSerial<uint32_t>(obj);
		}
		else if (obj.type() == typeid(uint64_t)) {
			oss << toTypeQualifiedSerial<uint64_t>(obj);
		}
		else if (obj.type() == typeid(bool)) {
			oss << std::boolalpha << std::any_cast<bool>(obj);
		}
		else if (obj.type() == typeid(float)) {
			oss << toTypeQualifiedSerial<float>(obj);
		}
		else if (obj.type() == typeid(double)) {
			oss << toTypeQualifiedSerial<double>(obj);
		}
		else if (obj.type() == typeid(unsigned long)) {
			oss << toTypeQualifiedSerial<unsigned long>(obj);
		}
		else if (obj.type() == typeid(long long)) {
			oss << toTypeQualifiedSerial<long long>(obj);
		}
		else if (obj.type() == typeid(long double)) {
			oss << toTypeQualifiedSerial<long double>(obj);
		}
		else if (obj.type() == typeid(std::string)) {
			oss << toTypeQualifiedSerial<std::string>(obj);
		}
		else if (obj.type() == typeid(std::shared_ptr<klass_definition>)) {
			auto classdef = std::any_cast<std::shared_ptr<klass_definition>>(obj);
			oss << SerializeClassDefinition(classdef);
		}
		else if (obj.type() == typeid(klass_instance)) {
			auto instance = std::any_cast<klass_instance>(obj);
			oss << SerializeClassInstance(instance);
		}
		else if (obj.type() == typeid(std::vector<std::any>)) {
			auto vec = std::any_cast<std::vector<std::any>>(obj);
			oss << SerializeVector(vec);
		}
		else if (obj.type() == typeid(nullptr)) {
			oss << "null";
		}
		else {
			throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to serialize object of type " + std::string(obj.type().name()), Severity().MEDIUM());
		}

		std::string str = oss.str();
		return std::vector<uint8_t>(str.begin(), str.end());
	}
	

	bool Serializable(std::any obj)
	{
		if (obj.type() == typeid(int)) {
			return true;
		}
		else if (obj.type() == typeid(int8_t)) {
			return true;
		}
		else if (obj.type() == typeid(int16_t)) {
			return true;
		}
		else if (obj.type() == typeid(int32_t)) {
			return true;
		}
		else if (obj.type() == typeid(int64_t)) {
			return true;
		}
		else if (obj.type() == typeid(uint8_t)) {
			return true;
		}
		else if (obj.type() == typeid(uint16_t)) {
			return true;
		}
		else if (obj.type() == typeid(uint32_t)) {
			return true;
		}
		else if (obj.type() == typeid(uint64_t)) {
			return true;
		}
		else if (obj.type() == typeid(bool)) {
			return true;
		}
		else if (obj.type() == typeid(float)) {
			return true;
		}
		else if (obj.type() == typeid(double)) {
			return true;
		}
		else if (obj.type() == typeid(unsigned long)) {
			return true;
		}
		else if (obj.type() == typeid(long long)) {
			return true;
		}
		else if (obj.type() == typeid(long double)) {
			return true;
		}
		else if (obj.type() == typeid(std::string)) {
			return true;
		}
		else if (obj.type() == typeid(std::shared_ptr<klass_definition>)) {
			return true;
		}
		else if (obj.type() == typeid(klass_instance)) {
			return true;
		}
		else if (obj.type() == typeid(std::vector<std::any>)) {
			return true;
		}
		else if (obj.type() == typeid(nullptr)) {
			return true;
		}
		else {
			return false;
		}
	}

private:

	std::string SerializeClassDefinition(std::shared_ptr<klass_definition> classdef)
	{
		if (classdef == nullptr 
			|| classdef->m_ar == nullptr 
			|| classdef->m_ar->environment == nullptr 
			|| classdef->m_ar->environment->lookup() == nullptr) 
		{
			return "null";
		}

		auto mpLookup = classdef->m_ar->environment->lookup();

		std::ostringstream oss;
		oss << "{";
		for (auto it = mpLookup->begin(); it != mpLookup->end(); it++) {
			if (Serializable(it->second)) {
				oss << "_ty ~" << it->first << "~ = " << Serialize(it->second) << ";";
			}
		}
		oss << "}";
		return oss.str();
	}


	std::string SerializeClassInstance(klass_instance& instance)
	{
		if (instance.m_ar == nullptr
			|| instance.m_ar->environment == nullptr
			|| instance.m_ar->environment->lookup() == nullptr)
		{
			return "null";
		}

		auto mpLookup = instance.m_ar->environment->lookup();

		std::ostringstream oss;
		oss << "{";
		for (auto it = mpLookup->begin(); it != mpLookup->end(); it++) {
			if (Serializable(it->second)) {
				oss << "_ty ~" << it->first << "~ = " << Serialize(it->second) << ";";
			}
		}
		oss << "}";
		return oss.str();
	}

	std::string SerializeVector(std::vector<std::any> v)
	{
		std::ostringstream oss;
		oss << "new Containers.list(";
		if (v.size() > 0) {
			oss << v.at(0);
		}
		for (unsigned int i{ 1 }; i < v.size(); i++) {
			oss << ",";
			if (Serializable(v.at(i))) {
				oss << Serialize(v.at(i));
			}
			else {
				oss << "null";
			}
		}
		oss << ")";
		return oss.str();
	}
};