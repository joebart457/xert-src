#pragma once

#ifndef __INCLUDE_CONTEXT_BUILDER_H
#define __INCLUDE_CONTEXT_BUILDER_H

#include <memory>
#include <any>
#include <iostream>
#include <sstream>
#include <filesystem>

#include "db_helper.h"
#include "interpreter.h"
#include "environment.h"
#include "OperatorHandler.h"
#include "Keywords.h"
#include "context.h"
#include "tokenizer.hpp"
#include "klass_instance.h"

#include "operators.h"
#include "stdlib.h"
#include "db_framework.h"
#include "parser.h"

#include "BuildDefinitions.h"

#ifdef BUILD_WINDOWS
#include "win_std_lib.h"
#endif





// Operators




class ContextBuilder
{
public:
	static std::shared_ptr<scope<std::any>> BuildDefaultScope()
	{
		std::shared_ptr<scope<std::any>> e = std::make_shared<scope<std::any>>("default");
		e->define("to_string", 
			std::make_shared<unary_fn>("to_string", to_string)
				->registerParameter(BuildParameter("")), 
			true);

		e->define("print", 
			std::make_shared<native_fn>("print", print)
				->registerParameter(BuildParameter("")), 
			true);
		e->define("e",
			std::make_shared<native_fn>("e", print_environment),
			true);

		e->define("typeof",
			std::make_shared<unary_fn>("typeof", type_of_any)
			->registerParameter(BuildParameter("")),
			true);

        // System 

        std::shared_ptr<activation_record> sys_env_ar = std::make_shared<activation_record>();
        sys_env_ar->szAlias = "System";
        sys_env_ar->environment = std::make_shared<scope<std::any>>();

#ifdef BUILD_WINDOWS
        /* Windows */

        std::shared_ptr<activation_record> winlib_env_ar = std::make_shared<activation_record>();
        winlib_env_ar->szAlias = "lib";
        winlib_env_ar->environment = std::make_shared<scope<std::any>>();
        winlib_env_ar->environment->define("valid",
            std::make_shared<native_fn>("valid", win_lib_valid, winlib_env_ar),
            true
        );

        // hMod will be defined, but in its ctor not here
        //winlib_env_ar->environment->define("hMod",
        //    0,
        //    true
        //);

        winlib_env_ar->environment->define("constructor",
            std::make_shared<native_fn>("constructor", win_lib_constructor, winlib_env_ar)
            ->registerParameter(BuildParameter<std::string>()),
            true
        );

        winlib_env_ar->environment->define("get_function",
            std::make_shared<native_fn>("get_function", win_lib_get_function, winlib_env_ar)
            ->registerParameter(BuildParameter<std::string>()),
            true
        );

        sys_env_ar->environment->define("lib",
            std::make_shared<klass_definition>("lib", winlib_env_ar),
            true
        );



        /* End Windows */
#endif

        e->define("System",
            std::make_shared<klass_definition>("System", sys_env_ar),
            true);

        // End System

        // List

		std::shared_ptr<activation_record> list_env_ar = std::make_shared<activation_record>();
		list_env_ar->szAlias = "list";
		list_env_ar->environment = std::make_shared<scope<std::any>>();
		list_env_ar->environment->define("push",
			std::make_shared<native_fn>("push", list_push, list_env_ar)->registerParameter(BuildParameter("")));

		list_env_ar->environment->define("constructor",
			std::make_shared<native_fn>("constructor", list_constructor, list_env_ar)->setVariadic());

		list_env_ar->environment->define("size",
			(unsigned long)0);

		e->define("list",
			std::make_shared<klass_definition>("list", list_env_ar),
			true);

        // FileSystem

        std::shared_ptr<activation_record> fs_env_ar = std::make_shared<activation_record>();
        fs_env_ar->szAlias = "FileSystem";
        fs_env_ar->environment = std::make_shared<scope<std::any>>();
        fs_env_ar->environment->define("relative_path",
            std::make_shared<native_fn>("relative_path", fs_relative_path, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>())
        );
        fs_env_ar->environment->define("copy",
            std::make_shared<native_fn>("copy", fs_copy_file, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>())
        );
        fs_env_ar->environment->define("remove_all",
            std::make_shared<native_fn>("remove_all", fs_remove_all, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>())
        );
        fs_env_ar->environment->define("read",
            std::make_shared<native_fn>("read", fs_read_file, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>())
        );
        fs_env_ar->environment->define("read_line",
            std::make_shared<native_fn>("read_line", fs_read_line_from_file, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>())
        );
        fs_env_ar->environment->define("read_to_string",
            std::make_shared<native_fn>("read_to_string", fs_real_file_to_string, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>())
        );
        fs_env_ar->environment->define("write",
            std::make_shared<native_fn>("write", fs_write_to_file, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::vector<std::string>>())
            ->registerParameter(BuildParameter<bool>())
        );
        fs_env_ar->environment->define("write_line",
            std::make_shared<native_fn>("write_line", fs_write_line_to_file, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<bool>())
        );
        fs_env_ar->environment->define("count_lines",
            std::make_shared<native_fn>("count_lines", fs_count_lines, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>())
        );
        fs_env_ar->environment->define("current_path",
            std::make_shared<native_fn>("current_path", fs_current_path, fs_env_ar)
        );
        fs_env_ar->environment->define("parent_path",
            std::make_shared<native_fn>("parent_path", fs_parent_path, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>())
        );
        fs_env_ar->environment->define("absolute_path",
            std::make_shared<native_fn>("absolute_path", fs_absolute_path, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>())
        );
        fs_env_ar->environment->define("rename",
            std::make_shared<native_fn>("rename", fs_rename_file, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>())
        );
        fs_env_ar->environment->define("size",
            std::make_shared<native_fn>("size", fs_file_size, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>())
        );
        fs_env_ar->environment->define("exists",
            std::make_shared<native_fn>("exists", fs_exists, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>())
        );
        fs_env_ar->environment->define("replace_line",
            std::make_shared<native_fn>("replace_line", fs_replace_line, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<unsigned long>()),
            true
        );
        fs_env_ar->environment->define("make_unique",
            std::make_shared<native_fn>("make_unique", fs_get_unique_name, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>()),
            true
        );
        fs_env_ar->environment->define("WorkingDirectory",
            std::filesystem::current_path().string(),
            true
        );

        e->define("FileSystem",
            std::make_shared<klass_definition>("FileSystem", fs_env_ar),
            true);

		std::shared_ptr<activation_record> db_env_ar = std::make_shared<activation_record>();
		db_env_ar->szAlias = "db";
		db_env_ar->environment = std::make_shared<scope<std::any>>();
		db_env_ar->environment->define("open",
			std::make_shared<native_fn>("open", db_open, db_env_ar)->registerParameter(BuildParameter<std::string>()), true);

		db_env_ar->environment->define("run_prepared",
			std::make_shared<native_fn>("run_prepared", db_run_prepared_query, db_env_ar)
			->registerParameter(BuildParameter<std::string>())
			->registerParameter(BuildParameter<std::shared_ptr<klass_definition>>())
			->setVariadic()
			->setVariadicAfter(2), 
			true
		);


		std::shared_ptr<activation_record> db_env_dbtypes_ar = std::make_shared<activation_record>();
		db_env_dbtypes_ar->szAlias = "dbTypes";
		db_env_dbtypes_ar->environment = std::make_shared<scope<std::any>>();

		db_env_dbtypes_ar->environment->define("INTEGER", std::string("INTEGER"), true);
		db_env_dbtypes_ar->environment->define("REAL", std::string("REAL"), true);
		db_env_dbtypes_ar->environment->define("TEXT", std::string("TEXT"), true);

		db_env_ar->environment->define("Types",
			std::make_shared<klass_definition>("Types", db_env_dbtypes_ar), true);

		db_env_ar->environment->define("db",
			std::make_shared<db_helper>(),
			true);


		e->define("Database", 
			std::make_shared<klass_definition>("Database", db_env_ar),
			true);

		return e;
	}

