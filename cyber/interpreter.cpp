#include "interpreter.h"


#include <sstream>

#include "exceptions.hpp"
#include "expression.h"
#include "tokenizer.hpp"
#include "parser.hpp"

#include "klass_instance.h"
#include "callable.h"
#include "context.h"
#include "Utilities.h"

#include "FileHandle.hpp"

interpreter::interpreter(
	std::shared_ptr<execution_context> context,
	std::shared_ptr<tokenizer> tokenizer,
	std::shared_ptr<parser> parser)
	:m_context{ context }, m_tokenizer{tokenizer}, m_parser{parser}
{
	Validate();
}

void interpreter::Validate()
{
	std::scoped_lock(m_mutex);

	if (m_context == nullptr || m_tokenizer == nullptr || m_parser == nullptr) {
		throw std::exception("interpreter held invalid data");
	}
}

void interpreter::CompleteImport(const std::string& szFile, const location& loc)
{
	std::scoped_lock(m_mutex);

	if (m_imports.count(szFile) && !m_imports[szFile]) {
		m_imports[szFile] = true;
		return;
	}
	throw ExceptionBuilder().Build(ExceptionTypes().IMPORT(), "unable to complete import of module '" + szFile + "'", Severity().HIGH(), loc);
}

bool interpreter::AddModule(const std::string& szFile)
{
	std::scoped_lock(m_mutex);

	if (m_imports.count(szFile)) {
		return !m_imports[szFile];
	}
	m_imports[szFile] = false;
	return true;
}

void interpreter::FlushImports()
{
	std::scoped_lock(m_mutex);

	m_imports.clear();
}

void interpreter::FlushImport(const std::string& szFile)
{
	std::scoped_lock(m_mutex);

	if (m_imports.count(szFile)) {
		m_imports[szFile] = 0;
	}
}


bool interpreter::isImported(const std::string& szFile)
{
	std::scoped_lock(m_mutex);

	if (m_imports.count(szFile)) {
		return m_imports[szFile];
	}
	return false;
}

std::shared_ptr<execution_context> interpreter::get_context()
{
	std::scoped_lock(m_mutex);

	return m_context;
}

std::shared_ptr<activation_record> interpreter::interpret(const std::string& data)
{
	std::scoped_lock(m_mutex);

	interpret(m_parser->parse(m_tokenizer->tokenize(data)));

	std::string entry = m_context->try_get_coalesce<std::string>("Language.Entry", "__main__");

	if (m_context->exists(entry)) {
		std::any __main__ = m_context->get(entry, location());
		std::shared_ptr<callable> hMain = Utilities().getCallable(__main__);
		hMain->call(shared_from_this(), _args());
	}

	return m_context->top();
}


std::shared_ptr<activation_record> interpreter::interpret(std::vector<std::shared_ptr<statement>> stmts)
{
	std::scoped_lock(m_mutex);

	for (unsigned int i{ 0 }; i < stmts.size(); i++) {
		acceptStatement(stmts.at(i));
	}
	return m_context->top();
}



void interpreter::acceptStatement(std::shared_ptr<statement> stmt) {
	std::scoped_lock(m_mutex);
	if (stmt != nullptr) {
		try {
			stmt->accept(std::static_pointer_cast<interpreter>(shared_from_this()));
		}
		catch (BreakException pe) {
			throw pe;
		}
		catch (ReturnException pe) {
			throw pe;
		}
		catch (PanicException pe) {
			pe.addStackTrace("error in " + stmt->getType(), stmt->getLocation());
			throw pe;
		}
		catch (ProgramException pe) {
			pe.addStackTrace("error in " + stmt->getType(), stmt->getLocation());
			throw pe;
		}
	}
}

void interpreter::acceptClassDeclaration(std::shared_ptr<class_declaration> class_decl)
{
	std::scoped_lock(m_mutex);

	std::shared_ptr<activation_record> env = acceptBlock_KeepEnvironment(class_decl->m_body);

	m_context->define(class_decl->m_szName, 
		std::make_shared<klass_definition>(class_decl->m_szName, env),
		false,
		class_decl->m_loc);
}

