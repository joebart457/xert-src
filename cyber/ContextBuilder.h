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
#include "numeric_operators.h"
#include "stdlib.h"
#include "db_framework.h"
#include "parser.h"
#include "network_helper.h"

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

        // Std

		e->define("to_string", 
			std::make_shared<unary_fn>("to_string", to_string)
				->registerParameter(BuildParameter("")), 
			true
        );

		e->define("print", 
			std::make_shared<native_fn>("print", print)
				->registerParameter(BuildParameter("")), 
			true
        );

		e->define("typeof",
			std::make_shared<unary_fn>("typeof", type_of_any)
			->registerParameter(BuildParameter("")),
			true
        );

        // String

        std::shared_ptr<activation_record> string_ar = std::make_shared<activation_record>();
        string_ar->szAlias = "String";
        string_ar->environment = std::make_shared<scope<std::any>>();

        string_ar->environment->define("split",
            std::make_shared<native_fn>("split", string_split)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>()),
            true
        );

        string_ar->environment->define("rtrim",
            std::make_shared<native_fn>("rtrim", string_rtrim, string_ar)
            ->registerParameter(BuildParameter<std::string>()),
            true
        );

        string_ar->environment->define("ltrim",
            std::make_shared<native_fn>("ltrim", string_ltrim, string_ar)
            ->registerParameter(BuildParameter<std::string>()),
            true
        );

        string_ar->environment->define("trim",
            std::make_shared<native_fn>("trim", string_trim, string_ar)
            ->registerParameter(BuildParameter<std::string>()),
            true
        );

        string_ar->environment->define("create",
            std::make_shared<unary_fn>("create", to_string)
            ->registerParameter(BuildParameter("")),
            true
        );

        string_ar->environment->define("find",
            std::make_shared<native_fn>("find", string_find)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>()),
            true
        );

        string_ar->environment->define("substr",
            std::make_shared<native_fn>("substr", string_substr)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint64_t>()),
            true
        );

        string_ar->environment->define("pad",
            std::make_shared<native_fn>("pad", string_pad)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int64_t>()),
            true
        );

        string_ar->environment->define("get_char",
            std::make_shared<native_fn>("get_char", string_to_char)
            ->registerParameter(BuildParameter<std::string>()),
            true
        );

        e->define("String",
            std::make_shared<klass_definition>("String", string_ar),
            true
        );

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
        // winlib_env_ar->environment->define("hMod",
        //    0,
        //    true
        // );

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

        // Containers

        std::shared_ptr<activation_record> containers_ar = std::make_shared<activation_record>();
        containers_ar->szAlias = "Containers";
        containers_ar->environment = std::make_shared<scope<std::any>>();

        // List

		std::shared_ptr<activation_record> list_env_ar = std::make_shared<activation_record>();
		list_env_ar->szAlias = "list";
		list_env_ar->environment = std::make_shared<scope<std::any>>();

		list_env_ar->environment->define("push",
			std::make_shared<native_fn>("push", list_push, list_env_ar)->registerParameter(BuildParameter(""))
        );

		list_env_ar->environment->define("constructor",
			std::make_shared<native_fn>("constructor", list_constructor, list_env_ar)->setVariadic()
        );

		list_env_ar->environment->define("size",
			(uint64_t)0
        );

		


        // Map

        std::shared_ptr<activation_record> map_env_ar = std::make_shared<activation_record>();
        map_env_ar->szAlias = "map";
        map_env_ar->environment = std::make_shared<scope<std::any>>();

        map_env_ar->environment->define("add",
            std::make_shared<native_fn>("add", map_add, map_env_ar)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter(""))
        );

        map_env_ar->environment->define("remove",
            std::make_shared<native_fn>("remove", map_delete, map_env_ar)
            ->registerParameter(BuildParameter<std::string>())
        );

        map_env_ar->environment->define("constructor",
            std::make_shared<native_fn>("constructor", map_constructor, map_env_ar)
        );

        map_env_ar->environment->define("exists",
            std::make_shared<native_fn>("exists", map_exists, map_env_ar)
            ->registerParameter(BuildParameter<std::string>())
        );


        containers_ar->environment->define("map",
            std::make_shared<klass_definition>("map", map_env_ar),
            true
        );

        containers_ar->environment->define("list",
            std::make_shared<klass_definition>("list", list_env_ar),
            true
        );

        e->define("Containers",
            std::make_shared<klass_definition>("Containers", containers_ar),
            true
        );


        // End Containers

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
            ->registerParameter(BuildParameter<uint64_t>())
                
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
            ->registerParameter(BuildParameter<uint64_t>()),
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

        // Database 

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


        // Time

        std::shared_ptr<activation_record> time_ar = std::make_shared<activation_record>();
        time_ar->szAlias = "Time";
        time_ar->environment = std::make_shared<scope<std::any>>();

        e->define("timestamp",
            std::make_shared<native_fn>("timestamp", time_timestamp, time_ar),
            true
        );

        e->define("time_str",
            std::make_shared<native_fn>("time_str", time_timestamp_to_timestring, time_ar)
            ->registerParameter(BuildParameter<int64_t>()),
            true
        );

        e->define("time_str_f",
            std::make_shared<native_fn>("time_str_f", time_timestamp_to_timestring_f, time_ar)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<std::string>()),
            true
        );

        e->define("Time",
            std::make_shared<klass_definition>("Time", time_ar),
            true
        );

        // Language

        std::shared_ptr<activation_record> language_ar = std::make_shared<activation_record>();
        language_ar->szAlias = "Language";
        language_ar->environment = std::make_shared<scope<std::any>>();

        language_ar->environment->define("e",
            std::make_shared<native_fn>("e", print_environment, language_ar),
            true
        );

        language_ar->environment->define("o",
            std::make_shared<native_fn>("o", print_operators, language_ar),
            true
        );

        language_ar->environment->define("flush_imports",
            std::make_shared<native_fn>("flush_imports", flush_imports, language_ar),
            true
        );

        language_ar->environment->define("flush_import",
            std::make_shared<native_fn>("flush_import", flush_import, language_ar)
            ->registerParameter(BuildParameter<std::string>()),
            true
        );

        language_ar->environment->define("Version",
            INTERPRETER_VERSION + "." + PARSER_VERSION + "." + TOKENIZER_VERSION + "." + STD_LIB_VERSION,
            true
        );

        e->define("Language",
            std::make_shared<klass_definition>("Language", language_ar),
            true
        );


        // Network

        std::shared_ptr<activation_record> net_env_ar = std::make_shared<activation_record>();
        net_env_ar->szAlias = "Network";
        net_env_ar->environment = std::make_shared<scope<std::any>>();


        std::shared_ptr<activation_record> netclient_env_ar = std::make_shared<activation_record>();
        netclient_env_ar->szAlias = "NetClient";
        netclient_env_ar->environment = std::make_shared<scope<std::any>>();
       

        netclient_env_ar->environment->define("constructor",
            std::make_shared<native_fn>("constructor", net_create_client, netclient_env_ar)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter(""))
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<bool>())
        );

        netclient_env_ar->environment->define("Send",
            std::make_shared<native_fn>("Send", net_client_send, netclient_env_ar)
            ->registerParameter(BuildParameter(""))
        );

        netclient_env_ar->environment->define("IsConnected",
            std::make_shared<native_fn>("IsConnected", net_client_isconnected, netclient_env_ar),
            true
        );

        netclient_env_ar->environment->define("Connect",
            std::make_shared<native_fn>("Connect", net_client_connect, netclient_env_ar),
            true
        );

        netclient_env_ar->environment->define("Disconnect",
            std::make_shared<native_fn>("Disconnect", net_client_disconnect, netclient_env_ar),
            true
        );

        netclient_env_ar->environment->define("Start",
            std::make_shared<native_fn>("Start", net_client_start, netclient_env_ar),
            true
        );

        netclient_env_ar->environment->define("StartAsync",
            std::make_shared<native_fn>("StartAsync", net_client_start_async, netclient_env_ar),
            true
        );

        netclient_env_ar->environment->define("Port",
            std::make_shared<native_fn>("Port", net_client_port, netclient_env_ar),
            true
        );

        netclient_env_ar->environment->define("Host",
            std::make_shared<native_fn>("Host", net_client_host, netclient_env_ar),
            true
        );

        netclient_env_ar->environment->define("GetLastError",
            std::make_shared<native_fn>("GetLastError", net_client_getlasterror, netclient_env_ar),
            true
        );

        net_env_ar->environment->define("NetClient",
            std::make_shared<klass_definition>("NetClient", netclient_env_ar));

        /*
         raw will be defined just in createTCPClient not here
         
        netclient_env_ar->environment->define("raw",
            std::make_shared<NetClient>("127.0.0.1", 50000, nullptr, nullptr)
        );
        */

        std::shared_ptr<activation_record> netserver_env_ar = std::make_shared<activation_record>();
        netserver_env_ar->szAlias = "NetServer";
        netserver_env_ar->environment = std::make_shared<scope<std::any>>();

        netserver_env_ar->environment->define("constructor",
            std::make_shared<native_fn>("constructor", net_create_server, netserver_env_ar)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter(""))
            ->registerParameter(BuildParameter(""))
            ->registerParameter(BuildParameter(""))
            ->registerParameter(BuildParameter(""))
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<bool>())
        );

        netserver_env_ar->environment->define("MessageClient",
            std::make_shared<native_fn>("MessageClient", net_server_messageclient, netserver_env_ar)
            ->registerParameter(BuildParameter<std::shared_ptr<net::connection<MsgType>>>())
            ->registerParameter(BuildParameter(""))
        );

        netserver_env_ar->environment->define("MessageAll",
            std::make_shared<native_fn>("MessageAll", net_server_messageall, netserver_env_ar)
            ->registerParameter(BuildParameter(""))
        );

        netserver_env_ar->environment->define("GetClientById",
            std::make_shared<native_fn>("GetConnectionById", net_server_getconnectionbyid, netserver_env_ar)
            ->registerParameter(BuildParameter<uint32_t>())
        );
        netserver_env_ar->environment->define("Start",
            std::make_shared<native_fn>("Start", net_server_start, netserver_env_ar)
        );
        netserver_env_ar->environment->define("Stop",
            std::make_shared<native_fn>("Stop", net_server_stop, netserver_env_ar)
        );
        netserver_env_ar->environment->define("Update",
            std::make_shared<native_fn>("Update", net_server_update, netserver_env_ar)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<bool>())
        );

        netserver_env_ar->environment->define("GetLastError",
            std::make_shared<native_fn>("GetLastError", net_server_getlasterror, netserver_env_ar)
        );

        /*
         raw will be defined just in createTCPClient not here
        
        netserver_env_ar->environment->define("raw",
            std::make_shared<NetServer>(50000, nullptr, nullptr, nullptr, nullptr, nullptr)
        );
        */

        net_env_ar->environment->define("NetServer",
            std::make_shared<klass_definition>("NetServer", netserver_env_ar));

        e->define("Network",
            std::make_shared<klass_definition>("Network", net_env_ar)
        );

		return e;
	}

	static std::shared_ptr<interpreter> BuildInterpreter()
	{
        auto context = BuildExecutionContext();
        auto i = std::make_shared<interpreter>(context, BuildTokenizer(), BuildParser());

        auto systemNamespace = context->get<std::shared_ptr<klass_definition>>("System");

        auto listDefintion = context->get_coalesce<std::shared_ptr<klass_definition>>("Containers.list");
        auto lsInstance = listDefintion->create();
        std::vector<std::any> arguments;
        Utilities().getCallable(lsInstance.Get("constructor", location()))->call(i, _args(arguments));

        systemNamespace->Define("Args", lsInstance, location(), true);

        return i;
	}

    static std::shared_ptr<interpreter> BuildInterpreter(const std::string& szExecutionDir, std::vector<std::string> clArgs)
    {
        auto context = BuildExecutionContext();
        auto i = std::make_shared<interpreter>(context, BuildTokenizer(), BuildParser());
  
        auto systemNamespace = context->get<std::shared_ptr<klass_definition>>("System");
        auto fsNamespace = context->get<std::shared_ptr<klass_definition>>("FileSystem");

        fsNamespace->Define("WorkingDirectory", szExecutionDir, location(), true);
        auto listDefintion = context->get_coalesce<std::shared_ptr<klass_definition>>("Containers.list");
        auto lsInstance = listDefintion->create();
        
        std::vector<std::any> arguments;
        for (auto arg : clArgs) {
            arguments.push_back(arg);
        }

        Utilities().getCallable(lsInstance.Get("constructor", location()))->call(i, _args(arguments));

        systemNamespace->Define("Args", lsInstance, location(), true);
        
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
		
        // Custom Ops
        
        opHandler->registerOperator(
            std::make_shared<unary_fn>("|", type_of_any)
            ->registerParameter(BuildParameter(""))
        );

        /* Index map */

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_map_string)
            ->registerParameter(BuildParameter<klass_definition>("", "map"))
            ->registerParameter(BuildParameter<std::string>())
        );

        /* Index list */

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_list_int8_t)
            ->registerParameter(BuildParameter<klass_definition>("", "list"))
            ->registerParameter(BuildParameter<int8_t>())
        );

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_list_int16_t)
            ->registerParameter(BuildParameter<klass_definition>("", "list"))
            ->registerParameter(BuildParameter<int16_t>())
        );

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_list_int32_t)
            ->registerParameter(BuildParameter<klass_definition>("", "list"))
            ->registerParameter(BuildParameter<int32_t>())
        );

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_list_int64_t)
            ->registerParameter(BuildParameter<klass_definition>("", "list"))
            ->registerParameter(BuildParameter<int64_t>())
        );

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_list_uint8_t)
            ->registerParameter(BuildParameter<klass_definition>("", "list"))
            ->registerParameter(BuildParameter<uint8_t>())
        );

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_list_uint16_t)
            ->registerParameter(BuildParameter<klass_definition>("", "list"))
            ->registerParameter(BuildParameter<uint16_t>())
        );

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_list_uint32_t)
            ->registerParameter(BuildParameter<klass_definition>("", "list"))
            ->registerParameter(BuildParameter<uint32_t>())
        );

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_list_uint64_t)
            ->registerParameter(BuildParameter<klass_definition>("", "list"))
            ->registerParameter(BuildParameter<uint64_t>())
        );

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_list_string)
            ->registerParameter(BuildParameter<klass_definition>("", "list"))
            ->registerParameter(BuildParameter<std::string>())
        );

        /* Index String*/

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_string_int8_t)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<int8_t>())
        );

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_string_int16_t)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<int16_t>())
        );

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_string_int32_t)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<int32_t>())
        );

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_string_int64_t)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<int64_t>())
        );

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_string_uint8_t)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<uint8_t>())
        );

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_string_uint16_t)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<uint16_t>())
        );

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_string_uint32_t)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<uint32_t>())
        );

        opHandler->registerOperator(
            std::make_shared<binary_fn>("[", index_string_uint64_t)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<uint64_t>())
        );

        /* Cast string */

        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_string_int8_t)
            ->registerParameter(BuildParameter<std::string>()),
            "::(" + std::string(typeid(std::string).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );

        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_string_int16_t)
            ->registerParameter(BuildParameter<std::string>()),
            "::(" + std::string(typeid(std::string).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );

        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_string_int32_t)
            ->registerParameter(BuildParameter<std::string>()),
            "::(" + std::string(typeid(std::string).name()) + "," + std::string(typeid(int32_t).name()) + ")"

        );

        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_string_int64_t)
            ->registerParameter(BuildParameter<std::string>()),
            "::(" + std::string(typeid(std::string).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );

        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_string_uint8_t)
            ->registerParameter(BuildParameter<std::string>()),
            "::(" + std::string(typeid(std::string).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );

        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_string_uint16_t)
            ->registerParameter(BuildParameter<std::string>()),
            "::(" + std::string(typeid(std::string).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );

        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_string_uint32_t)
            ->registerParameter(BuildParameter<std::string>()),
            "::(" + std::string(typeid(std::string).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );

        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_string_uint64_t)
            ->registerParameter(BuildParameter<std::string>()),
            "::(" + std::string(typeid(std::string).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
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
            std::make_shared<unary_fn>("::", cast_string_string)
            ->registerParameter(BuildParameter<std::string>()),
            "::(" + std::string(typeid(std::string).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );

        /* Add string */

        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_string_string)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>())
        );

        /* Compare string */

        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_string_string)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>())
        );

        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_string_string)
            ->registerParameter(BuildParameter<std::string>())
            ->registerParameter(BuildParameter<std::string>())
        );

        /* Cast bool */

        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_bool_int8_t)
            ->registerParameter(BuildParameter<bool>()),
            "::(" + std::string(typeid(bool).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );

        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_bool_int16_t)
            ->registerParameter(BuildParameter<bool>()),
            "::(" + std::string(typeid(bool).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );

        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_bool_int32_t)
            ->registerParameter(BuildParameter<bool>()),
            "::(" + std::string(typeid(bool).name()) + "," + std::string(typeid(int32_t).name()) + ")"

        );

        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_bool_int64_t)
            ->registerParameter(BuildParameter<bool>()),
            "::(" + std::string(typeid(bool).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );

        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_bool_uint8_t)
            ->registerParameter(BuildParameter<bool>()),
            "::(" + std::string(typeid(bool).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );

        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_bool_uint16_t)
            ->registerParameter(BuildParameter<bool>()),
            "::(" + std::string(typeid(bool).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );

        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_bool_uint32_t)
            ->registerParameter(BuildParameter<bool>()),
            "::(" + std::string(typeid(bool).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );

        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_bool_uint64_t)
            ->registerParameter(BuildParameter<bool>()),
            "::(" + std::string(typeid(bool).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
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
            std::make_shared<unary_fn>("::", cast_bool_string)
            ->registerParameter(BuildParameter<bool>()),
            "::(" + std::string(typeid(bool).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );

        /* Compare bool */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_bool_bool)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_bool_bool)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", greaterthan_bool_bool)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_bool_bool)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_bool_bool)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<bool>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_bool_bool)
            ->registerParameter(BuildParameter<bool>())
            ->registerParameter(BuildParameter<bool>())
        );

        /* Unary */

        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_string)
            ->registerParameter(BuildParameter<std::string>())
        );

        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_null)
            ->registerParameter(BuildParameter<std::nullptr_t>())
        );
   

		// End Custom Operators

       /* START Auto-generation */