	static std::shared_ptr<interpreter> BuildInterpreter()
	{
		return std::make_shared<interpreter>(BuildExecutionContext(), BuildTokenizer(), BuildParser());
	}

    static std::shared_ptr<interpreter> BuildInterpreter(const std::string& szExecutionDir, std::vector<std::string> clArgs)
    {
        auto context = BuildExecutionContext();
        auto i = std::make_shared<interpreter>(context, BuildTokenizer(), BuildParser());
  
        auto systemNamespace = context->get<std::shared_ptr<klass_definition>>("System");
        auto fsNamespace = context->get<std::shared_ptr<klass_definition>>("FileSystem");

        fsNamespace->Define("WorkingDirectory", szExecutionDir, location(), true);
        auto listDefintion = context->get<std::shared_ptr<klass_definition>>("list");
        auto lsInstance = listDefintion->create();
        
        std::vector<std::any> arguments;
        for (auto arg : clArgs) {
            arguments.push_back(arg);
        }
        systemNamespace->Define("Args", Utilities().getCallable(lsInstance.Get("constructor", location()))->call(i, _args(arguments)), location(), true);
        
        return i;
    }

	static std::shared_ptr<execution_context> BuildExecutionContext() 
	{
		std::shared_ptr<activation_record> default_ar = std::make_shared<activation_record>();
		default_ar->id = 0;
		default_ar->environment = BuildDefaultScope();
		return std::make_shared<execution_context>(default_ar, BuildOperatorHandler());
	}