void interpreter::acceptFunctionDeclaration(std::shared_ptr<function_declaration> func_decl)
{
	std::scoped_lock(m_mutex);

	m_context->define(func_decl->m_szName, 
		std::make_shared<custom_fn>(func_decl->m_szName, m_context->current_ar(), func_decl->m_body->m_statements, func_decl->m_params, func_decl->m_loc), 
		false,
		func_decl->m_loc);
}


void interpreter::acceptVariableDeclaration(std::shared_ptr<variable_declaration> var_decl)
{
	std::scoped_lock(m_mutex);

	if (var_decl->m_var.default_value != nullptr) {
		std::any val = acceptExpression(var_decl->m_var.default_value);

		val = assert_or_convert_type(var_decl->m_var, val, var_decl->m_loc);
		m_context->define(var_decl->m_var.szName, val, false, var_decl->m_loc);
	} 
	else {
		// Here we avoid using param.class_specifier 
		// this is because custom class prototypes are not currently allowed/supported
		std::any val = m_context->getObjectPrototype(var_decl->m_var.szNativeType, var_decl->m_loc);
		m_context->define(var_decl->m_var.szName, val, false, var_decl->m_loc);
	}
}

void interpreter::acceptInjectStatement(std::shared_ptr<inject_statement> inject_stmt)
{
	std::scoped_lock(m_mutex);

	std::any inFile = acceptExpression(inject_stmt->m_expr);
	if (inFile.type() != typeid(std::string)) {
		throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "expect <expr> to resolve to filename in inject_statement", Severity().MEDIUM(), inject_stmt->m_loc);
	}
	std::string szInFile = FileHandle().absolute_path(std::any_cast<std::string>(inFile));
	if (!AddModule(szInFile)) {
		// if module is already imported, we skip re-importing it
		return;
	}
	std::string previous_wd = FileHandle().current_path();

	auto fs = m_context->tryGet<std::shared_ptr<klass_definition>>("FileSystem", nullptr);
	if (fs != nullptr) {
		previous_wd = fs->tryGet<std::string>("WorkingDirectory", FileHandle().current_path());
		fs->Define("WorkingDirectory", FileHandle().absolute_path(FileHandle().parent_path(szInFile)), inject_stmt->m_loc, true);
	}
	try {
		interpret(m_parser->parse(m_tokenizer->tokenize(FileHandle().readFileAsString(szInFile))));
		CompleteImport(szInFile, inject_stmt->m_loc);
	}
	catch (PanicException pe) {
		if (fs != nullptr) {
			fs->Define("WorkingDirectory", previous_wd, inject_stmt->m_loc, true);
		}
		throw pe;
	}
	catch (ProgramException pe) {
		if (fs != nullptr) {
			fs->Define("WorkingDirectory", previous_wd, inject_stmt->m_loc, true);
		}
		throw pe;
	}
	if (fs != nullptr) {
		fs->Define("WorkingDirectory", previous_wd, inject_stmt->m_loc, true);
	}
}

void interpreter::acceptReturnStatement(std::shared_ptr<return_statement> return_stmt)
{
	std::scoped_lock(m_mutex);

	throw ReturnException(acceptExpression(return_stmt->m_expr), return_stmt->m_loc);
}

void interpreter::acceptIfStatement(std::shared_ptr<if_statement> if_stmt)
{
	std::scoped_lock(m_mutex);

	if (Utilities().isTruthy(acceptExpression(if_stmt->m_condition))) {
		acceptStatement(if_stmt->m_then);
	}
	else {
		acceptStatement(if_stmt->m_elsethen); // Okay because nullptr is safe for acceptStatement()
	}
}


void interpreter::acceptWhileStatement(std::shared_ptr<while_statement> while_stmt)
{
	std::scoped_lock(m_mutex);

	while (Utilities().isTruthy(acceptExpression(while_stmt->m_condition))) {
		try {
			acceptStatement(while_stmt->m_then);
		}
		catch (BreakException) {
			break;
		}
	}
}