/*

int8_t

*/
/*

not

*/
        std::any not_int8_t(std::shared_ptr<interpreter> i, std::any& rhs);
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_int8_t)
            ->registerParameter(BuildParameter<int8_t>())
        );
        /*

        negate

        */
        std::any negate_int8_t(std::shared_ptr<interpreter> i, std::any& rhs);
        opHandler->registerOperator(
            std::make_shared<unary_fn>("-", negate_int8_t)
            ->registerParameter(BuildParameter<int8_t>())
        );
        /*

        int16_t

        */
        /*

        not

        */
        std::any not_int16_t(std::shared_ptr<interpreter> i, std::any& rhs);
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_int16_t)
            ->registerParameter(BuildParameter<int16_t>())
        );
        /*

        negate

        */
        std::any negate_int16_t(std::shared_ptr<interpreter> i, std::any& rhs);
        opHandler->registerOperator(
            std::make_shared<unary_fn>("-", negate_int16_t)
            ->registerParameter(BuildParameter<int16_t>())
        );
        /*

        int32_t

        */
        /*

        not

        */
        std::any not_int32_t(std::shared_ptr<interpreter> i, std::any& rhs);
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_int32_t)
            ->registerParameter(BuildParameter<int32_t>())
        );
        /*

        negate

        */
        std::any negate_int32_t(std::shared_ptr<interpreter> i, std::any& rhs);
        opHandler->registerOperator(
            std::make_shared<unary_fn>("-", negate_int32_t)
            ->registerParameter(BuildParameter<int32_t>())
        );
        /*

        int64_t

        */
        /*

        not

        */
        std::any not_int64_t(std::shared_ptr<interpreter> i, std::any& rhs);
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_int64_t)
            ->registerParameter(BuildParameter<int64_t>())
        );
        /*

        negate

        */
        std::any negate_int64_t(std::shared_ptr<interpreter> i, std::any& rhs);
        opHandler->registerOperator(
            std::make_shared<unary_fn>("-", negate_int64_t)
            ->registerParameter(BuildParameter<int64_t>())
        );
        /*

        uint8_t

        */
        /*

        not

        */
        std::any not_uint8_t(std::shared_ptr<interpreter> i, std::any& rhs);
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_uint8_t)
            ->registerParameter(BuildParameter<uint8_t>())
        );
        /*

        uint16_t

        */
        /*

        not

        */
        std::any not_uint16_t(std::shared_ptr<interpreter> i, std::any& rhs);
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_uint16_t)
            ->registerParameter(BuildParameter<uint16_t>())
        );
        /*

        uint32_t

        */
        /*

        not

        */
        std::any not_uint32_t(std::shared_ptr<interpreter> i, std::any& rhs);
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_uint32_t)
            ->registerParameter(BuildParameter<uint32_t>())
        );
        /*

        uint64_t

        */
        /*

        not

        */
        std::any not_uint64_t(std::shared_ptr<interpreter> i, std::any& rhs);
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_uint64_t)
            ->registerParameter(BuildParameter<uint64_t>())
        );
        /*

        float

        */
        /*

        not

        */
        std::any not_float(std::shared_ptr<interpreter> i, std::any& rhs);
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_float)
            ->registerParameter(BuildParameter<float>())
        );
        /*

        negate

        */
        std::any negate_float(std::shared_ptr<interpreter> i, std::any& rhs);
        opHandler->registerOperator(
            std::make_shared<unary_fn>("-", negate_float)
            ->registerParameter(BuildParameter<float>())
        );
        /*

        double

        */
        /*

        not

        */
        std::any not_double(std::shared_ptr<interpreter> i, std::any& rhs);
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_double)
            ->registerParameter(BuildParameter<double>())
        );
        /*

        negate

        */
        std::any negate_double(std::shared_ptr<interpreter> i, std::any& rhs);
        opHandler->registerOperator(
            std::make_shared<unary_fn>("-", negate_double)
            ->registerParameter(BuildParameter<double>())
        );



        /* Binary Operators*/


        /*

        int8_t

        */
        /*

        add

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int8_t_int8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int8_t_int16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int8_t_int32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int8_t_int64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int8_t_uint8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int8_t_uint16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int8_t_uint32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int8_t_uint64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int8_t_float)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int8_t_double)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        subtract

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int8_t_int8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int8_t_int16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int8_t_int32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int8_t_int64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int8_t_uint8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int8_t_uint16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int8_t_uint32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int8_t_uint64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int8_t_float)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int8_t_double)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        multiply

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int8_t_int8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int8_t_int16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int8_t_int32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int8_t_int64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int8_t_uint8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int8_t_uint16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int8_t_uint32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int8_t_uint64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int8_t_float)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int8_t_double)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        divide

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int8_t_int8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int8_t_int16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int8_t_int32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int8_t_int64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int8_t_uint8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int8_t_uint16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int8_t_uint32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int8_t_uint64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int8_t_float)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int8_t_double)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        lessthan

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int8_t_int8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int8_t_int16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int8_t_int32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int8_t_int64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int8_t_uint8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int8_t_uint16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int8_t_uint32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int8_t_uint64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int8_t_float)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int8_t_double)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        lessthanequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int8_t_int8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int8_t_int16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int8_t_int32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int8_t_int64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int8_t_uint8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int8_t_uint16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int8_t_uint32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int8_t_uint64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int8_t_float)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int8_t_double)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        greaterthan

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int8_t_int8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int8_t_int16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int8_t_int32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int8_t_int64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int8_t_uint8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int8_t_uint16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int8_t_uint32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int8_t_uint64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int8_t_float)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int8_t_double)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        greaterthanequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int8_t_int8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int8_t_int16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int8_t_int32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int8_t_int64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int8_t_uint8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int8_t_uint16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int8_t_uint32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int8_t_uint64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int8_t_float)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int8_t_double)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        equalequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int8_t_int8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int8_t_int16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int8_t_int32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int8_t_int64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int8_t_uint8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int8_t_uint16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int8_t_uint32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int8_t_uint64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int8_t_float)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int8_t_double)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        notequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int8_t_int8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int8_t_int16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int8_t_int32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int8_t_int64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int8_t_uint8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int8_t_uint16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int8_t_uint32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int8_t_uint64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int8_t_float)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int8_t_double)
            ->registerParameter(BuildParameter<int8_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        cast

        */
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_int8_t)
            ->registerParameter(BuildParameter<int8_t>()),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_int16_t)
            ->registerParameter(BuildParameter<int8_t>()),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_int32_t)
            ->registerParameter(BuildParameter<int8_t>()),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(int32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_int64_t)
            ->registerParameter(BuildParameter<int8_t>()),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_uint8_t)
            ->registerParameter(BuildParameter<int8_t>()),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_uint16_t)
            ->registerParameter(BuildParameter<int8_t>()),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_uint32_t)
            ->registerParameter(BuildParameter<int8_t>()),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_uint64_t)
            ->registerParameter(BuildParameter<int8_t>()),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_float)
            ->registerParameter(BuildParameter<int8_t>()),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_double)
            ->registerParameter(BuildParameter<int8_t>()),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_string)
            ->registerParameter(BuildParameter<int8_t>()),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_bool)
            ->registerParameter(BuildParameter<int8_t>()),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(bool).name()) + ")"
        );
        /*

        int16_t

        */
        /*

        add

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int16_t_int8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int16_t_int16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int16_t_int32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int16_t_int64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int16_t_uint8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int16_t_uint16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int16_t_uint32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int16_t_uint64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int16_t_float)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int16_t_double)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        subtract

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int16_t_int8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int16_t_int16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int16_t_int32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int16_t_int64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int16_t_uint8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int16_t_uint16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int16_t_uint32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int16_t_uint64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int16_t_float)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int16_t_double)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        multiply

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int16_t_int8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int16_t_int16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int16_t_int32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int16_t_int64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int16_t_uint8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int16_t_uint16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int16_t_uint32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int16_t_uint64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int16_t_float)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int16_t_double)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        divide

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int16_t_int8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int16_t_int16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int16_t_int32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int16_t_int64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int16_t_uint8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int16_t_uint16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int16_t_uint32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int16_t_uint64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int16_t_float)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int16_t_double)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        lessthan

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int16_t_int8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int16_t_int16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int16_t_int32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int16_t_int64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int16_t_uint8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int16_t_uint16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int16_t_uint32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int16_t_uint64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int16_t_float)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int16_t_double)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        lessthanequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int16_t_int8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int16_t_int16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int16_t_int32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int16_t_int64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int16_t_uint8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int16_t_uint16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int16_t_uint32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int16_t_uint64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int16_t_float)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int16_t_double)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        greaterthan

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int16_t_int8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int16_t_int16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int16_t_int32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int16_t_int64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int16_t_uint8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int16_t_uint16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int16_t_uint32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int16_t_uint64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int16_t_float)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int16_t_double)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        greaterthanequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int16_t_int8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int16_t_int16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int16_t_int32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int16_t_int64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int16_t_uint8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int16_t_uint16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int16_t_uint32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int16_t_uint64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int16_t_float)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int16_t_double)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        equalequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int16_t_int8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int16_t_int16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int16_t_int32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int16_t_int64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int16_t_uint8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int16_t_uint16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int16_t_uint32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int16_t_uint64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int16_t_float)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int16_t_double)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        notequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int16_t_int8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int16_t_int16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int16_t_int32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int16_t_int64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int16_t_uint8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int16_t_uint16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int16_t_uint32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int16_t_uint64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int16_t_float)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int16_t_double)
            ->registerParameter(BuildParameter<int16_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        cast

        */
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_int8_t)
            ->registerParameter(BuildParameter<int16_t>()),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_int16_t)
            ->registerParameter(BuildParameter<int16_t>()),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_int32_t)
            ->registerParameter(BuildParameter<int16_t>()),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(int32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_int64_t)
            ->registerParameter(BuildParameter<int16_t>()),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_uint8_t)
            ->registerParameter(BuildParameter<int16_t>()),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_uint16_t)
            ->registerParameter(BuildParameter<int16_t>()),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_uint32_t)
            ->registerParameter(BuildParameter<int16_t>()),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_uint64_t)
            ->registerParameter(BuildParameter<int16_t>()),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_float)
            ->registerParameter(BuildParameter<int16_t>()),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_double)
            ->registerParameter(BuildParameter<int16_t>()),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_string)
            ->registerParameter(BuildParameter<int16_t>()),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_bool)
            ->registerParameter(BuildParameter<int16_t>()),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(bool).name()) + ")"
        );
        /*

        int32_t

        */
        /*

        add

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int32_t_int8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int32_t_int16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int32_t_int32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int32_t_int64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int32_t_uint8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int32_t_uint16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int32_t_uint32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int32_t_uint64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int32_t_float)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int32_t_double)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        subtract

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int32_t_int8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int32_t_int16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int32_t_int32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int32_t_int64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int32_t_uint8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int32_t_uint16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int32_t_uint32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int32_t_uint64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int32_t_float)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int32_t_double)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        multiply

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int32_t_int8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int32_t_int16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int32_t_int32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int32_t_int64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int32_t_uint8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int32_t_uint16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int32_t_uint32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int32_t_uint64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int32_t_float)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int32_t_double)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        divide

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int32_t_int8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int32_t_int16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int32_t_int32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int32_t_int64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int32_t_uint8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int32_t_uint16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int32_t_uint32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int32_t_uint64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int32_t_float)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int32_t_double)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        lessthan

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int32_t_int8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int32_t_int16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int32_t_int32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int32_t_int64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int32_t_uint8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int32_t_uint16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int32_t_uint32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int32_t_uint64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int32_t_float)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int32_t_double)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        lessthanequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int32_t_int8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int32_t_int16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int32_t_int32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int32_t_int64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int32_t_uint8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int32_t_uint16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int32_t_uint32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int32_t_uint64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int32_t_float)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int32_t_double)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        greaterthan

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int32_t_int8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int32_t_int16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int32_t_int32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int32_t_int64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int32_t_uint8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int32_t_uint16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int32_t_uint32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int32_t_uint64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int32_t_float)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int32_t_double)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        greaterthanequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int32_t_int8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int32_t_int16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int32_t_int32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int32_t_int64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int32_t_uint8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int32_t_uint16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int32_t_uint32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int32_t_uint64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int32_t_float)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int32_t_double)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        equalequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int32_t_int8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int32_t_int16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int32_t_int32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int32_t_int64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int32_t_uint8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int32_t_uint16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int32_t_uint32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int32_t_uint64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int32_t_float)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int32_t_double)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        notequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int32_t_int8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int32_t_int16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int32_t_int32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int32_t_int64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int32_t_uint8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int32_t_uint16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int32_t_uint32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int32_t_uint64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int32_t_float)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int32_t_double)
            ->registerParameter(BuildParameter<int32_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        cast

        */
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_int8_t)
            ->registerParameter(BuildParameter<int32_t>()),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_int16_t)
            ->registerParameter(BuildParameter<int32_t>()),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_int32_t)
            ->registerParameter(BuildParameter<int32_t>()),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(int32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_int64_t)
            ->registerParameter(BuildParameter<int32_t>()),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_uint8_t)
            ->registerParameter(BuildParameter<int32_t>()),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_uint16_t)
            ->registerParameter(BuildParameter<int32_t>()),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_uint32_t)
            ->registerParameter(BuildParameter<int32_t>()),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_uint64_t)
            ->registerParameter(BuildParameter<int32_t>()),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_float)
            ->registerParameter(BuildParameter<int32_t>()),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_double)
            ->registerParameter(BuildParameter<int32_t>()),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_string)
            ->registerParameter(BuildParameter<int32_t>()),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_bool)
            ->registerParameter(BuildParameter<int32_t>()),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(bool).name()) + ")"
        );
        /*

        int64_t

        */
        /*

        add

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int64_t_int8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int64_t_int16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int64_t_int32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int64_t_int64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int64_t_uint8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int64_t_uint16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int64_t_uint32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int64_t_uint64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int64_t_float)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_int64_t_double)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        subtract

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int64_t_int8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int64_t_int16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int64_t_int32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int64_t_int64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int64_t_uint8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int64_t_uint16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int64_t_uint32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int64_t_uint64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int64_t_float)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_int64_t_double)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        multiply

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int64_t_int8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int64_t_int16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int64_t_int32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int64_t_int64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int64_t_uint8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int64_t_uint16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int64_t_uint32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int64_t_uint64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int64_t_float)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_int64_t_double)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        divide

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int64_t_int8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int64_t_int16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int64_t_int32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int64_t_int64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int64_t_uint8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int64_t_uint16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int64_t_uint32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int64_t_uint64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int64_t_float)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_int64_t_double)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        lessthan

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int64_t_int8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int64_t_int16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int64_t_int32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int64_t_int64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int64_t_uint8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int64_t_uint16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int64_t_uint32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int64_t_uint64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int64_t_float)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_int64_t_double)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        lessthanequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int64_t_int8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int64_t_int16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int64_t_int32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int64_t_int64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int64_t_uint8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int64_t_uint16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int64_t_uint32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int64_t_uint64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int64_t_float)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_int64_t_double)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        greaterthan

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int64_t_int8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int64_t_int16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int64_t_int32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int64_t_int64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int64_t_uint8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int64_t_uint16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int64_t_uint32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int64_t_uint64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int64_t_float)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_int64_t_double)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        greaterthanequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int64_t_int8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int64_t_int16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int64_t_int32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int64_t_int64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int64_t_uint8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int64_t_uint16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int64_t_uint32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int64_t_uint64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int64_t_float)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_int64_t_double)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        equalequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int64_t_int8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int64_t_int16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int64_t_int32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int64_t_int64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int64_t_uint8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int64_t_uint16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int64_t_uint32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int64_t_uint64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int64_t_float)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_int64_t_double)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        notequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int64_t_int8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int64_t_int16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int64_t_int32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int64_t_int64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int64_t_uint8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int64_t_uint16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int64_t_uint32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int64_t_uint64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int64_t_float)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_int64_t_double)
            ->registerParameter(BuildParameter<int64_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        cast

        */
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_int8_t)
            ->registerParameter(BuildParameter<int64_t>()),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_int16_t)
            ->registerParameter(BuildParameter<int64_t>()),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_int32_t)
            ->registerParameter(BuildParameter<int64_t>()),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(int32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_int64_t)
            ->registerParameter(BuildParameter<int64_t>()),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_uint8_t)
            ->registerParameter(BuildParameter<int64_t>()),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_uint16_t)
            ->registerParameter(BuildParameter<int64_t>()),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_uint32_t)
            ->registerParameter(BuildParameter<int64_t>()),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_uint64_t)
            ->registerParameter(BuildParameter<int64_t>()),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_float)
            ->registerParameter(BuildParameter<int64_t>()),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_double)
            ->registerParameter(BuildParameter<int64_t>()),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_string)
            ->registerParameter(BuildParameter<int64_t>()),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_bool)
            ->registerParameter(BuildParameter<int64_t>()),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(bool).name()) + ")"
        );
        /*

        uint8_t

        */
        /*

        add

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint8_t_int8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint8_t_int16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint8_t_int32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint8_t_int64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint8_t_uint8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint8_t_uint16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint8_t_uint32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint8_t_uint64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint8_t_float)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint8_t_double)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        subtract

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint8_t_int8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint8_t_int16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint8_t_int32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint8_t_int64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint8_t_uint8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint8_t_uint16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint8_t_uint32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint8_t_uint64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint8_t_float)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint8_t_double)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        multiply

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint8_t_int8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint8_t_int16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint8_t_int32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint8_t_int64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint8_t_uint8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint8_t_uint16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint8_t_uint32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint8_t_uint64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint8_t_float)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint8_t_double)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        divide

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint8_t_int8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint8_t_int16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint8_t_int32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint8_t_int64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint8_t_uint8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint8_t_uint16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint8_t_uint32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint8_t_uint64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint8_t_float)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint8_t_double)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        lessthan

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint8_t_int8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint8_t_int16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint8_t_int32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint8_t_int64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint8_t_uint8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint8_t_uint16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint8_t_uint32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint8_t_uint64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint8_t_float)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint8_t_double)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        lessthanequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint8_t_int8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint8_t_int16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint8_t_int32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint8_t_int64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint8_t_uint8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint8_t_uint16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint8_t_uint32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint8_t_uint64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint8_t_float)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint8_t_double)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        greaterthan

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint8_t_int8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint8_t_int16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint8_t_int32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint8_t_int64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint8_t_uint8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint8_t_uint16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint8_t_uint32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint8_t_uint64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint8_t_float)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint8_t_double)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        greaterthanequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint8_t_int8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint8_t_int16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint8_t_int32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint8_t_int64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint8_t_uint8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint8_t_uint16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint8_t_uint32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint8_t_uint64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint8_t_float)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint8_t_double)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        equalequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint8_t_int8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint8_t_int16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint8_t_int32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint8_t_int64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint8_t_uint8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint8_t_uint16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint8_t_uint32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint8_t_uint64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint8_t_float)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint8_t_double)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        notequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint8_t_int8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint8_t_int16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint8_t_int32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint8_t_int64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint8_t_uint8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint8_t_uint16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint8_t_uint32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint8_t_uint64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint8_t_float)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint8_t_double)
            ->registerParameter(BuildParameter<uint8_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        cast

        */
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_int8_t)
            ->registerParameter(BuildParameter<uint8_t>()),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_int16_t)
            ->registerParameter(BuildParameter<uint8_t>()),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_int32_t)
            ->registerParameter(BuildParameter<uint8_t>()),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(int32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_int64_t)
            ->registerParameter(BuildParameter<uint8_t>()),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_uint8_t)
            ->registerParameter(BuildParameter<uint8_t>()),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_uint16_t)
            ->registerParameter(BuildParameter<uint8_t>()),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_uint32_t)
            ->registerParameter(BuildParameter<uint8_t>()),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_uint64_t)
            ->registerParameter(BuildParameter<uint8_t>()),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_float)
            ->registerParameter(BuildParameter<uint8_t>()),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_double)
            ->registerParameter(BuildParameter<uint8_t>()),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_string)
            ->registerParameter(BuildParameter<uint8_t>()),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_bool)
            ->registerParameter(BuildParameter<uint8_t>()),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(bool).name()) + ")"
        );
        /*

        uint16_t

        */
        /*

        add

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint16_t_int8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint16_t_int16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint16_t_int32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint16_t_int64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint16_t_uint8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint16_t_uint16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint16_t_uint32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint16_t_uint64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint16_t_float)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint16_t_double)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        subtract

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint16_t_int8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint16_t_int16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint16_t_int32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint16_t_int64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint16_t_uint8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint16_t_uint16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint16_t_uint32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint16_t_uint64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint16_t_float)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint16_t_double)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        multiply

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint16_t_int8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint16_t_int16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint16_t_int32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint16_t_int64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint16_t_uint8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint16_t_uint16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint16_t_uint32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint16_t_uint64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint16_t_float)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint16_t_double)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        divide

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint16_t_int8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint16_t_int16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint16_t_int32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint16_t_int64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint16_t_uint8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint16_t_uint16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint16_t_uint32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint16_t_uint64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint16_t_float)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint16_t_double)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        lessthan

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint16_t_int8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint16_t_int16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint16_t_int32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint16_t_int64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint16_t_uint8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint16_t_uint16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint16_t_uint32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint16_t_uint64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint16_t_float)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint16_t_double)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        lessthanequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint16_t_int8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint16_t_int16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint16_t_int32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint16_t_int64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint16_t_uint8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint16_t_uint16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint16_t_uint32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint16_t_uint64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint16_t_float)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint16_t_double)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        greaterthan

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint16_t_int8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint16_t_int16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint16_t_int32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint16_t_int64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint16_t_uint8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint16_t_uint16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint16_t_uint32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint16_t_uint64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint16_t_float)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint16_t_double)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        greaterthanequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint16_t_int8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint16_t_int16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint16_t_int32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint16_t_int64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint16_t_uint8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint16_t_uint16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint16_t_uint32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint16_t_uint64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint16_t_float)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint16_t_double)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        equalequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint16_t_int8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint16_t_int16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint16_t_int32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint16_t_int64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint16_t_uint8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint16_t_uint16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint16_t_uint32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint16_t_uint64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint16_t_float)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint16_t_double)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        notequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint16_t_int8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint16_t_int16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint16_t_int32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint16_t_int64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint16_t_uint8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint16_t_uint16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint16_t_uint32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint16_t_uint64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint16_t_float)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint16_t_double)
            ->registerParameter(BuildParameter<uint16_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        cast

        */
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_int8_t)
            ->registerParameter(BuildParameter<uint16_t>()),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_int16_t)
            ->registerParameter(BuildParameter<uint16_t>()),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_int32_t)
            ->registerParameter(BuildParameter<uint16_t>()),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(int32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_int64_t)
            ->registerParameter(BuildParameter<uint16_t>()),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_uint8_t)
            ->registerParameter(BuildParameter<uint16_t>()),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_uint16_t)
            ->registerParameter(BuildParameter<uint16_t>()),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_uint32_t)
            ->registerParameter(BuildParameter<uint16_t>()),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_uint64_t)
            ->registerParameter(BuildParameter<uint16_t>()),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_float)
            ->registerParameter(BuildParameter<uint16_t>()),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_double)
            ->registerParameter(BuildParameter<uint16_t>()),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_string)
            ->registerParameter(BuildParameter<uint16_t>()),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_bool)
            ->registerParameter(BuildParameter<uint16_t>()),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(bool).name()) + ")"
        );
        /*

        uint32_t

        */
        /*

        add

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint32_t_int8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint32_t_int16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint32_t_int32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint32_t_int64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint32_t_uint8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint32_t_uint16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint32_t_uint32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint32_t_uint64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint32_t_float)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint32_t_double)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        subtract

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint32_t_int8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint32_t_int16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint32_t_int32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint32_t_int64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint32_t_uint8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint32_t_uint16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint32_t_uint32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint32_t_uint64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint32_t_float)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint32_t_double)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        multiply

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint32_t_int8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint32_t_int16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint32_t_int32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint32_t_int64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint32_t_uint8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint32_t_uint16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint32_t_uint32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint32_t_uint64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint32_t_float)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint32_t_double)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        divide

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint32_t_int8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint32_t_int16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint32_t_int32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint32_t_int64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint32_t_uint8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint32_t_uint16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint32_t_uint32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint32_t_uint64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint32_t_float)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint32_t_double)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        lessthan

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint32_t_int8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint32_t_int16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint32_t_int32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint32_t_int64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint32_t_uint8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint32_t_uint16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint32_t_uint32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint32_t_uint64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint32_t_float)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint32_t_double)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        lessthanequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint32_t_int8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint32_t_int16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint32_t_int32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint32_t_int64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint32_t_uint8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint32_t_uint16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint32_t_uint32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint32_t_uint64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint32_t_float)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint32_t_double)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        greaterthan

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint32_t_int8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint32_t_int16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint32_t_int32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint32_t_int64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint32_t_uint8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint32_t_uint16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint32_t_uint32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint32_t_uint64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint32_t_float)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint32_t_double)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        greaterthanequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint32_t_int8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint32_t_int16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint32_t_int32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint32_t_int64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint32_t_uint8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint32_t_uint16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint32_t_uint32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint32_t_uint64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint32_t_float)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint32_t_double)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        equalequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint32_t_int8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint32_t_int16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint32_t_int32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint32_t_int64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint32_t_uint8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint32_t_uint16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint32_t_uint32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint32_t_uint64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint32_t_float)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint32_t_double)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        notequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint32_t_int8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint32_t_int16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint32_t_int32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint32_t_int64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint32_t_uint8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint32_t_uint16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint32_t_uint32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint32_t_uint64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint32_t_float)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint32_t_double)
            ->registerParameter(BuildParameter<uint32_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        cast

        */
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_int8_t)
            ->registerParameter(BuildParameter<uint32_t>()),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_int16_t)
            ->registerParameter(BuildParameter<uint32_t>()),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_int32_t)
            ->registerParameter(BuildParameter<uint32_t>()),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(int32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_int64_t)
            ->registerParameter(BuildParameter<uint32_t>()),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_uint8_t)
            ->registerParameter(BuildParameter<uint32_t>()),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_uint16_t)
            ->registerParameter(BuildParameter<uint32_t>()),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_uint32_t)
            ->registerParameter(BuildParameter<uint32_t>()),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_uint64_t)
            ->registerParameter(BuildParameter<uint32_t>()),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_float)
            ->registerParameter(BuildParameter<uint32_t>()),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_double)
            ->registerParameter(BuildParameter<uint32_t>()),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_string)
            ->registerParameter(BuildParameter<uint32_t>()),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_bool)
            ->registerParameter(BuildParameter<uint32_t>()),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(bool).name()) + ")"
        );
        /*

        uint64_t

        */
        /*

        add

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint64_t_int8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint64_t_int16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint64_t_int32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint64_t_int64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint64_t_uint8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint64_t_uint16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint64_t_uint32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint64_t_uint64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint64_t_float)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_uint64_t_double)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        subtract

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint64_t_int8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint64_t_int16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint64_t_int32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint64_t_int64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint64_t_uint8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint64_t_uint16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint64_t_uint32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint64_t_uint64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint64_t_float)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_uint64_t_double)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        multiply

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint64_t_int8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint64_t_int16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint64_t_int32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint64_t_int64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint64_t_uint8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint64_t_uint16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint64_t_uint32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint64_t_uint64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint64_t_float)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_uint64_t_double)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        divide

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint64_t_int8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint64_t_int16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint64_t_int32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint64_t_int64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint64_t_uint8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint64_t_uint16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint64_t_uint32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint64_t_uint64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint64_t_float)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_uint64_t_double)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        lessthan

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint64_t_int8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint64_t_int16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint64_t_int32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint64_t_int64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint64_t_uint8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint64_t_uint16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint64_t_uint32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint64_t_uint64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint64_t_float)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_uint64_t_double)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        lessthanequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint64_t_int8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint64_t_int16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint64_t_int32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint64_t_int64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint64_t_uint8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint64_t_uint16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint64_t_uint32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint64_t_uint64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint64_t_float)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_uint64_t_double)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        greaterthan

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint64_t_int8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint64_t_int16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint64_t_int32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint64_t_int64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint64_t_uint8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint64_t_uint16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint64_t_uint32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint64_t_uint64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint64_t_float)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_uint64_t_double)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        greaterthanequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint64_t_int8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint64_t_int16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint64_t_int32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint64_t_int64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint64_t_uint8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint64_t_uint16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint64_t_uint32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint64_t_uint64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint64_t_float)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_uint64_t_double)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        equalequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint64_t_int8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint64_t_int16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint64_t_int32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint64_t_int64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint64_t_uint8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint64_t_uint16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint64_t_uint32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint64_t_uint64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint64_t_float)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_uint64_t_double)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        notequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint64_t_int8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint64_t_int16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint64_t_int32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint64_t_int64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint64_t_uint8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint64_t_uint16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint64_t_uint32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint64_t_uint64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<uint64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint64_t_float)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<float>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_uint64_t_double)
            ->registerParameter(BuildParameter<uint64_t>())
            ->registerParameter(BuildParameter<double>())
        );
        /*

        cast

        */
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_int8_t)
            ->registerParameter(BuildParameter<uint64_t>()),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_int16_t)
            ->registerParameter(BuildParameter<uint64_t>()),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_int32_t)
            ->registerParameter(BuildParameter<uint64_t>()),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(int32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_int64_t)
            ->registerParameter(BuildParameter<uint64_t>()),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_uint8_t)
            ->registerParameter(BuildParameter<uint64_t>()),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_uint16_t)
            ->registerParameter(BuildParameter<uint64_t>()),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_uint32_t)
            ->registerParameter(BuildParameter<uint64_t>()),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_uint64_t)
            ->registerParameter(BuildParameter<uint64_t>()),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_float)
            ->registerParameter(BuildParameter<uint64_t>()),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_double)
            ->registerParameter(BuildParameter<uint64_t>()),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_string)
            ->registerParameter(BuildParameter<uint64_t>()),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_bool)
            ->registerParameter(BuildParameter<uint64_t>()),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(bool).name()) + ")"
        );
        /*

        float

        */
        /*

        add

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_float_int8_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_float_int16_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_float_int32_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_float_int64_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_float_uint8_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_float_uint16_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_float_uint32_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_float_uint64_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint64_t>())
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
        /*

        subtract

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_float_int8_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_float_int16_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_float_int32_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_float_int64_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_float_uint8_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_float_uint16_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_float_uint32_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_float_uint64_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint64_t>())
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
        /*

        multiply

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_float_int8_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_float_int16_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_float_int32_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_float_int64_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_float_uint8_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_float_uint16_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_float_uint32_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_float_uint64_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint64_t>())
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
        /*

        divide

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_float_int8_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_float_int16_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_float_int32_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_float_int64_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_float_uint8_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_float_uint16_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_float_uint32_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_float_uint64_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint64_t>())
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
        /*

        lessthan

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_float_int8_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_float_int16_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_float_int32_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_float_int64_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_float_uint8_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_float_uint16_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_float_uint32_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_float_uint64_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint64_t>())
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
        /*

        lessthanequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_float_int8_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_float_int16_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_float_int32_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_float_int64_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_float_uint8_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_float_uint16_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_float_uint32_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_float_uint64_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint64_t>())
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
        /*

        greaterthan

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_float_int8_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_float_int16_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_float_int32_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_float_int64_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_float_uint8_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_float_uint16_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_float_uint32_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_float_uint64_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint64_t>())
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
        /*

        greaterthanequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_float_int8_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_float_int16_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_float_int32_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_float_int64_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_float_uint8_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_float_uint16_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_float_uint32_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_float_uint64_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint64_t>())
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
        /*

        equalequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_float_int8_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_float_int16_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_float_int32_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_float_int64_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_float_uint8_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_float_uint16_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_float_uint32_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_float_uint64_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint64_t>())
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
        /*

        notequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_float_int8_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_float_int16_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_float_int32_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_float_int64_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_float_uint8_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_float_uint16_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_float_uint32_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_float_uint64_t)
            ->registerParameter(BuildParameter<float>())
            ->registerParameter(BuildParameter<uint64_t>())
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
        /*

        cast

        */
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_int8_t)
            ->registerParameter(BuildParameter<float>()),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_int16_t)
            ->registerParameter(BuildParameter<float>()),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_int32_t)
            ->registerParameter(BuildParameter<float>()),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(int32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_int64_t)
            ->registerParameter(BuildParameter<float>()),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_uint8_t)
            ->registerParameter(BuildParameter<float>()),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_uint16_t)
            ->registerParameter(BuildParameter<float>()),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_uint32_t)
            ->registerParameter(BuildParameter<float>()),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_uint64_t)
            ->registerParameter(BuildParameter<float>()),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
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
            std::make_shared<unary_fn>("::", cast_float_string)
            ->registerParameter(BuildParameter<float>()),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_bool)
            ->registerParameter(BuildParameter<float>()),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(bool).name()) + ")"
        );
        /*

        double

        */
        /*

        add

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_double_int8_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_double_int16_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_double_int32_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_double_int64_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_double_uint8_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_double_uint16_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_double_uint32_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("+", add_double_uint64_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint64_t>())
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
        /*

        subtract

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_double_int8_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_double_int16_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_double_int32_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_double_int64_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_double_uint8_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_double_uint16_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_double_uint32_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("-", subtract_double_uint64_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint64_t>())
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
        /*

        multiply

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_double_int8_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_double_int16_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_double_int32_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_double_int64_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_double_uint8_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_double_uint16_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_double_uint32_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("*", multiply_double_uint64_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint64_t>())
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
        /*

        divide

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_double_int8_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_double_int16_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_double_int32_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_double_int64_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_double_uint8_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_double_uint16_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_double_uint32_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("/", divide_double_uint64_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint64_t>())
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
        /*

        lessthan

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_double_int8_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_double_int16_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_double_int32_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_double_int64_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_double_uint8_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_double_uint16_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_double_uint32_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<", lessthan_double_uint64_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint64_t>())
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
        /*

        lessthanequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_double_int8_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_double_int16_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_double_int32_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_double_int64_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_double_uint8_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_double_uint16_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_double_uint32_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("<=", lessthanequal_double_uint64_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint64_t>())
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
        /*

        greaterthan

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_double_int8_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_double_int16_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_double_int32_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_double_int64_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_double_uint8_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_double_uint16_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_double_uint32_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">", greaterthan_double_uint64_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint64_t>())
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
        /*

        greaterthanequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_double_int8_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_double_int16_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_double_int32_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_double_int64_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_double_uint8_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_double_uint16_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_double_uint32_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>(">=", greaterthanequal_double_uint64_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint64_t>())
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
        /*

        equalequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_double_int8_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_double_int16_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_double_int32_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_double_int64_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_double_uint8_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_double_uint16_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_double_uint32_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("==", equalequal_double_uint64_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint64_t>())
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
        /*

        notequal

        */
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_double_int8_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_double_int16_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_double_int32_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_double_int64_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<int64_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_double_uint8_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint8_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_double_uint16_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint16_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_double_uint32_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint32_t>())
        );
        opHandler->registerOperator(
            std::make_shared<binary_fn>("!=", notequal_double_uint64_t)
            ->registerParameter(BuildParameter<double>())
            ->registerParameter(BuildParameter<uint64_t>())
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
        /*

        cast

        */
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_int8_t)
            ->registerParameter(BuildParameter<double>()),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_int16_t)
            ->registerParameter(BuildParameter<double>()),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_int32_t)
            ->registerParameter(BuildParameter<double>()),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(int32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_int64_t)
            ->registerParameter(BuildParameter<double>()),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_uint8_t)
            ->registerParameter(BuildParameter<double>()),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_uint16_t)
            ->registerParameter(BuildParameter<double>()),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_uint32_t)
            ->registerParameter(BuildParameter<double>()),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_uint64_t)
            ->registerParameter(BuildParameter<double>()),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
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
            std::make_shared<unary_fn>("::", cast_double_string)
            ->registerParameter(BuildParameter<double>()),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_bool)
            ->registerParameter(BuildParameter<double>()),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(bool).name()) + ")"
        );
        /* END Auto-generation */
       
		
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
			tokenizer_rule(Keywords().BOOLTRUE(), "true"),
			tokenizer_rule(Keywords().BOOLFALSE(), "false"),
			tokenizer_rule(Keywords().NUL(), "null"),
			tokenizer_rule(Keywords().BREAK(), "break"),
			tokenizer_rule(Keywords().SWITCH(), "switch"),
			tokenizer_rule(Keywords().CASE(), "case"),
			tokenizer_rule(Keywords().DEFAULT(), "default"),
			tokenizer_rule(Keywords().RUN(), "run"),
			tokenizer_rule(Keywords().RECOVER(), "recover"),
            tokenizer_rule(Keywords().ON(), "on"),
            tokenizer_rule(Keywords().PANIC(), "panic"),
            tokenizer_rule(Keywords().EXTENSION(), "extension"),
            tokenizer_rule(Keywords().TRY(), "try"),
            tokenizer_rule(Keywords().CATCH(), "catch"),

            tokenizer_rule(Keywords().BOOL(), "bool"),
            tokenizer_rule(Keywords().CHAR(), "char", std::make_shared<std::string>(typeid(char).name())),
            tokenizer_rule(Keywords().STRING(), "string", std::make_shared<std::string>(typeid(std::string).name())),
            tokenizer_rule(Keywords().UINT8_T(), "uint8_t", std::make_shared<std::string>(typeid(uint8_t).name())),
            tokenizer_rule(Keywords().UINT16_T(), "uint16_t", std::make_shared<std::string>(typeid(uint16_t).name())),
            tokenizer_rule(Keywords().UINT32_T(), "uint32_t", std::make_shared<std::string>(typeid(uint32_t).name())),
            tokenizer_rule(Keywords().UINT64_T(), "uint64_t", std::make_shared<std::string>(typeid(uint64_t).name())),
            tokenizer_rule(Keywords().INT8_T(), "int8_t", std::make_shared<std::string>(typeid(int8_t).name())),
            tokenizer_rule(Keywords().INT16_T(), "int16_t", std::make_shared<std::string>(typeid(int16_t).name())),
            tokenizer_rule(Keywords().INT32_T(), "int32_t", std::make_shared<std::string>(typeid(int32_t).name())),
            tokenizer_rule(Keywords().INT64_T(), "int64_t", std::make_shared<std::string>(typeid(int64_t).name())),
            tokenizer_rule(Keywords().FLOAT_T(), "float_t", std::make_shared<std::string>(typeid(float).name())),
            tokenizer_rule(Keywords().DBLFLOAT_T(), "double_t", std::make_shared<std::string>(typeid(double).name())),

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