#pragma once


#include <memory>
#include <any>

#include "context.h"
#include "exceptions.hpp"

class klass_instance { 

	friend class Serializer;
public: 
	klass_instance(const std::string& type, const std::string& signature, std::shared_ptr<activation_record> ar)
		:m_szType{ type }, m_szSignature{ signature }, m_ar{ ar } {}
	~klass_instance() {}

	bool Exists(const std::string& szName) {
		return m_ar->environment->exists_local(szName);
	}

	void Define(std::string szName, std::any value, const location& loc, bool overwrite) {
		if (!m_ar->environment->define(szName, value, overwrite)) {
			throw ExceptionBuilder().Build(ExceptionTypes().UNRESOLVED_SYMBOL(), "unable to define value for key '" + szName + "'", Severity().MEDIUM(), loc);
		}
	}

	void Assign(std::string szName, std::any value, const location& loc) {
		if (!m_ar->environment->assign(szName, value)) {
			throw ExceptionBuilder().Build(ExceptionTypes().UNRESOLVED_SYMBOL(), "unable to assign value to key '" + szName + "'", Severity().MEDIUM(), loc);
		}
	}

	std::any Get(std::string szName, const location& loc) {
		std::any out;
		if (!m_ar->environment->get(szName, out)) {
			throw ExceptionBuilder().Build(ExceptionTypes().UNRESOLVED_SYMBOL(), "unable to retrieve value with key '" + szName + "'", Severity().MEDIUM(), loc);
		}
		return out;
	}

	template <class Ty>
	Ty Get(std::string szName, const location& loc) {
		std::any out;
		if (!m_ar->environment->get(szName, out)) {
			throw ExceptionBuilder().Build(ExceptionTypes().UNRESOLVED_SYMBOL(), "unable to retrieve value with key '" + szName + "'", Severity().MEDIUM());
		}
		if (out.type() != typeid(Ty)) {
			throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "type mismatch in assertion type " + Utilities().getTypeString(out) + " != " + std::string(typeid(Ty).name()), Severity().HIGH());
		}
		return std::any_cast<Ty>(out);
	}

	template <typename Ty>
	Ty tryGet(const std::string& szKey, Ty defaultValue)
	{
		std::any out = nullptr;
		if (!m_ar->environment->get(szKey, out)) {
			return defaultValue;
		}

		if (out.type() != typeid(Ty)) {
			return defaultValue;
		}
		return std::any_cast<Ty>(out);
	}

	std::string getSignature()
	{
		return m_szSignature;
	}

	std::string getType()
	{
		return m_szType;
	}

	std::string toString()
	{
		return m_ar->environment->toString();
	}

	std::shared_ptr<activation_record> ar()
	{
		return m_ar;
	}

private:
	std::string m_szSignature{ "class_instance_0" };
	std::string m_szType{ "class_instance" };
	std::shared_ptr<activation_record> m_ar;
};

class klass_definition {
	friend class Serializer;

public:
	klass_definition(std::string szName, std::shared_ptr<activation_record> ar)
		:m_szName{ szName }, m_ar{ ar }{}
	~klass_definition() {}

	klass_instance create()
	{
		std::string alias = m_szName + "_instance_" + std::to_string(m_refIndex);
		std::shared_ptr<activation_record> ar = std::make_shared<activation_record>();
		ar->environment = m_ar->environment->copy();
		ar->szAlias = alias;
		m_refIndex = m_refIndex + 1;
		auto m = ar->environment->lookup();
		for (auto it = m->begin(); it != m->end(); it++) {
			if (it->second.type() == typeid(std::shared_ptr<custom_fn>)) {
				std::shared_ptr<custom_fn> fn = std::any_cast<std::shared_ptr<custom_fn>>(it->second);
				fn = std::make_shared<custom_fn>(*fn.get());
				fn->setEnclosing(ar);
				ar->environment->define(it->first, fn, true);
			} 
			else if (it->second.type() == typeid(std::shared_ptr<native_fn>)) {
				std::shared_ptr<native_fn> fn = std::any_cast<std::shared_ptr<native_fn>>(it->second);
				fn = std::make_shared<native_fn>(*fn.get());
				fn->setEnclosing(ar);
				ar->environment->define(it->first, fn, true);
			}
#ifdef BUILD_WINDOWS
			else if (it->second.type() == typeid(std::shared_ptr<loaded_native_fn>)) {
				std::shared_ptr<loaded_native_fn> fn = std::any_cast<std::shared_ptr<loaded_native_fn>>(it->second);
				fn = std::make_shared<loaded_native_fn>(*fn.get());
				fn->setEnclosing(ar);
				ar->environment->define(it->first, fn, true);
			}
#endif
		}
		klass_instance instance = klass_instance(m_szName, alias, ar);
		ar->environment->define("this", instance, true);
		return instance;
	}

	bool Exists(const std::string& szName) {
		return m_ar->environment->exists_local(szName);
	}

	void Define(std::string szName, std::any value, const location& loc, bool overwrite) {
		if (!m_ar->environment->define(szName, value, overwrite)) {
			throw ExceptionBuilder().Build(ExceptionTypes().UNRESOLVED_SYMBOL(), "unable to define value for key '" + szName + "'", Severity().MEDIUM(), loc);
		}
	}

	void Assign(std::string szName, std::any value, const location& loc) {
		if (!m_ar->environment->assign(szName, value)) {
			throw ExceptionBuilder().Build(ExceptionTypes().UNRESOLVED_SYMBOL(), "unable to assign value to key '" + szName + "'", Severity().MEDIUM(), loc);
		}
	}

	std::any Get(std::string szName, const location& loc) {
		std::any out;
		if (!m_ar->environment->get(szName, out)) {
			throw ExceptionBuilder().Build(ExceptionTypes().UNRESOLVED_SYMBOL(), "unable to retrieve value with key '" + szName + "'", Severity().MEDIUM(), loc);
		}
		return out;
	}

	template <class Ty>
	Ty Get(std::string szName, const location& loc) {
		std::any out;
		if (!m_ar->environment->get(szName, out)) {
			throw ExceptionBuilder().Build(ExceptionTypes().UNRESOLVED_SYMBOL(), "unable to retrieve value with key '" + szName + "'", Severity().MEDIUM());
		}
		if (out.type() != typeid(Ty)) {
			throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "type mismatch in assertion type " + Utilities().getTypeString(out) + " != " + std::string(typeid(Ty).name()), Severity().HIGH());
		}
		return std::any_cast<Ty>(out);
	}

	template <typename Ty>
	Ty tryGet(const std::string& szKey, Ty defaultValue)
	{
		std::any out = nullptr;
		if (!m_ar->environment->get(szKey, out)) {
			return defaultValue;
		}

		if (out.type() != typeid(Ty)) {
			return defaultValue;
		}
		return std::any_cast<Ty>(out);
	}

	std::string toString()
	{
		return m_ar->environment->toString();
	}

	std::string getSignature()
	{
		return "class " + m_szName + " :r" + std::to_string(m_refIndex);
	}

	std::string getName()
	{
		return m_szName;
	}

	std::shared_ptr<activation_record> ar()
	{
		return m_ar;
	}

private:

	unsigned int m_refIndex{ 0 };
	std::string m_szName{ "" };
	std::shared_ptr<activation_record> m_ar;
};