void interpreter::acceptBreakStatement(std::shared_ptr<break_statement> break_stmt)
{
	std::scoped_lock(m_mutex);

	throw BreakException(break_stmt->m_loc);
}


void interpreter::acceptDirectiveStatement(std::shared_ptr<directive_statement> directive_stmt)
{
	std::scoped_lock(m_mutex);

	throw ExceptionBuilder().Build(ExceptionTypes().NOT_SUPPORTED(), "NotSupportedException", Severity().HIGH(), directive_stmt->m_loc);
}

void interpreter::acceptBlock(std::shared_ptr<block> blk)
{
	std::scoped_lock(m_mutex);

	m_context->push_ar(std::to_string(m_arIndex));
	try {
		interpret(blk->m_statements);
	}
	catch (BreakException pe) {
		m_context->pop_ar();
		throw pe;
	}
	catch (ReturnException pe) {
		m_context->pop_ar();
		throw pe;
	}
	catch (PanicException pe) {
		m_context->pop_ar();
		throw pe;
	}
	catch (ProgramException pe) {
		m_context->pop_ar();
		throw pe;
	}
	m_context->pop_ar();
}


std::shared_ptr<activation_record> interpreter::acceptBlock_KeepEnvironment(std::shared_ptr<block> blk)
{
	std::scoped_lock(m_mutex);

	m_context->push_ar(std::to_string(m_arIndex));
	try {
		interpret(blk->m_statements);
	}
	catch (BreakException pe) {
		m_context->pop_ar();
		throw pe;
	}
	catch (ReturnException pe) {
		m_context->pop_ar();
		throw pe;
	}
	catch (PanicException pe) {
		m_context->pop_ar();
		throw pe;
	}
	catch (ProgramException pe) {
		m_context->pop_ar();
		throw pe;
	}

	return m_context->pop_ar();
}

void interpreter::acceptSwitchStatement(std::shared_ptr<switch_statement> switch_stmt)
{
	std::scoped_lock(m_mutex);

	std::any test = acceptExpression(switch_stmt->m_testValue);

	for (switch_case c : switch_stmt->m_cases) {
		bool matched = false;
		if (c.isDefault) {
			try {
				acceptStatement(c.then);
			}
			catch (BreakException) {
				break;
			}
			continue;
		}
		for (auto expr : c.cases) {
			std::any rhs = acceptExpression(expr);
			std::vector<std::any> arguments = { test, rhs };

			if (Utilities().isTruthy(m_context->getOperator("==", arguments)
				->call(std::static_pointer_cast<interpreter>(shared_from_this()), _args(arguments))))
			{
				matched = true;
				break;
			}
		}
		if (matched) {
			try {
				acceptStatement(c.then);
			}
			catch (BreakException) {
				break;
			}
		}
	}
	
}


void interpreter::acceptTryCatchStatement(std::shared_ptr<try_catch_statement> tc_stmt)
{
	std::scoped_lock(m_mutex);

	try {
		acceptStatement(tc_stmt->m_try);
	}
	catch (PanicException err) {
		bool caught{ false };
		for (auto c : tc_stmt->m_catches) {
			std::string errType = Utilities().getTypeString(err.value());
			// TODO refactor
			if ((c.first->m_var.szCustomType != "" && c.first->m_var.szCustomType == errType)
				|| c.first->m_var.szNativeType == errType) {
				caught = true;
				m_context->push_ar();
				m_context->define(c.first->m_var.szName, err.value(), false, c.first->getLocation());
				try {
					// this is so we don't nest blocks unneccessarily
					interpret(c.second->m_statements);
					m_context->pop_ar();
				}
				catch (BreakException pe) {
					m_context->pop_ar();
					throw pe;
				}
				catch (ReturnException pe) {
					m_context->pop_ar();
					throw pe;
				}
				catch (PanicException pe) {
					m_context->pop_ar();
					throw pe;
				}
				catch (ProgramException pe) {
					m_context->pop_ar();
					throw pe;
				}
			}
		}
		if (!caught) {
			throw err;
		}
	}
}