    static std::shared_ptr<execution_context> BuildExecutionContext(const std::string& szExecutionDir)
    {
        std::shared_ptr<activation_record> default_ar = std::make_shared<activation_record>();
        default_ar->id = 0;
        default_ar->environment = BuildDefaultScope();
        auto context = std::make_shared<execution_context>(default_ar, BuildOperatorHandler());
        
    }

    static std::shared_ptr<parser> BuildParser()
    {
        return std::make_shared<parser>();
    }


	static std::shared_ptr<OperatorHandler> BuildOperatorHandler()
	{
		std::shared_ptr<OperatorHandler> opHandler = std::make_shared<OperatorHandler>();
		

        /*
         Neccessary for Auto Generation
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int_int)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<int>())
        );
        
        opHandler->registerOperator(
			std::make_shared<binary_fn>("<", lessthan_int_int)
			->registerParameter(BuildParameter<int>())
			->registerParameter(BuildParameter<int>())
		);
        
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_string_string)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>())
        );
        

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_list_int)
            ->registerParameter(BuildParameter<klass_definition>("", "list"))
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_string_string)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>())
        );

        */
		
        // Other Custom Ops

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_list_int)
            ->registerParameter(BuildParameter<klass_definition>("", "list"))
            ->registerParameter(BuildParameter<int>())
        );

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_list_unsignedlong)
            ->registerParameter(BuildParameter<klass_definition>("", "list"))
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_list_string)
            ->registerParameter(BuildParameter<klass_definition>("", "list"))
            ->registerParameter(BuildParameter<std::string>())
        );

		// End Custom Operators

       /* Auto Generated using op_create.scrwl */

        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_int)
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_unsignedlong)
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_float)
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_double)
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_bool)
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_string)
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_null)
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("-", negate_int)
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("-", negate_unsignedlong)
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("-", negate_float)
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("-", negate_double)
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("-", negate_bool)
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("-", negate_string)
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("-", negate_null)
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int_int)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int_unsignedlong)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int_float)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int_double)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int_bool)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int_string)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int_null)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_unsignedlong_int)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_unsignedlong_unsignedlong)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_unsignedlong_float)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_unsignedlong_double)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_unsignedlong_bool)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_unsignedlong_string)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_unsignedlong_null)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_float_int)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_float_unsignedlong)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_float_float)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_float_double)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_float_bool)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_float_string)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_float_null)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_double_int)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_double_unsignedlong)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_double_float)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_double_double)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_double_bool)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_double_string)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_double_null)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_bool_int)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_bool_unsignedlong)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_bool_float)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_bool_double)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_bool_bool)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_bool_string)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_bool_null)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_string_int)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_string_unsignedlong)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_string_float)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_string_double)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_string_bool)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_string_string)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_string_null)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_null_int)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_null_unsignedlong)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_null_float)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_null_double)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_null_bool)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_null_string)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_null_null)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int_int)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int_unsignedlong)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int_float)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int_double)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int_bool)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int_string)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int_null)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_unsignedlong_int)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_unsignedlong_unsignedlong)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_unsignedlong_float)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_unsignedlong_double)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_unsignedlong_bool)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_unsignedlong_string)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_unsignedlong_null)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_float_int)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_float_unsignedlong)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_float_float)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_float_double)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_float_bool)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_float_string)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_float_null)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_double_int)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_double_unsignedlong)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_double_float)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_double_double)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_double_bool)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_double_string)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_double_null)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_bool_int)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_bool_unsignedlong)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_bool_float)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_bool_double)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_bool_bool)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_bool_string)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_bool_null)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_string_int)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_string_unsignedlong)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_string_float)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_string_double)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_string_bool)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_string_string)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_string_null)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_null_int)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_null_unsignedlong)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_null_float)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_null_double)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_null_bool)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_null_string)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_null_null)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int_int)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int_unsignedlong)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int_float)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int_double)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int_bool)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int_string)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int_null)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_unsignedlong_int)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_unsignedlong_unsignedlong)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_unsignedlong_float)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_unsignedlong_double)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_unsignedlong_bool)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_unsignedlong_string)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_unsignedlong_null)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_float_int)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_float_unsignedlong)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_float_float)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_float_double)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_float_bool)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_float_string)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_float_null)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_double_int)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_double_unsignedlong)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_double_float)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_double_double)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_double_bool)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_double_string)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_double_null)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_bool_int)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_bool_unsignedlong)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_bool_float)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_bool_double)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_bool_bool)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_bool_string)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_bool_null)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_string_int)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_string_unsignedlong)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_string_float)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_string_double)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_string_bool)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_string_string)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_string_null)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_null_int)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_null_unsignedlong)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_null_float)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_null_double)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_null_bool)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_null_string)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_null_null)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int_int)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int_unsignedlong)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int_float)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int_double)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int_bool)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int_string)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int_null)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_unsignedlong_int)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_unsignedlong_unsignedlong)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_unsignedlong_float)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_unsignedlong_double)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_unsignedlong_bool)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_unsignedlong_string)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_unsignedlong_null)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_float_int)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_float_unsignedlong)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_float_float)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_float_double)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_float_bool)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_float_string)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_float_null)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_double_int)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_double_unsignedlong)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_double_float)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_double_double)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_double_bool)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_double_string)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_double_null)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_bool_int)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_bool_unsignedlong)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_bool_float)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_bool_double)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_bool_bool)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_bool_string)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_bool_null)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_string_int)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_string_unsignedlong)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_string_float)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_string_double)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_string_bool)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_string_string)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_string_null)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_null_int)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_null_unsignedlong)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_null_float)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_null_double)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_null_bool)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_null_string)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_null_null)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int_int)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int_unsignedlong)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int_float)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int_double)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int_bool)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int_string)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int_null)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_unsignedlong_int)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_unsignedlong_unsignedlong)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_unsignedlong_float)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_unsignedlong_double)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_unsignedlong_bool)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_unsignedlong_string)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_unsignedlong_null)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_float_int)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_float_unsignedlong)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_float_float)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_float_double)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_float_bool)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_float_string)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_float_null)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_double_int)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_double_unsignedlong)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_double_float)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_double_double)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_double_bool)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_double_string)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_double_null)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_bool_int)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_bool_unsignedlong)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_bool_float)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_bool_double)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_bool_bool)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_bool_string)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_bool_null)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_string_int)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_string_unsignedlong)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_string_float)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_string_double)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_string_bool)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_string_string)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_string_null)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_null_int)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_null_unsignedlong)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_null_float)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_null_double)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_null_bool)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_null_string)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_null_null)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int_int)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int_unsignedlong)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int_float)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int_double)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int_bool)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int_string)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int_null)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_unsignedlong_int)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_unsignedlong_unsignedlong)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_unsignedlong_float)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_unsignedlong_double)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_unsignedlong_bool)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_unsignedlong_string)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_unsignedlong_null)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_float_int)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_float_unsignedlong)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_float_float)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_float_double)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_float_bool)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_float_string)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_float_null)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_double_int)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_double_unsignedlong)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_double_float)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_double_double)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_double_bool)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_double_string)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_double_null)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_bool_int)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_bool_unsignedlong)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_bool_float)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_bool_double)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_bool_bool)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_bool_string)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_bool_null)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_string_int)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_string_unsignedlong)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_string_float)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_string_double)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_string_bool)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_string_string)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_string_null)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_null_int)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_null_unsignedlong)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_null_float)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_null_double)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_null_bool)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_null_string)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_null_null)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int_int)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int_unsignedlong)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int_float)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int_double)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int_bool)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int_string)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int_null)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_unsignedlong_int)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_unsignedlong_unsignedlong)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_unsignedlong_float)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_unsignedlong_double)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_unsignedlong_bool)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_unsignedlong_string)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_unsignedlong_null)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_float_int)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_float_unsignedlong)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_float_float)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_float_double)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_float_bool)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_float_string)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_float_null)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_double_int)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_double_unsignedlong)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_double_float)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_double_double)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_double_bool)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_double_string)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_double_null)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_bool_int)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_bool_unsignedlong)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_bool_float)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_bool_double)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_bool_bool)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_bool_string)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_bool_null)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_string_int)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_string_unsignedlong)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_string_float)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_string_double)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_string_bool)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_string_string)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_string_null)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_null_int)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_null_unsignedlong)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_null_float)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_null_double)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_null_bool)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_null_string)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_null_null)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int_int)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int_unsignedlong)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int_float)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int_double)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int_bool)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int_string)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int_null)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_unsignedlong_int)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_unsignedlong_unsignedlong)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_unsignedlong_float)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_unsignedlong_double)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_unsignedlong_bool)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_unsignedlong_string)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_unsignedlong_null)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_float_int)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_float_unsignedlong)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_float_float)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_float_double)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_float_bool)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_float_string)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_float_null)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_double_int)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_double_unsignedlong)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_double_float)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_double_double)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_double_bool)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_double_string)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_double_null)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_bool_int)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_bool_unsignedlong)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_bool_float)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_bool_double)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_bool_bool)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_bool_string)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_bool_null)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_string_int)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_string_unsignedlong)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_string_float)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_string_double)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_string_bool)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_string_string)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_string_null)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_null_int)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_null_unsignedlong)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_null_float)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_null_double)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_null_bool)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_null_string)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_null_null)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int_int)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int_unsignedlong)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int_float)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int_double)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int_bool)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int_string)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int_null)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_unsignedlong_int)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_unsignedlong_unsignedlong)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_unsignedlong_float)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_unsignedlong_double)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_unsignedlong_bool)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_unsignedlong_string)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_unsignedlong_null)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_float_int)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_float_unsignedlong)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_float_float)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_float_double)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_float_bool)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_float_string)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_float_null)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_double_int)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_double_unsignedlong)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_double_float)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_double_double)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_double_bool)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_double_string)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_double_null)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_bool_int)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_bool_unsignedlong)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_bool_float)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_bool_double)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_bool_bool)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_bool_string)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_bool_null)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_string_int)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_string_unsignedlong)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_string_float)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_string_double)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_string_bool)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_string_string)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_string_null)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_null_int)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_null_unsignedlong)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_null_float)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_null_double)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_null_bool)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_null_string)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_null_null)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int_int)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int_unsignedlong)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int_float)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int_double)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int_bool)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int_string)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int_null)
            ->registerParameter(BuildParameter<int>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_unsignedlong_int)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_unsignedlong_unsignedlong)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_unsignedlong_float)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_unsignedlong_double)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_unsignedlong_bool)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_unsignedlong_string)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_unsignedlong_null)
            ->registerParameter(BuildParameter<unsigned long>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_float_int)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_float_unsignedlong)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_float_float)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_float_double)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_float_bool)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_float_string)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_float_null)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_double_int)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_double_unsignedlong)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_double_float)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_double_double)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_double_bool)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_double_string)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_double_null)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_bool_int)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_bool_unsignedlong)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_bool_float)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_bool_double)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_bool_bool)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_bool_string)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_bool_null)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_string_int)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_string_unsignedlong)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_string_float)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_string_double)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_string_bool)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_string_string)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_string_null)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_null_int)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<int>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_null_unsignedlong)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<unsigned long>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_null_float)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_null_double)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<double>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_null_bool)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_null_string)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<std::string>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_null_null)
            ->registerParameter(BuildParameter<std::nullptr_t>())
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int_int)
            ->registerParameter(BuildParameter<int>()),
            "::(" + std::string(typeid(int).name()) + "," + std::string(typeid(int).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int_unsignedlong)
            ->registerParameter(BuildParameter<int>()),
            "::(" + std::string(typeid(int).name()) + "," + std::string(typeid(unsigned long).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int_float)
            ->registerParameter(BuildParameter<int>()),
            "::(" + std::string(typeid(int).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int_double)
            ->registerParameter(BuildParameter<int>()),
            "::(" + std::string(typeid(int).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int_bool)
            ->registerParameter(BuildParameter<int>()),
            "::(" + std::string(typeid(int).name()) + "," + std::string(typeid(bool).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int_string)
            ->registerParameter(BuildParameter<int>()),
            "::(" + std::string(typeid(int).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int_null)
            ->registerParameter(BuildParameter<int>()),
            "::(" + std::string(typeid(int).name()) + "," + std::string(typeid(std::nullptr_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_unsignedlong_int)
            ->registerParameter(BuildParameter<unsigned long>()),
            "::(" + std::string(typeid(unsigned long).name()) + "," + std::string(typeid(int).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_unsignedlong_unsignedlong)
            ->registerParameter(BuildParameter<unsigned long>()),
            "::(" + std::string(typeid(unsigned long).name()) + "," + std::string(typeid(unsigned long).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_unsignedlong_float)
            ->registerParameter(BuildParameter<unsigned long>()),
            "::(" + std::string(typeid(unsigned long).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_unsignedlong_double)
            ->registerParameter(BuildParameter<unsigned long>()),
            "::(" + std::string(typeid(unsigned long).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_unsignedlong_bool)
            ->registerParameter(BuildParameter<unsigned long>()),
            "::(" + std::string(typeid(unsigned long).name()) + "," + std::string(typeid(bool).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_unsignedlong_string)
            ->registerParameter(BuildParameter<unsigned long>()),
            "::(" + std::string(typeid(unsigned long).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_unsignedlong_null)
            ->registerParameter(BuildParameter<unsigned long>()),
            "::(" + std::string(typeid(unsigned long).name()) + "," + std::string(typeid(std::nullptr_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_int)
            ->registerParameter(BuildParameter<float>()),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(int).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_unsignedlong)
            ->registerParameter(BuildParameter<float>()),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(unsigned long).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_float)
            ->registerParameter(BuildParameter<float>()),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_double)
            ->registerParameter(BuildParameter<float>()),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_bool)
            ->registerParameter(BuildParameter<float>()),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(bool).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_string)
            ->registerParameter(BuildParameter<float>()),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_null)
            ->registerParameter(BuildParameter<float>()),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(std::nullptr_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_int)
            ->registerParameter(BuildParameter<double>()),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(int).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_unsignedlong)
            ->registerParameter(BuildParameter<double>()),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(unsigned long).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_float)
            ->registerParameter(BuildParameter<double>()),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_double)
            ->registerParameter(BuildParameter<double>()),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_bool)
            ->registerParameter(BuildParameter<double>()),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(bool).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_string)
            ->registerParameter(BuildParameter<double>()),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_null)
            ->registerParameter(BuildParameter<double>()),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(std::nullptr_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_bool_int)
            ->registerParameter(BuildParameter<bool>()),
            "::(" + std::string(typeid(bool).name()) + "," + std::string(typeid(int).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_bool_unsignedlong)
            ->registerParameter(BuildParameter<bool>()),
            "::(" + std::string(typeid(bool).name()) + "," + std::string(typeid(unsigned long).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_bool_float)
            ->registerParameter(BuildParameter<bool>()),
            "::(" + std::string(typeid(bool).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_bool_double)
            ->registerParameter(BuildParameter<bool>()),
            "::(" + std::string(typeid(bool).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_bool_bool)
            ->registerParameter(BuildParameter<bool>()),
            "::(" + std::string(typeid(bool).name()) + "," + std::string(typeid(bool).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_bool_string)
            ->registerParameter(BuildParameter<bool>()),
            "::(" + std::string(typeid(bool).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_bool_null)
            ->registerParameter(BuildParameter<bool>()),
            "::(" + std::string(typeid(bool).name()) + "," + std::string(typeid(std::nullptr_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_string_int)
            ->registerParameter(BuildParameter<std::string>()),
            "::(" + std::string(typeid(std::string).name()) + "," + std::string(typeid(int).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_string_unsignedlong)
            ->registerParameter(BuildParameter<std::string>()),
            "::(" + std::string(typeid(std::string).name()) + "," + std::string(typeid(unsigned long).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_string_float)
            ->registerParameter(BuildParameter<std::string>()),
            "::(" + std::string(typeid(std::string).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_string_double)
            ->registerParameter(BuildParameter<std::string>()),
            "::(" + std::string(typeid(std::string).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_string_bool)
            ->registerParameter(BuildParameter<std::string>()),
            "::(" + std::string(typeid(std::string).name()) + "," + std::string(typeid(bool).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_string_string)
            ->registerParameter(BuildParameter<std::string>()),
            "::(" + std::string(typeid(std::string).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_string_null)
            ->registerParameter(BuildParameter<std::string>()),
            "::(" + std::string(typeid(std::string).name()) + "," + std::string(typeid(std::nullptr_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_null_int)
            ->registerParameter(BuildParameter<std::nullptr_t>()),
            "::(" + std::string(typeid(std::nullptr_t).name()) + "," + std::string(typeid(int).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_null_unsignedlong)
            ->registerParameter(BuildParameter<std::nullptr_t>()),
            "::(" + std::string(typeid(std::nullptr_t).name()) + "," + std::string(typeid(unsigned long).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_null_float)
            ->registerParameter(BuildParameter<std::nullptr_t>()),
            "::(" + std::string(typeid(std::nullptr_t).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_null_double)
            ->registerParameter(BuildParameter<std::nullptr_t>()),
            "::(" + std::string(typeid(std::nullptr_t).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_null_bool)
            ->registerParameter(BuildParameter<std::nullptr_t>()),
            "::(" + std::string(typeid(std::nullptr_t).name()) + "," + std::string(typeid(bool).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_null_string)
            ->registerParameter(BuildParameter<std::nullptr_t>()),
            "::(" + std::string(typeid(std::nullptr_t).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_null_null)
            ->registerParameter(BuildParameter<std::nullptr_t>()),
            "::(" + std::string(typeid(std::nullptr_t).name()) + "," + std::string(typeid(std::nullptr_t).name()) + ")"
        );
        /* End Auto Generation */
		
		return opHandler;
	}

	static std::shared_ptr<tokenizer> BuildTokenizer()
	{
		const std::vector<tokenizer_rule> rules = {
			tokenizer_rule(Keywords().AND(), "&&"),
			tokenizer_rule(Keywords().OR(), "||"),
			tokenizer_rule(Keywords().TYPEOF(), "|"),
			tokenizer_rule(Keywords().CAST(), "::"),
			tokenizer_rule(Keywords().LPAREN(), "("),
			tokenizer_rule(Keywords().RPAREN(), ")"),
			tokenizer_rule(Keywords().LCURLY(), "{"),
			tokenizer_rule(Keywords().RCURLY(), "}"),
			tokenizer_rule(Keywords().LBRACKET(), "["),
			tokenizer_rule(Keywords().RBRACKET(), "]"),
			tokenizer_rule(Keywords().COMMA(), ","),
			tokenizer_rule(Keywords().SEMI(), ";"),
			tokenizer_rule(Keywords().DOT(), "."),
			tokenizer_rule(Keywords().EQUAL(), "="),
			tokenizer_rule(Keywords().EQUALEQUAL(), "=="),
			tokenizer_rule(Keywords().BANGEQUAL(), "!="),
			tokenizer_rule(Keywords().BANG(), "!"),
			tokenizer_rule(Keywords().SUBTRACT(), "-"),
			tokenizer_rule(Keywords().LESSTHAN(), "<"),
			tokenizer_rule(Keywords().LESSTHANEQUAL(), "<="),
			tokenizer_rule(Keywords().GREATERTHAN(), ">"),
			tokenizer_rule(Keywords().GREATERTHANEQUAL(), ">="),
			tokenizer_rule(Keywords().ADD(), "+"),
			tokenizer_rule(Keywords().ASTERISK(), "*"),
			tokenizer_rule(Keywords().BACKSLASH(), "/"),
			tokenizer_rule(Keywords().IF(), "if"),
			tokenizer_rule(Keywords().ELSE(), "else"),
			tokenizer_rule(Keywords().WHILE(), "while"),
			tokenizer_rule(Keywords().RETURN(), "return"),
			tokenizer_rule(Keywords().FUNCTION(), "function"),
			tokenizer_rule(Keywords().CLASS(), "class"),
			tokenizer_rule(Keywords().TRUE(), "true"),
			tokenizer_rule(Keywords().FALSE(), "false"),
			tokenizer_rule(Keywords().NUL(), "null"),
			tokenizer_rule(Keywords().BREAK(), "break"),
			tokenizer_rule(Keywords().SWITCH(), "switch"),
			tokenizer_rule(Keywords().CASE(), "case"),
			tokenizer_rule(Keywords().DEFAULT(), "default"),
			tokenizer_rule(Keywords().RUN(), "run"),
			tokenizer_rule(Keywords().RECOVER(), "recover"),
            tokenizer_rule(Keywords().ON(), "on"),
            tokenizer_rule(Keywords().PANIC(), "panic"),
            tokenizer_rule(Keywords().BOOL(), "bool"),


			/* types */
			tokenizer_rule(Keywords().UINT(), "uint", std::make_shared<std::string>(typeid(unsigned long).name())),
			tokenizer_rule(Keywords().INT(), "int", std::make_shared<std::string>(typeid(int).name())),
			tokenizer_rule(Keywords().FLOAT(), "float", std::make_shared<std::string>(typeid(float).name())),
			tokenizer_rule(Keywords().DOUBLE(), "double", std::make_shared<std::string>(typeid(double).name())),
			tokenizer_rule(Keywords().CHAR(), "char", std::make_shared<std::string>(typeid(char).name())),
			tokenizer_rule(Keywords().STRING(), "string", std::make_shared<std::string>(typeid(std::string).name())),
			tokenizer_rule(TOKEN_TYPE_WORD, "_ty", std::make_shared<std::string>("")),
			
			
			tokenizer_rule(Keywords().NEW(), "new"),
			tokenizer_rule(TOKEN_TYPE_EOL_COMMENT, "//"),
            tokenizer_rule(TOKEN_TYPE_ML_COMMENT_START, "/*"),
            tokenizer_rule(TOKEN_TYPE_ML_COMMENT_ENCLOSING, "*/"),
			tokenizer_rule(TOKEN_TYPE_STRING_ENCLOSING, "\""),
			tokenizer_rule(Keywords().INJECT(), "inject"),
			tokenizer_rule(Keywords().DIRECTIVE(), "@"),
			tokenizer_rule(Keywords().UPCARAT(), "^")
		};
		return std::make_shared<tokenizer>(rules);
	}

private:
	static param BuildParameter(std::string szType, std::string szName = "") {
		param p;
		p.name = szName;
		p.type = szType;
		return p;
	}

	template <typename Ty>
	static param BuildParameter(std::string szName = "", std::string class_specifier = "") {
		param p;
		p.name = szName;
		p.type = typeid(Ty).name();
		p.class_specifier = class_specifier;
		return p;
	}
};

#endif