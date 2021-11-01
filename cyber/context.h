#pragma once

#ifndef __INCLUDE_CONTEXT_H
#define __INCLUDE_CONTEXT_H

#include <memory>
#include <sstream>
#include <any>
#include <iostream>
#include <mutex>

#include "list_crawler.hpp"
#include "scope.h"
#include "location.h"
#include "exceptions.hpp"
#include "callable.h"
#include "operator_handler.h"
#include "Utilities.h"
#include "StringUtilities.h"


struct activation_record {
	unsigned int id{ 0 };
	std::string szAlias;
	std::shared_ptr<scope<std::any>> environment;
};



class execution_context {
public:
	execution_context(
		std::shared_ptr<activation_record> ar, 
		std::shared_ptr<operator_handler> opHandler)
		:m_opHandler{ opHandler }
	{
		push_ar(ar);
		if (m_opHandler == nullptr) {
			m_opHandler = std::make_shared<operator_handler>();
		}
	}
	~execution_context() {}

	void push_ar(std::string szAlias = "")
	{
		std::scoped_lock(m_mutex);

		activation_record ar;
		ar.id = m_index;
		ar.szAlias = szAlias;
		ar.environment = std::make_shared<scope<std::any>>(szAlias);
		push_ar(std::make_shared<activation_record>(ar));
	}

	void push_ar(std::shared_ptr<activation_record> ar)
	{
		std::scoped_lock(m_mutex);

		if (ar == nullptr) {
			ar = std::make_shared<activation_record>();
			ar->id = m_index;
			ar->environment = std::make_shared<scope<std::any>>("");
		}

		m_records.push_back(ar);
		m_index++;
		if (m_index >= MAX_CALLSTACK) {
			pop_ar();
			throw ExceptionBuilder().Build(ExceptionTypes().SYSTEM(), "stack overflow", Severity().CRITICAL());
		}
	}


	std::shared_ptr<activation_record> pop_ar()
	{
		std::scoped_lock(m_mutex);

		if (m_records.size() > 0 && m_index > 0) {
			std::shared_ptr<activation_record> ar = m_records.at(m_records.size() - 1);
			m_records.pop_back();
			m_index--;
			return ar;
		}
		throw std::exception("unable to pop activation record; none exist");
	}

	bool exists(const std::string& szKey)
	{
		std::scoped_lock(m_mutex);

		rlist_crawler<std::shared_ptr<activation_record>> crawler(m_records);
		while (!crawler.end()) {
			if (crawler.next()->environment->exists_local(szKey)) {
				return true;
			}
		}
		return false;
	}

