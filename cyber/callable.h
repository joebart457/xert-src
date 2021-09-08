#pragma once

#ifndef __INCLUDE_CALLABLE_H
#define __INCLUDE_CALLABLE_H

#include <any>
#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "statement.h"
#include "exceptions.h" 
#include "location.h"

#include "BuildDefinitions.h"

class interpreter;
struct activation_record;

class _args
{
public:
	_args(std::vector<std::any>& data)
	{
		m_data = data;
	}
	_args(){}
	~_args(){}

	std::any& at(unsigned int index)
	{
		return m_data.at(index);
	}

	std::vector<std::any> subset(unsigned int offset_front, unsigned int offset_back = 0) {
		return std::vector<std::any>(m_data.begin() + offset_front, m_data.end() + offset_back);
	}

	size_t size()
	{
		return m_data.size();
	}

	template <typename _Ty>
	_Ty get(unsigned int index)
	{
		if (index < m_data.size()) {
			if (m_data.at(index).type() != typeid(_Ty)) {
				throw ProgramException("unable to retrieve object from callable arguments; type mismatch "
					+std::string(m_data.at(index).type().name())+" != "+std::string(typeid(_Ty).name()), location());
			}
			return std::any_cast<_Ty>(m_data.at(index));
		}
		throw ProgramException("index out of range "+std::to_string(m_data.size())+" < "+std::to_string(index), location());
	}

private:
	std::vector<std::any> m_data;
};


class callable :
	public std::enable_shared_from_this<callable>
{
public:
	callable(std::string szName)
		:m_szName{ szName }{}
	callable(std::string szName, std::vector<param> params)
		:m_szName{ szName }, m_params{ params } {}

	virtual std::any call(std::shared_ptr<interpreter> c, _args arguments) = 0;

	virtual std::string getSignature();

protected:
	std::string m_szName{ "" };
	std::vector<param> m_params;
};


typedef std::any( *func)(std::shared_ptr<interpreter>, _args);

class native_fn :
	public callable {
public:
	native_fn(std::string szName, func fn, std::shared_ptr<activation_record> enclosing = nullptr)
		:callable(szName), m_hFn{ fn }, m_enclosing{ enclosing } {}
	native_fn(native_fn& fn)
		:callable(fn.m_szName, fn.m_params), m_hFn{ fn.m_hFn }, m_enclosing{ fn.m_enclosing }, m_variadic{ fn.m_variadic }, m_variadic_after{ fn.m_variadic_after } {}
	~native_fn() {}

	std::any call(std::shared_ptr<interpreter> c, _args args);

	void setEnclosing(std::shared_ptr<activation_record> ar);
	std::shared_ptr<native_fn> setVariadic();
	std::shared_ptr<native_fn> setVariadicAfter(unsigned int index);

	std::shared_ptr<native_fn> registerParameter(const param& p);

private:
	func m_hFn;
	std::shared_ptr<activation_record> m_enclosing{ nullptr };
	bool m_variadic{ false };
	unsigned int m_variadic_after{ 0 };
};


class custom_fn :
	public callable {
public:
	custom_fn(std::string szName, std::shared_ptr<activation_record> ar, std::vector<std::shared_ptr<statement>> body, std::vector<param> parameters, const location& loc)
		:callable{ szName, parameters }, m_enclosing{ ar }, m_body{ body }, m_loc{ loc } {}
	custom_fn(custom_fn& fn)
		:callable{ fn.m_szName, fn.m_params }, m_enclosing{ fn.m_enclosing }, m_body{ fn.m_body }, m_loc{ fn.m_loc }{}

	~custom_fn() {}

	std::any call(std::shared_ptr<interpreter> c, _args arguments);

	void setEnclosing(std::shared_ptr<activation_record> ar);
private:
	std::shared_ptr<activation_record> m_enclosing;
	std::vector<std::shared_ptr<statement>> m_body;
	location m_loc;
};


typedef std::any(*unary_func)(std::shared_ptr<interpreter>, std::any&);


class unary_fn :
	public callable {
public:
	unary_fn(std::string szName, unary_func fn)
		:callable(szName), m_hFn{ fn } {}
	~unary_fn() {}

	std::any call(std::shared_ptr<interpreter> c, _args args);


	std::shared_ptr<callable> registerParameter(const param& p);

	virtual std::string getSignature();


private:
	unary_func m_hFn;
	param m_param;
};



typedef std::any(*binary_func)(std::shared_ptr<interpreter>, std::any&, std::any&);

class binary_fn :
	public callable {
public:
	binary_fn(std::string szName, binary_func fn)
		:callable(szName), m_hFn{ fn } {}
	~binary_fn() {}

	std::any call(std::shared_ptr<interpreter> c, _args args);

	std::shared_ptr<binary_fn> registerParameter(const param& p);

private:
	binary_func m_hFn;
};

#ifdef BUILD_WINDOWS

typedef std::any(__stdcall *hFunc)(std::shared_ptr<interpreter>, _args);

class loaded_native_fn :
	public callable {
public:
	loaded_native_fn(std::string szName, hFunc fn, std::shared_ptr<activation_record> enclosing = nullptr)
		:callable(szName), m_hFn{ fn }, m_enclosing{ enclosing } {}
	loaded_native_fn(loaded_native_fn& fn)
		:callable(fn.m_szName, fn.m_params), m_hFn{ fn.m_hFn }, m_enclosing{ fn.m_enclosing }, m_variadic{ fn.m_variadic }, m_variadic_after{ fn.m_variadic_after } {}
	~loaded_native_fn() {}

	std::any call(std::shared_ptr<interpreter> c, _args args);

	void setEnclosing(std::shared_ptr<activation_record> ar);
	std::shared_ptr<loaded_native_fn> setVariadic();
	std::shared_ptr<loaded_native_fn> setVariadicAfter(unsigned int index);

	std::shared_ptr<loaded_native_fn> registerParameter(const param& p);

private:
	hFunc m_hFn;
	std::shared_ptr<activation_record> m_enclosing{ nullptr };
	bool m_variadic{ false };
	unsigned int m_variadic_after{ 0 };
};
#endif

#endif