void interpreter::acceptRunRecoverStatement(std::shared_ptr<run_recover_statement> rr_stmt)
{
	std::scoped_lock(m_mutex);

	if (rr_stmt->m_szName != "") {
		m_context->define(rr_stmt->m_szName, nullptr, true, rr_stmt->m_loc);
	}
	try {
		acceptStatement(rr_stmt->m_try);
	}
	catch (PanicException err) {
		std::any val = err.value();
		std::string type = val.type().name();
		if (val.type() == typeid(klass_instance)) {
			type = std::any_cast<klass_instance>(val).getType();
		}
		if (rr_stmt->m_szTypename != "" && type != rr_stmt->m_szTypename) {
			throw err;
		}
		if (rr_stmt->m_szName != "") {
			m_context->define(rr_stmt->m_szName, val, true, rr_stmt->getLocation());
		}
	}
}

void interpreter::acceptPanicStatement(std::shared_ptr<panic_statement> panic_stmt)
{
	std::scoped_lock(m_mutex);

	std::any val = acceptExpression(panic_stmt->m_expr);
	throw PanicException(val, panic_stmt->m_loc);
}

void interpreter::acceptClassExtensionStatement(std::shared_ptr<class_extension> ce_stmt)
{
	std::scoped_lock(m_mutex);

	if (ce_stmt->m_func_decl == nullptr) {
		return;
	}
	std::any parent_klass = acceptExpression(ce_stmt->m_parent);
	std::shared_ptr<function_declaration> fn = ce_stmt->m_func_decl;

	if (parent_klass.type() == typeid(klass_instance)) {
		klass_instance instance = std::any_cast<klass_instance>(parent_klass);
		instance.Define(fn->m_szName,
			std::make_shared<custom_fn>(fn->m_szName, instance.ar(), fn->m_body->m_statements, fn->m_params, fn->m_loc),
			ce_stmt->m_loc,
			true
		);
	}
	else if (parent_klass.type() == typeid(std::shared_ptr<klass_definition>)) {
		std::shared_ptr<klass_definition> klass_def = std::any_cast<std::shared_ptr<klass_definition>>(parent_klass);
		klass_def->Define(fn->m_szName,
			std::make_shared<custom_fn>(fn->m_szName, klass_def->ar(), fn->m_body->m_statements, fn->m_params, fn->m_loc),
			ce_stmt->m_loc,
			true
		);
	}
	else {
		throw ExceptionBuilder().Build(ExceptionTypes().PRECOMPILE(), "expect klass_definition or klass_instance as extension parent but got " + Utilities().getTypeString(parent_klass), Severity().HIGH(), ce_stmt->m_loc);
	}
}



void interpreter::acceptExpressionStatement(std::shared_ptr<expression_statement> expr_stmt)
{
	std::scoped_lock(m_mutex);

	acceptExpression(expr_stmt->m_expr);
}


std::any interpreter::acceptExpression(std::shared_ptr<expression> expr)
{
	std::scoped_lock(m_mutex);

	if (expr == nullptr) {
		return nullptr;
	}
	try {
		return expr->visit(std::static_pointer_cast<interpreter>(shared_from_this()));
	}
	catch (PanicException pe) {
		pe.addStackTrace("error in " + expr->getType(), expr->getLocation());
		throw pe;
	}
	catch (ProgramException pe) {
		pe.addStackTrace("error in " + expr->getType(), expr->getLocation());
		throw pe;
	}
}

std::any interpreter::acceptAssignment(std::shared_ptr<assignment> assignmnt)
{
	std::scoped_lock(m_mutex);

	std::any val = acceptExpression(assignmnt->val);
	if (assignmnt->lhs != nullptr) {
		std::any lhs = acceptExpression(assignmnt->lhs);
		if (lhs.type() == typeid(klass_instance)) {// environment
			klass_instance instance = std::any_cast<klass_instance>(lhs);
			instance.Assign(assignmnt->name, val, assignmnt->m_loc);
			return val;
		}
		if (lhs.type() == typeid(std::shared_ptr<klass_definition>)) {// environment
			std::shared_ptr<klass_definition> instance = std::any_cast<std::shared_ptr<klass_definition>>(lhs);
			instance->Assign(assignmnt->name, val, assignmnt->m_loc);
			return val;
		}
		throw ExceptionBuilder().Build(ExceptionTypes().PRECOMPILE(), "invalid assignment target", Severity().HIGH(), assignmnt->m_loc);
	}
	else {
		m_context->assign(assignmnt->name, val, assignmnt->m_loc);
		return val;
	}
}