	template <typename Ty>
	Ty get_coalesce(const std::string& szKey, const std::string& delim = ".")
	{
		std::scoped_lock(m_mutex);

		std::vector<std::string> matches = StringUtilities().split(szKey, delim);
		list_crawler<std::string> crwlMatches(matches);
		std::shared_ptr<activation_record> ar = nullptr;
		std::any obj = nullptr;
		for (unsigned int i{ 0 }; i < matches.size(); i++) {
			std::string key = matches.at(i);
			if (i > 0 && ar == nullptr) {
				throw ExceptionBuilder().Build(ExceptionTypes().UNRESOLVED_SYMBOL(), "unable to retrieve value with key '" + szKey + "'", Severity().MEDIUM());
			}
			if (ar == nullptr) {
				obj = get(key, location());
			}
			else {
				if (!ar->environment->get(key, obj)) {
					throw ExceptionBuilder().Build(ExceptionTypes().UNRESOLVED_SYMBOL(), "unable to retrieve value with key '" + szKey + "'", Severity().MEDIUM());
				}
			}
			ar = Utilities().extractScope(obj);
		}

		if (obj.type() != typeid(Ty)) {
			throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "type mismatch in assertion type " + Utilities().getTypeString(obj) + " != " + std::string(typeid(Ty).name()), Severity().HIGH());
		}
		return std::any_cast<Ty>(obj);
	}

	template <typename Ty>
	Ty try_get_coalesce(const std::string& szKey, Ty defaultValue, const std::string& delim = ".")
	{
		std::scoped_lock(m_mutex);

		std::vector<std::string> matches = StringUtilities().split(szKey, delim);
		list_crawler<std::string> crwlMatches(matches);
		std::shared_ptr<activation_record> ar = nullptr;
		std::any obj = nullptr;
		for (unsigned int i{ 0 }; i < matches.size(); i++) {
			std::string key = matches.at(i);
			if (i > 0 && ar == nullptr) {
				return defaultValue;
			}
			if (ar == nullptr) {
				obj = get(key, location());
			}
			else {
				if (!ar->environment->get(key, obj)) {
					return defaultValue;
				}
			}
			ar = Utilities().extractScope(obj);
		}

		if (obj.type() != typeid(Ty)) {
			return defaultValue;
		}
		return std::any_cast<Ty>(obj);
	}


	std::any get(const std::string& szKey, const location& loc)
	{
		std::scoped_lock(m_mutex);

		rlist_crawler<std::shared_ptr<activation_record>> crawler(m_records);
		while (!crawler.end()) {
			std::shared_ptr<activation_record> ar = crawler.next();
			std::any out;
			if (ar->environment->get(szKey, out)) {
				return out;
			}
		}
		throw ExceptionBuilder().Build(ExceptionTypes().UNRESOLVED_SYMBOL(), "unable to retrieve value with key '" + szKey + "'", Severity().MEDIUM(), loc);
	}
	
	template <typename Ty>
	Ty get(const std::string& szKey)
	{
		std::scoped_lock(m_mutex);

		std::any obj = get(szKey, location());
		if (obj.type() != typeid(Ty)) {
			throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "type mismatch in assertion type " + Utilities().getTypeString(obj) + " != " + std::string(typeid(Ty).name()), Severity().HIGH());
		}
		return std::any_cast<Ty>(obj);
	}

	std::shared_ptr<callable> get_callable(const std::string& szKey, const location& loc)
	{
		std::scoped_lock(m_mutex);

		rlist_crawler<std::shared_ptr<activation_record>> crawler(m_records);
		while (!crawler.end()) {
			std::shared_ptr<activation_record> ar = crawler.next();
			std::any out;
			if (ar->environment->get(szKey, out)) {
				return Utilities().getCallable(out);
			}
		}
		throw ExceptionBuilder().Build(ExceptionTypes().UNRESOLVED_SYMBOL(), "unable to retrieve value with key '" + szKey + "'", Severity().MEDIUM(), loc);
	}


	void assign(const std::string& szKey, std::any value, const location& loc)
	{
		std::scoped_lock(m_mutex);

		rlist_crawler<std::shared_ptr<activation_record>> crawler(m_records);
		while (!crawler.end()) {
			std::shared_ptr<activation_record> ar = crawler.next();
			if (ar->environment->assign(szKey, value)) {
				return;
			}
		}
		throw ExceptionBuilder().Build(ExceptionTypes().UNRESOLVED_SYMBOL(), "unable to assign value to key '" + szKey + "' key not found or type mismatch", Severity().MEDIUM());
	}
	

	void define(const std::string& szKey, std::any value, bool overwrite, const location& loc)
	{
		std::scoped_lock(m_mutex);

		rlist_crawler<std::shared_ptr<activation_record>> crawler(m_records);
		while (!crawler.end()) {
			std::shared_ptr<activation_record> ar = crawler.next();
			if (ar->environment->define(szKey, value, overwrite)) {
				return;
			}
		}
		throw ExceptionBuilder().Build(ExceptionTypes().VARIABLE_REDEFINITION(), "unable to define value for key '" + szKey + "' key already defined", Severity().MEDIUM());
	}

	bool remove(const std::string& szKey)
	{
		std::scoped_lock(m_mutex);

		return current_ar()->environment->remove(szKey);
	}

	
	void output(const std::string& exclude = "")
	{
		std::scoped_lock(m_mutex);

		for (unsigned int i{ 0 }; i < m_records.size(); i++) {
			std::cout << toString(*m_records.at(i), exclude) << "\n";
		}
	}

	void output_operators(const std::string& exclude = "")
	{
		std::scoped_lock(m_mutex);

		m_opHandler->output();
	}

	std::shared_ptr<activation_record> top()
	{
		std::scoped_lock(m_mutex);

		rlist_crawler<std::shared_ptr<activation_record>> crawler(m_records);
		return crawler.back();
	}


	std::shared_ptr<activation_record> current_ar()
	{
		std::scoped_lock(m_mutex);

		if (m_records.size() == 0) throw ExceptionBuilder().Build(ExceptionTypes().SYSTEM(), "no activation record to execute", Severity().CRITICAL());
		return m_records.at(m_records.size() - 1);
	}


	std::shared_ptr<callable> getOperator(const std::string& szName)
	{
		std::scoped_lock(m_mutex);

		return m_opHandler->getOperator(szName);
	}

	std::shared_ptr<callable> getOperator(const std::string& szName, std::vector<std::any> args)
	{
		std::scoped_lock(m_mutex);

		return m_opHandler->getOperator(Utilities().createOperatorSignature(szName, args));
	}

	bool operatorExists(const std::string& szName)
	{
		std::scoped_lock(m_mutex);

		return m_opHandler->exists(szName);
	}

	bool operatorExists(const std::string& szName, std::vector<std::any> args) 
	{
		std::scoped_lock(m_mutex);

		return m_opHandler->exists(Utilities().createOperatorSignature(szName, args));
	}

	std::any getObjectPrototype(const std::string& szTypename, const location& loc)
	{
		std::scoped_lock(m_mutex);

		return this->get(PROTO_PREFIX + szTypename, loc);
	}


	template <typename Ty>
	Ty tryGet(const std::string& szKey, Ty defaultValue)
	{
		std::scoped_lock(m_mutex);

		std::any out = nullptr;
		rlist_crawler<std::shared_ptr<activation_record>> crawler(m_records);
		while (!crawler.end()) {
			std::shared_ptr<activation_record> ar = crawler.next();
			if (ar->environment->get(szKey, out)) {
				break;
			}
		}

		if (out.type() != typeid(Ty)) {
			return defaultValue;
		}
		return std::any_cast<Ty>(out);
	}

private:

	std::string toString(const activation_record& ar, const std::string& exclude = "")
	{
		std::scoped_lock(m_mutex);
		std::ostringstream oss;
		oss << "<" << ar.szAlias << ":" << ar.id << ">";
		oss << "\r\n\t" << ar.environment->toString();
		oss << "\r\n</" << (ar.szAlias.empty() ? ":" + std::to_string(ar.id) : ar.szAlias) << ">";
		return oss.str();
	}


	const unsigned int MAX_CALLSTACK{ 100 };
	const std::string PROTO_PREFIX{ "__proto__" };

	unsigned int m_index{ 0 };
	std::vector<std::shared_ptr<activation_record>> m_records;
	std::shared_ptr<operator_handler> m_opHandler{ nullptr };
	std::mutex m_mutex;
};

#endif