std::any interpreter::acceptLogicAnd(std::shared_ptr<logic_and> expr_logic_and)
{
	std::scoped_lock(m_mutex);

	return Utilities().isTruthy(acceptExpression(expr_logic_and->lhs)) && Utilities().isTruthy(acceptExpression(expr_logic_and->rhs));
}

std::any interpreter::acceptLogicOr(std::shared_ptr<logic_or> expr_logic_or)
{
	std::scoped_lock(m_mutex);

	return Utilities().isTruthy(acceptExpression(expr_logic_or->lhs)) || Utilities().isTruthy(acceptExpression(expr_logic_or->rhs));
}

std::any interpreter::acceptBinary(std::shared_ptr<binary> expr_binary)
{
	std::scoped_lock(m_mutex);

	std::any rhs = acceptExpression(expr_binary->rhs);
	std::any lhs = acceptExpression(expr_binary->lhs);

	std::vector<std::any> arguments = { lhs, rhs };

	return m_context->getOperator(expr_binary->op, { lhs, rhs })
		->call(std::static_pointer_cast<interpreter>(shared_from_this()), _args(arguments));
}


std::any interpreter::acceptUnary(std::shared_ptr<unary> expr_unary)
{
	std::scoped_lock(m_mutex);

	std::any rhs = acceptExpression(expr_unary->rhs);
	std::vector<std::any> arguments = { rhs };


	return m_context->getOperator(expr_unary->op, { rhs })
		->call(std::static_pointer_cast<interpreter>(shared_from_this()), _args(arguments));
}


std::any interpreter::acceptCall(std::shared_ptr<call> expr_call)
{
	std::scoped_lock(m_mutex);

	std::vector<std::any> arguments;
	for (unsigned int i{ 0 }; i < expr_call->arguments.size(); i++) {
		arguments.push_back(acceptExpression(expr_call->arguments.at(i)));
	}

	std::any callee = acceptExpression(expr_call->lhs);
	
	std::shared_ptr<callable> callee_internal = Utilities().getCallable(callee);

	return callee_internal->call(std::static_pointer_cast<interpreter>(shared_from_this()), _args(arguments));
}


std::any interpreter::acceptGet(std::shared_ptr<get> expr_get)
{
	std::scoped_lock(m_mutex);

	std::any lhs = acceptExpression(expr_get->lhs);
	
	if (lhs.type() == typeid(klass_instance)) {
		return std::any_cast<klass_instance>(lhs).Get(expr_get->identifier, expr_get->m_loc);
	}
	if (lhs.type() == typeid(std::shared_ptr<klass_definition>)) {
		return std::any_cast<std::shared_ptr<klass_definition>>(lhs)->Get(expr_get->identifier, expr_get->m_loc);
	}

	throw ExceptionBuilder().Build(ExceptionTypes().RUNTIME(), "Unable to perform get on non-container type", Severity().MEDIUM(), expr_get->m_loc);
}
std::any interpreter::acceptGroup(std::shared_ptr<group> expr_group)
{
	std::scoped_lock(m_mutex);

	return acceptExpression(expr_group->m_expr);
}

std::any interpreter::acceptIdentifier(std::shared_ptr<expr_identifier> identifier)
{
	std::scoped_lock(m_mutex);

	return m_context->get(identifier->name, identifier->m_loc);
}

std::any interpreter::acceptPrimary(std::shared_ptr<primary> expr_primary)
{
	std::scoped_lock(m_mutex);

	return expr_primary->data;
}
std::any interpreter::acceptCast(std::shared_ptr<cast> expr_cast)
{
	std::scoped_lock(m_mutex);

	std::any rhs = acceptExpression(expr_cast->rhs);
	std::vector<std::any> arguments = { rhs };


	return m_context->getOperator(Utilities().createOperatorSignature(expr_cast->op, rhs, expr_cast->szTypeName))
		->call(std::static_pointer_cast<interpreter>(shared_from_this()), _args(arguments));
}


std::any interpreter::acceptInitializer(std::shared_ptr<initializer> expr_intializer)
{
	std::scoped_lock(m_mutex);

	std::vector<std::any> args;
	for (auto arg : expr_intializer->arguments) {
		args.push_back(acceptExpression(arg));
	}
	std::any klass = acceptExpression(expr_intializer->expr);
	if (klass.type() != typeid(std::shared_ptr<klass_definition>)) {
		throw ExceptionBuilder().Build(ExceptionTypes().RUNTIME(), "expect valid class type in initializer", Severity().MEDIUM(), expr_intializer->m_loc);
	}
	std::shared_ptr<klass_definition> klass_def = std::any_cast<std::shared_ptr<klass_definition>>(klass);
	klass_instance ki = klass_def->create();
	
	std::shared_ptr<callable> constructor = Utilities().getCallable(ki.Get("constructor", expr_intializer->m_loc));
	constructor->call(std::static_pointer_cast<interpreter>(shared_from_this()), _args(args));
	return ki;
}

std::any interpreter::acceptListInitializer(std::shared_ptr<list_initializer> expr_list_initializer)
{
	std::scoped_lock(m_mutex);

	throw ExceptionBuilder().Build(ExceptionTypes().NOT_SUPPORTED(), "NotSupportedException", Severity().HIGH(), expr_list_initializer->m_loc);
}

std::any interpreter::acceptObjectLiteral(std::shared_ptr<object_literal> obj_lit)
{
	std::scoped_lock(m_mutex);

	std::shared_ptr<activation_record> env = acceptBlock_KeepEnvironment(std::make_shared<block>(obj_lit->statements, obj_lit->getLocation()));

	return klass_instance("klass_instance", "", env);
}


std::any interpreter::assert_or_convert_type(const param& p, std::any obj, const location& loc)
{
	std::scoped_lock(m_mutex);

	std::string szType = Utilities().getTypeString(obj);

	if (p.szCustomType.empty()) {
		if (obj.type().name() == p.szNativeType || p.szNativeType.empty()) {
			return obj;
		}
		else {
			// If there is a conversion function, call it
			std::string szPossibleOpSignature = Utilities().createOperatorSignature("::", obj, p.szNativeType);
			if (m_context->operatorExists(szPossibleOpSignature)) {
				std::cout<<"attempting conversion using" << szPossibleOpSignature<<std::endl;
				std::vector<std::any> arguments = { obj };
				std::any convertedVal = m_context->getOperator(szPossibleOpSignature)->call(std::static_pointer_cast<interpreter>(shared_from_this()), _args(arguments));
				if (convertedVal.type().name() == p.szNativeType) {
					return convertedVal;
				}
				// Even the conversion did not resolve the type correctly
				throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "Unable to convert type " + Utilities().getTypeString(obj) + " to " + p.szNativeType + "; conversion failed", Severity().MEDIUM(), loc);
			}

			// Otherwise throw a type_mismatch error
			throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "Type mismatch " + Utilities().getTypeString(obj) + " != " + p.szNativeType, Severity().MEDIUM(), loc);
		}
	}
	else {
		// We are looking for a custom type
		if (p.szNativeType == typeid(klass_instance).name()) {
			klass_instance instance = std::any_cast<klass_instance>(obj);
			if (instance.getType() == p.szCustomType) {
				return obj;
			}
			throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "Type mismatch " + Utilities().getTypeString(obj) + " != " + p.szCustomType, Severity().MEDIUM(), loc);
		}
		throw ExceptionBuilder().Build(ExceptionTypes().NOT_SUPPORTED(), "Custom typing with native type: " + p.szNativeType + " is not supported.", Severity().CRITICAL(), loc);
	}
}
