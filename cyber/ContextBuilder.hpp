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
#include "operator_handler.h"
#include "Keywords.hpp"
#include "context.h"
#include "tokenizer.hpp"
#include "klass_instance.h"

#include "operators.h"
#include "numeric_operators.h"
#include "stdlib.h"
#include "parser.hpp"
#include "network_helper.h"
#include "Colors.hpp"
#include "clArgs.hpp"

#include "BuildDefinitions.hpp"

#ifdef BUILD_WINDOWS
#include "win_std_lib.h"
#endif


class ContextBuilder
{
public:
	static std::shared_ptr<scope<std::any>> BuildDefaultScope()
	{
		std::shared_ptr<scope<std::any>> e = std::make_shared<scope<std::any>>("default");

        // Std

		e->define("to_string", 
			std::make_shared<unary_fn>("to_string", to_string)
				->registerParameter(BuildParameter(""))
                ->returns<std::string>(), 
			true
        );

		e->define("print", 
			std::make_shared<native_fn>("print", print)
				->setVariadic(), 
			true
        );

		e->define("typeof",
			std::make_shared<unary_fn>("typeof", type_of_any)
			->registerParameter(BuildParameter("")),
			true
        );

        // Thread

        std::shared_ptr<activation_record> thread_ar = std::make_shared<activation_record>();
        thread_ar->szAlias = "Thread";
        thread_ar->environment = std::make_shared<scope<std::any>>();

        std::shared_ptr<activation_record> thread_safe_result_ar = std::make_shared<activation_record>();
        thread_safe_result_ar->szAlias = "SafeResult";
        thread_safe_result_ar->environment = std::make_shared<scope<std::any>>();

        thread_safe_result_ar->environment->define("result", nullptr, true);
        thread_safe_result_ar->environment->define("bHadError", false, true);
        thread_safe_result_ar->environment->define("error", std::string(""), true);

        thread_ar->environment->define("SafeResult",
            std::make_shared<klass_definition>("SafeResult", thread_safe_result_ar),
            true
        );

        thread_ar->environment->define("Sleep",
            std::make_shared<native_fn>("Sleep", thread_sleep, thread_ar)
            ->registerParameter(BuildParameter<uint64_t>("milliseconds")),
            true
        );

        thread_ar->environment->define("constructor",
            std::make_shared<native_fn>("constructor", thread_constructor, thread_ar)
            ->registerParameter(BuildParameter("", "callee"))
            ->setVariadic()
            ->setVariadicAfter(0),
            true
        );

        thread_ar->environment->define("Join",
            std::make_shared<native_fn>("Join", thread_join, thread_ar),
            true
        );

        thread_ar->environment->define("Joinable",
            std::make_shared<native_fn>("Joinable", thread_joinable, thread_ar)
            ->returns<bool>(),
            true
        );

        thread_ar->environment->define("Detach",
            std::make_shared<native_fn>("Detach", thread_detach, thread_ar),
            true
        );

        thread_ar->environment->define("GetId",
            std::make_shared<native_fn>("GetId", thread_get_id, thread_ar)
            ->returns<std::string>(),
            true
        );

        e->define("Thread",
            std::make_shared<klass_definition>("Thread", thread_ar),
            true
        );

        // Null

        std::shared_ptr<activation_record> null_ar = std::make_shared<activation_record>();
        null_ar->szAlias = "Null";
        null_ar->environment = std::make_shared<scope<std::any>>();

        null_ar->environment->define("IsNullType",
            std::make_shared<native_fn>("IsNullType", null_isNullType)
            ->registerParameter(BuildParameter("", "object")),
            true
        );

        e->define("Null",
            std::make_shared<klass_definition>("Null", null_ar)
        );

        // String

        std::shared_ptr<activation_record> string_ar = std::make_shared<activation_record>();
        string_ar->szAlias = "String";
        string_ar->environment = std::make_shared<scope<std::any>>();

        string_ar->environment->define("Split",
            std::make_shared<native_fn>("Split", string_split)
            ->registerParameter(BuildParameter<std::string>("source"))
            ->registerParameter(BuildParameter<std::string>("delimiter"))
        );

        string_ar->environment->define("Rtrim",
            std::make_shared<native_fn>("Rtrim", string_rtrim, string_ar)
            ->registerParameter(BuildParameter<std::string>("source"))
        );

        string_ar->environment->define("Ltrim",
            std::make_shared<native_fn>("Ltrim", string_ltrim, string_ar)
            ->registerParameter(BuildParameter<std::string>("source"))
        );

        string_ar->environment->define("Trim",
            std::make_shared<native_fn>("Trim", string_trim, string_ar)
            ->registerParameter(BuildParameter<std::string>("source"))
        );

        string_ar->environment->define("Create",
            std::make_shared<unary_fn>("Create", to_string)
            ->registerParameter(BuildParameter("","object")),
            true
        );

        string_ar->environment->define("Find",
            std::make_shared<native_fn>("Find", string_find)
            ->registerParameter(BuildParameter<std::string>("source"))
            ->registerParameter(BuildParameter<std::string>("search")),
            true
        );

        string_ar->environment->define("SubString",
            std::make_shared<native_fn>("SubString", string_substr)
            ->registerParameter(BuildParameter<std::string>("source"))
            ->registerParameter(BuildParameter<uint64_t>("from"))
            ->registerParameter(BuildParameter<uint64_t>("to")),
            true
        );

        string_ar->environment->define("Pad",
            std::make_shared<native_fn>("Pad", string_pad)
            ->registerParameter(BuildParameter<std::string>("source"))
            ->registerParameter(BuildParameter<uint8_t>("pad"))
            ->registerParameter(BuildParameter<int64_t>("width")),
            true
        );

        string_ar->environment->define("Char",
            std::make_shared<native_fn>("Char", string_to_char)
            ->registerParameter(BuildParameter<std::string>("source")),
            true
        );

        string_ar->environment->define("Length",
            std::make_shared<native_fn>("Length", string_length)
            ->registerParameter(BuildParameter<std::string>("source")),
            true
        );

        e->define("String",
            std::make_shared<klass_definition>("String", string_ar),
            true
        );

        // End String

        // Console

        std::shared_ptr<activation_record> console_env_ar = std::make_shared<activation_record>();
        console_env_ar->szAlias = "Console";
        console_env_ar->environment = std::make_shared<scope<std::any>>();

        console_env_ar->environment->define("Write",
            std::make_shared<native_fn>("Write", console_write)
            ->registerParameter(BuildParameter("", "object")),
            true
        );

        console_env_ar->environment->define("WriteLine",
            std::make_shared<native_fn>("WriteLine", console_writeline)
            ->registerParameter(BuildParameter("", "object")),
            true
        );

        console_env_ar->environment->define("ReadKey",
            std::make_shared<native_fn>("ReadKey", console_readKey),
            true
        );

        console_env_ar->environment->define("ReadLine",
            std::make_shared<native_fn>("ReadLine", console_readLine),
            true
        );

        e->define("Console",
            std::make_shared<klass_definition>("Console", console_env_ar),
            true);

        // End Console

        // Colors

        std::shared_ptr<activation_record> colors_env_ar = std::make_shared<activation_record>();
        colors_env_ar->szAlias = "Colors";
        colors_env_ar->environment = std::make_shared<scope<std::any>>();

        colors_env_ar->environment->define("BLACK", BLACK, true);
        colors_env_ar->environment->define("BLUE", BLUE, true);
        colors_env_ar->environment->define("GREEN", GREEN, true);
        colors_env_ar->environment->define("CYAN", CYAN, true);
        colors_env_ar->environment->define("RED", RED, true);
        colors_env_ar->environment->define("MAGENTA", MAGENTA, true);
        colors_env_ar->environment->define("BROWN", BROWN, true);
        colors_env_ar->environment->define("LIGHTGRAY", LIGHTGRAY, true);
        colors_env_ar->environment->define("DARKGRAY", DARKGRAY, true);
        colors_env_ar->environment->define("LIGHTBLUE", LIGHTBLUE, true);
        colors_env_ar->environment->define("LIGHTCYAN", LIGHTCYAN, true);
        colors_env_ar->environment->define("LIGHTRED", LIGHTRED, true);
        colors_env_ar->environment->define("LIGHTMAGENTA", LIGHTMAGENTA, true);
        colors_env_ar->environment->define("YELLOW", YELLOW, true);
        colors_env_ar->environment->define("WHITE", WHITE, true);
        
        colors_env_ar->environment->define("BLACK_B", BLACK_B, true);
        colors_env_ar->environment->define("BLUE_B", BLUE_B, true);
        colors_env_ar->environment->define("GREEN_B", GREEN_B, true);
        colors_env_ar->environment->define("CYAN_B", CYAN_B, true);
        colors_env_ar->environment->define("RED_B", RED_B, true);
        colors_env_ar->environment->define("MAGENTA_B", MAGENTA_B, true);
        colors_env_ar->environment->define("BROWN_B", BROWN_B, true);
        colors_env_ar->environment->define("LIGHTGRAY_B", LIGHTGRAY_B, true);
        colors_env_ar->environment->define("DARKGRAY_B", DARKGRAY_B, true);
        colors_env_ar->environment->define("LIGHTBLUE_B", LIGHTBLUE_B, true);
        colors_env_ar->environment->define("LIGHTCYAN_B", LIGHTCYAN_B, true);
        colors_env_ar->environment->define("LIGHTRED_B", LIGHTRED_B, true);
        colors_env_ar->environment->define("LIGHTMAGENTA_B", LIGHTMAGENTA_B, true);
        colors_env_ar->environment->define("YELLOW_B", YELLOW_B, true);
        colors_env_ar->environment->define("WHITE_B", WHITE_B, true);

        e->define("Colors",
            std::make_shared<klass_definition>("Colors", colors_env_ar),
            true
        );

        // End Colors


        // System 

        std::shared_ptr<activation_record> sys_env_ar = std::make_shared<activation_record>();
        sys_env_ar->szAlias = "System";
        sys_env_ar->environment = std::make_shared<scope<std::any>>();

        std::shared_ptr<activation_record> sys_flags_ar = std::make_shared<activation_record>();
        sys_flags_ar->szAlias = "Flags";
        sys_flags_ar->environment = std::make_shared<scope<std::any>>();

#ifndef BUILD_WINDOWS
        sys_flags_ar->environment->define("Windows", false);
#endif

#ifdef BUILD_WINDOWS
        /* Windows */

        sys_flags_ar->environment->define("Windows", true);


        std::shared_ptr<activation_record> winlib_env_ar = std::make_shared<activation_record>();
        winlib_env_ar->szAlias = "lib";
        winlib_env_ar->environment = std::make_shared<scope<std::any>>();

        winlib_env_ar->environment->define("Valid",
            std::make_shared<native_fn>("Valid", win_lib_valid, winlib_env_ar),
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

        winlib_env_ar->environment->define("Get",
            std::make_shared<native_fn>("Get", win_lib_get_function, winlib_env_ar)
            ->registerParameter(BuildParameter<std::string>("idString")),
            true
        );

        sys_env_ar->environment->define("lib",
            std::make_shared<klass_definition>("lib", winlib_env_ar),
            true
        );

        console_env_ar->environment->define("Opacity",
            std::make_shared<native_fn>("Opacity", win_SetConsoleOpacity)
            ->registerParameter(BuildParameter<uint8_t>("alpha")),
            true
        );

        console_env_ar->environment->define("SetOutputColor",
            std::make_shared<native_fn>("SetOutputColor", win_SetOutputColor)
            ->registerParameter(BuildParameter<uint16_t>("color")),
            true
        );

        console_env_ar->environment->define("ResetOutputColor",
            std::make_shared<native_fn>("ResetOutputColor", win_ResetOutputColor),
            true
        );

        console_env_ar->environment->define("SetCursorPosition",
            std::make_shared<native_fn>("SetCursorPosition", win_SetCursorPosition)
            ->registerParameter(BuildParameter<int16_t>("x"))
            ->registerParameter(BuildParameter<int16_t>("y")),
            true
        );

        console_env_ar->environment->define("GetCursorPosition",
            std::make_shared<native_fn>("GetCursorPosition", win_GetCursorPosition),
            true
        );

        console_env_ar->environment->define("SetCursorVisibility",
            std::make_shared<native_fn>("SetCursorVisibility", win_SetCursorVisibility)
            ->registerParameter(BuildParameter<bool>("show")),
            true
        );

        console_env_ar->environment->define("GetWindowSize",
            std::make_shared<native_fn>("GetWindowSize", win_GetWindowSize),
            true
        );

        console_env_ar->environment->define("GetWindowSize",
            std::make_shared<native_fn>("GetWindowSize", win_GetWindowSize)
            ->registerParameter(BuildParameter<std::string>("title")),
            true
        );

        console_env_ar->environment->define("SetWindowSize",
            std::make_shared<native_fn>("SetWindowSize", win_SetWindowSize)
            ->registerParameter(BuildParameter<int32_t>("width"))
            ->registerParameter(BuildParameter<int32_t>("height")),
            true
        );

        /* End Windows */
#endif

        sys_env_ar->environment->define("Flags",
            std::make_shared<klass_definition>("Flags", sys_flags_ar),
            true
        );

        std::shared_ptr<activation_record> clargs_env_ar = std::make_shared<activation_record>();
        clargs_env_ar->szAlias = "clArgs";
        clargs_env_ar->environment = std::make_shared<scope<std::any>>();

        clargs_env_ar->environment->define("constructor",
            std::make_shared<native_fn>("constructor", clArgs_constructor, clargs_env_ar)
            ->registerParameter(BuildParameter<std::shared_ptr<_clArgs>>("raw"))
        );

        clargs_env_ar->environment->define("TryGetBooleanOption",
            std::make_shared<native_fn>("TryGetBooleanOption", clArgs_getbooleanoption, clargs_env_ar)
            ->registerParameter(BuildParameter<std::string>("szVerbose"))
            ->registerParameter(BuildParameter<std::string>("szAbbr"))
            ->registerParameter(BuildParameter<int32_t>("nPos"))
            ->registerParameter(BuildParameter<bool>("defaultValue"))
        );

        clargs_env_ar->environment->define("TryGetStringOption",
            std::make_shared<native_fn>("TryGetStringOption", clArgs_getstringoption, clargs_env_ar)
            ->registerParameter(BuildParameter<std::string>("szVerbose"))
            ->registerParameter(BuildParameter<std::string>("szAbbr"))
            ->registerParameter(BuildParameter<int32_t>("nPos"))
            ->registerParameter(BuildParameter<std::string>("defaultValue"))
        );

        clargs_env_ar->environment->define("TryGetInt32Option",
            std::make_shared<native_fn>("TryGetInt32Option", clArgs_getint32option, clargs_env_ar)
            ->registerParameter(BuildParameter<std::string>("szVerbose"))
            ->registerParameter(BuildParameter<std::string>("szAbbr"))
            ->registerParameter(BuildParameter<int32_t>("nPos"))
            ->registerParameter(BuildParameter<int32_t>("defaultValue"))
        );

        clargs_env_ar->environment->define("TryGetUInt32Option",
            std::make_shared<native_fn>("TryGetUInt32Option", clArgs_getuint32option, clargs_env_ar)
            ->registerParameter(BuildParameter<std::string>("szVerbose"))
            ->registerParameter(BuildParameter<std::string>("szAbbr"))
            ->registerParameter(BuildParameter<int32_t>("nPos"))
            ->registerParameter(BuildParameter<uint32_t>("defaultValue"))
        );

        clargs_env_ar->environment->define("TryGetDoubleOption",
            std::make_shared<native_fn>("TryGetDoubleOption", clArgs_getdoubleoption, clargs_env_ar)
            ->registerParameter(BuildParameter<std::string>("szVerbose"))
            ->registerParameter(BuildParameter<std::string>("szAbbr"))
            ->registerParameter(BuildParameter<int32_t>("nPos"))
            ->registerParameter(BuildParameter<double>("defaultValue"))
        );

        clargs_env_ar->environment->define("Size",
            std::make_shared<native_fn>("Size", clArgs_size, clargs_env_ar)
        );

        sys_env_ar->environment->define("clArgs",
            std::make_shared<klass_definition>("clArgs", clargs_env_ar)
        );

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
			std::make_shared<native_fn>("push", list_push, list_env_ar)
            ->registerParameter(BuildParameter("", "object"))
        );

        list_env_ar->environment->define("remove",
            std::make_shared<native_fn>("remove", list_remove, list_env_ar)
            ->registerParameter(BuildParameter<int32_t>("index"))
        );

		list_env_ar->environment->define("constructor",
			std::make_shared<native_fn>("constructor", list_constructor, list_env_ar)
            ->setVariadic()
        );

		list_env_ar->environment->define("size",
            std::make_shared<native_fn>("size", list_size, list_env_ar)
        );

        list_env_ar->environment->define("join",
            std::make_shared<native_fn>("join", list_join, list_env_ar)
            ->registerParameter(BuildParameter<std::string>("delim"))
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
        fs_env_ar->environment->define("RelativePath",
            std::make_shared<native_fn>("RelativePath", fs_relative_path, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>("path"))
        );
        fs_env_ar->environment->define("Copy",
            std::make_shared<native_fn>("Copy", fs_copy_file, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>("from"))
            ->registerParameter(BuildParameter<std::string>("to"))
        ); 
        fs_env_ar->environment->define("RemoveAll",
            std::make_shared<native_fn>("RemoveAll", fs_remove_all, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>("path"))
        );
        fs_env_ar->environment->define("Read",
            std::make_shared<native_fn>("Read", fs_read_file, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>("filepath"))
        );
        fs_env_ar->environment->define("ReadLine",
            std::make_shared<native_fn>("ReadLine", fs_read_line_from_file, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>("filepath"))
            ->registerParameter(BuildParameter<uint64_t>("lineIndex"))
                
        );
        fs_env_ar->environment->define("ReadToString",
            std::make_shared<native_fn>("ReadToString", fs_real_file_to_string, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>("filepath"))
        );
        fs_env_ar->environment->define("Write",
            std::make_shared<native_fn>("Write", fs_write_to_file, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>("filepath"))
            ->registerParameter(BuildParameter<klass_instance>("data", "list"))
            ->registerParameter(BuildParameter<bool>("overwrite"))
        );
        fs_env_ar->environment->define("WriteLine",
            std::make_shared<native_fn>("WriteLine", fs_write_line_to_file, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>("filepath"))
            ->registerParameter(BuildParameter<std::string>("data"))
            ->registerParameter(BuildParameter<bool>("overwrite"))
        );
        fs_env_ar->environment->define("CountLines",
            std::make_shared<native_fn>("CountLines", fs_count_lines, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>("filepath"))
        );
        fs_env_ar->environment->define("CurrentPath",
            std::make_shared<native_fn>("CurrentPath", fs_current_path, fs_env_ar)
        );
        fs_env_ar->environment->define("ParentPath",
            std::make_shared<native_fn>("ParentPath", fs_parent_path, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>("path"))
        );

        fs_env_ar->environment->define("AbsolutePath",
            std::make_shared<native_fn>("AbsolutePath", fs_absolute_path, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>("path"))
        );
        fs_env_ar->environment->define("Rename",
            std::make_shared<native_fn>("Rename", fs_rename_file, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>("from"))
            ->registerParameter(BuildParameter<std::string>("to"))
        );
        fs_env_ar->environment->define("FileSize",
            std::make_shared<native_fn>("FileSize", fs_file_size, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>("filepath"))
        );
        fs_env_ar->environment->define("Exists",
            std::make_shared<native_fn>("Exists", fs_exists, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>("path"))
        );
        fs_env_ar->environment->define("ReplaceLine",
            std::make_shared<native_fn>("ReplaceLine", fs_replace_line, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>("path"))
            ->registerParameter(BuildParameter<std::string>("data"))
            ->registerParameter(BuildParameter<uint64_t>("lineIndex")),
            true
        );
        fs_env_ar->environment->define("CreateUnique",
            std::make_shared<native_fn>("CreateUnique", fs_get_unique_name, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>("baseDir"))
            ->registerParameter(BuildParameter<uint32_t>("attempts")),
            true
        );
        fs_env_ar->environment->define("CreateDir",
            std::make_shared<native_fn>("CreateDir", fs_create_dir, fs_env_ar)
            ->registerParameter(BuildParameter<std::string>("path")),
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
		db_env_ar->szAlias = "Database";
		db_env_ar->environment = std::make_shared<scope<std::any>>();
        db_env_ar->environment->define("Open",
            std::make_shared<native_fn>("Open", db_open, db_env_ar)
            ->registerParameter(BuildParameter<std::string>("filepath")),
            true
        );

		db_env_ar->environment->define("RunPreparedQuery",
			std::make_shared<native_fn>("RunPreparedQuery", db_run_prepared_query, db_env_ar)
			->registerParameter(BuildParameter<std::string>("query"))
			->registerParameter(BuildParameter<std::shared_ptr<klass_definition>>("template"))
			->setVariadic()
			->setVariadicAfter(2), 
			true
		);


		std::shared_ptr<activation_record> db_env_dbtypes_ar = std::make_shared<activation_record>();
		db_env_dbtypes_ar->szAlias = "Types";
		db_env_dbtypes_ar->environment = std::make_shared<scope<std::any>>();

		db_env_dbtypes_ar->environment->define("INTEGER", std::string("INTEGER"), true);
		db_env_dbtypes_ar->environment->define("REAL", std::string("REAL"), true);
		db_env_dbtypes_ar->environment->define("TEXT", std::string("TEXT"), true);

		db_env_ar->environment->define("Types",
			std::make_shared<klass_definition>("Types", db_env_dbtypes_ar), true);

		db_env_ar->environment->define("__raw__",
			std::make_shared<db_helper>(),
			true);


		e->define("Database", 
			std::make_shared<klass_definition>("Database", db_env_ar),
			true);


        // Time

        std::shared_ptr<activation_record> time_ar = std::make_shared<activation_record>();
        time_ar->szAlias = "Time";
        time_ar->environment = std::make_shared<scope<std::any>>();

        time_ar->environment->define("Now",
            std::make_shared<native_fn>("Now", time_timestamp, time_ar),
            true
        );

        time_ar->environment->define("ToString",
            std::make_shared<native_fn>("ToString", time_timestamp_to_timestring, time_ar)
            ->registerParameter(BuildParameter<int64_t>("timestamp")),
            true
        );

        time_ar->environment->define("ToFormattedString",
            std::make_shared<native_fn>("ToFormattedString", time_timestamp_to_timestring_f, time_ar)
            ->registerParameter(BuildParameter<int64_t>("timestamp"))
            ->registerParameter(BuildParameter<std::string>("format")),
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

        std::shared_ptr<activation_record> language_flags_ar = std::make_shared<activation_record>();
        language_flags_ar->szAlias = "Flags";
        language_flags_ar->environment = std::make_shared<scope<std::any>>();

        language_flags_ar->environment->define("Lightweight", false, true);

        language_flags_ar->environment->define("Windows", 
#ifdef BUILD_WINDOWS
            true,
#else
            false, 
#endif            
            true);

        language_ar->environment->define("Flags",
            std::make_shared<klass_definition>("Flags", language_flags_ar),
            true
        );

        std::shared_ptr<activation_record> language_debug_ar = std::make_shared<activation_record>();
        language_debug_ar->szAlias = "Debug";
        language_debug_ar->environment = std::make_shared<scope<std::any>>();

        language_debug_ar->environment->define("e",
            std::make_shared<native_fn>("e", print_environment, language_ar),
            true
        );

        language_debug_ar->environment->define("o",
            std::make_shared<native_fn>("o", print_operators, language_ar),
            true
        );

        language_debug_ar->environment->define("FlushImports",
            std::make_shared<native_fn>("FlushImports", flush_imports, language_ar),
            true
        );

        language_debug_ar->environment->define("FlushImport",
            std::make_shared<native_fn>("FlushImport", flush_import, language_ar)
            ->registerParameter(BuildParameter<std::string>("filepath")),
            true
        );

        language_debug_ar->environment->define("Exists",
            std::make_shared<native_fn>("Exists", language_object_exists, language_ar)
            ->registerParameter(BuildParameter("", "object")),
            true
        )
            ;
        language_ar->environment->define("Debug",
            std::make_shared<klass_definition>("Debug", language_debug_ar),
            true
        );

        language_ar->environment->define("Version",
            INTERPRETER_VERSION + "." + PARSER_VERSION + "." + TOKENIZER_VERSION + "." + STD_LIB_VERSION,
            true
        );

        language_ar->environment->define("Entry",
            std::string("__main__"),
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
            ->registerParameter(BuildParameter<std::string>("host"))
            ->registerParameter(BuildParameter<uint16_t>("port"))
            ->registerParameter(BuildParameter("", "onMessageRecieved"))
            ->registerParameter(BuildParameter<bool>("continueOnError"))
            ->registerParameter(BuildParameter<bool>("suppressOutput"))
        );

        netclient_env_ar->environment->define("Send",
            std::make_shared<native_fn>("Send", net_client_send, netclient_env_ar)
            ->registerParameter(BuildParameter("", "object"))
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

        netclient_env_ar->environment->define("Stop",
            std::make_shared<native_fn>("Stop", net_client_stop, netclient_env_ar),
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
            ->registerParameter(BuildParameter<uint16_t>("port"))
            ->registerParameter(BuildParameter("", "onClientConnect"))
            ->registerParameter(BuildParameter("", "onClientValidated"))
            ->registerParameter(BuildParameter("", "onClientDisconnect"))
            ->registerParameter(BuildParameter("", "onMessageRecieved"))
            ->registerParameter(BuildParameter<bool>("continueOnError"))
            ->registerParameter(BuildParameter<bool>("suppressOutput"))
        );

        netserver_env_ar->environment->define("MessageClient",
            std::make_shared<native_fn>("MessageClient", net_server_messageclient, netserver_env_ar)
            ->registerParameter(BuildParameter<uint32_t>("client"))
            ->registerParameter(BuildParameter("", "object"))
        );

        netserver_env_ar->environment->define("MessageAll",
            std::make_shared<native_fn>("MessageAll", net_server_messageall, netserver_env_ar)
            ->registerParameter(BuildParameter("", "object"))
            ->registerParameter(BuildParameter<uint32_t>("except"))
        );

        netserver_env_ar->environment->define("GetClientById",
            std::make_shared<native_fn>("GetConnectionById", net_server_getconnectionbyid, netserver_env_ar)
            ->registerParameter(BuildParameter<uint32_t>("id"))
        );
        netserver_env_ar->environment->define("Start",
            std::make_shared<native_fn>("Start", net_server_start, netserver_env_ar)
        );
        netserver_env_ar->environment->define("Stop",
            std::make_shared<native_fn>("Stop", net_server_stop, netserver_env_ar)
        );
        netserver_env_ar->environment->define("Update",
            std::make_shared<native_fn>("Update", net_server_update, netserver_env_ar)
            ->registerParameter(BuildParameter<uint32_t>("maxMessages"))
            ->registerParameter(BuildParameter<bool>("waitForMessage"))
        );

        netserver_env_ar->environment->define("GetLastError",
            std::make_shared<native_fn>("GetLastError", net_server_getlasterror, netserver_env_ar)
        );

        netserver_env_ar->environment->define("Port",
            std::make_shared<native_fn>("Port", net_server_port, netserver_env_ar)
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

    static std::shared_ptr<scope<std::any>> BuildLightweightScope()
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
            ->setVariadic(),
            true
        );

        e->define("typeof",
            std::make_shared<unary_fn>("typeof", type_of_any)
            ->registerParameter(BuildParameter("")),
            true
        );

        // Language

        std::shared_ptr<activation_record> language_ar = std::make_shared<activation_record>();
        language_ar->szAlias = "Language";
        language_ar->environment = std::make_shared<scope<std::any>>();

        std::shared_ptr<activation_record> language_flags_ar = std::make_shared<activation_record>();
        language_flags_ar->szAlias = "Flags";
        language_flags_ar->environment = std::make_shared<scope<std::any>>();

        language_flags_ar->environment->define("Lightweight", false, true);

        language_flags_ar->environment->define("Windows",
#ifdef BUILD_WINDOWS
            true,
#else
            false,
#endif            
            true);

        language_ar->environment->define("Flags",
            std::make_shared<klass_definition>("Flags", language_flags_ar),
            true
        );

        language_ar->environment->define("Version",
            INTERPRETER_VERSION + "." + PARSER_VERSION + "." + TOKENIZER_VERSION + "." + STD_LIB_VERSION,
            true
        );

        language_ar->environment->define("Entry",
            std::string("__main__"),
            true
        );

        e->define("Language",
            std::make_shared<klass_definition>("Language", language_ar),
            true
        );

        // System

        std::shared_ptr<activation_record> sys_env_ar = std::make_shared<activation_record>();
        sys_env_ar->szAlias = "System";
        sys_env_ar->environment = std::make_shared<scope<std::any>>();

        std::shared_ptr<activation_record> clargs_env_ar = std::make_shared<activation_record>();
        clargs_env_ar->szAlias = "clArgs";
        clargs_env_ar->environment = std::make_shared<scope<std::any>>();

        clargs_env_ar->environment->define("constructor",
            std::make_shared<native_fn>("constructor", clArgs_constructor, clargs_env_ar)
            ->registerParameter(BuildParameter<std::shared_ptr<_clArgs>>("raw"))
        );

        clargs_env_ar->environment->define("TryGetBooleanOption",
            std::make_shared<native_fn>("TryGetBooleanOption", clArgs_getbooleanoption, clargs_env_ar)
            ->registerParameter(BuildParameter<std::string>("szVerbose"))
            ->registerParameter(BuildParameter<std::string>("szAbbr"))
            ->registerParameter(BuildParameter<int32_t>("nPos"))
            ->registerParameter(BuildParameter<bool>("defaultValue"))
        );

        clargs_env_ar->environment->define("TryGetStringOption",
            std::make_shared<native_fn>("TryGetStringOption", clArgs_getstringoption, clargs_env_ar)
            ->registerParameter(BuildParameter<std::string>("szVerbose"))
            ->registerParameter(BuildParameter<std::string>("szAbbr"))
            ->registerParameter(BuildParameter<int32_t>("nPos"))
            ->registerParameter(BuildParameter<std::string>("defaultValue"))
        );

        clargs_env_ar->environment->define("TryGetInt32Option",
            std::make_shared<native_fn>("TryGetInt32Option", clArgs_getint32option, clargs_env_ar)
            ->registerParameter(BuildParameter<std::string>("szVerbose"))
            ->registerParameter(BuildParameter<std::string>("szAbbr"))
            ->registerParameter(BuildParameter<int32_t>("nPos"))
            ->registerParameter(BuildParameter<int32_t>("defaultValue"))
        );

        clargs_env_ar->environment->define("TryGetUInt32Option",
            std::make_shared<native_fn>("TryGetUInt32Option", clArgs_getuint32option, clargs_env_ar)
            ->registerParameter(BuildParameter<std::string>("szVerbose"))
            ->registerParameter(BuildParameter<std::string>("szAbbr"))
            ->registerParameter(BuildParameter<int32_t>("nPos"))
            ->registerParameter(BuildParameter<uint32_t>("defaultValue"))
        );

        clargs_env_ar->environment->define("TryGetDoubleOption",
            std::make_shared<native_fn>("TryGetDoubleOption", clArgs_getdoubleoption, clargs_env_ar)
            ->registerParameter(BuildParameter<std::string>("szVerbose"))
            ->registerParameter(BuildParameter<std::string>("szAbbr"))
            ->registerParameter(BuildParameter<int32_t>("nPos"))
            ->registerParameter(BuildParameter<double>("defaultValue"))
        );

        clargs_env_ar->environment->define("Size",
            std::make_shared<native_fn>("Size", clArgs_size, clargs_env_ar)
        );

        sys_env_ar->environment->define("clArgs",
            std::make_shared<klass_definition>("clArgs", clargs_env_ar)
        );

        e->define("System",
            std::make_shared<klass_definition>("System", sys_env_ar),
            true);

        return e;
    }

	static std::shared_ptr<interpreter> BuildInterpreter(bool bLightweight)
	{
        auto context = BuildExecutionContext(bLightweight);
        auto i = std::make_shared<interpreter>(context, BuildTokenizer(), BuildParser());

        auto systemNamespace = context->get<std::shared_ptr<klass_definition>>("System");

        auto clArgsDefinition = context->get_coalesce<std::shared_ptr<klass_definition>>("System.clArgs");
        auto clArgsInstance = clArgsDefinition->create();

        std::vector<std::any> args = { std::make_shared<_clArgs>() };
        Utilities().getCallable(clArgsInstance.Get("constructor", location()))->call(i, _args(args));

        systemNamespace->Define("clArgs", clArgsInstance, location(), true);

        return i;
	}

    static std::shared_ptr<interpreter> BuildInterpreter(const std::string& szExecutionDir, std::shared_ptr<_clArgs> clArgs, bool bLightweight)
    {
        auto context = BuildExecutionContext(bLightweight);
        auto i = std::make_shared<interpreter>(context, BuildTokenizer(), BuildParser());
  
        auto systemNamespace = context->get<std::shared_ptr<klass_definition>>("System");
        auto fsNamespace = context->get<std::shared_ptr<klass_definition>>("FileSystem");

        fsNamespace->Define("WorkingDirectory", szExecutionDir, location(), true);
        auto clArgsDefinition = context->get_coalesce<std::shared_ptr<klass_definition>>("System.clArgs");
        auto clArgsInstance = clArgsDefinition->create();
        
       
        std::vector<std::any> args = { clArgs };
        Utilities().getCallable(clArgsInstance.Get("constructor", location()))->call(i, _args(args));

        systemNamespace->Define("clArgs", clArgsInstance, location(), true);
        
        return i;
    }

	static std::shared_ptr<execution_context> BuildExecutionContext(bool bLightweight) 
	{
		std::shared_ptr<activation_record> default_ar = std::make_shared<activation_record>();
		default_ar->id = 0;
		default_ar->environment = bLightweight ? BuildLightweightScope() : BuildDefaultScope();
		return std::make_shared<execution_context>(default_ar, BuildOperatorHandler());
	}


    static std::shared_ptr<parser> BuildParser()
    {
        return std::make_shared<parser>();
    }


	static std::shared_ptr<operator_handler> BuildOperatorHandler()
	{
		std::shared_ptr<operator_handler> opHandler = std::make_shared<operator_handler>();
		
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

        /* Not bool */

        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_bool)
            ->registerParameter(BuildParameter<bool>())
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
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_int8_t)
            ->registerParameter(BuildParameter<int8_t>())
        );
        /*

        negate

        */
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
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_int16_t)
            ->registerParameter(BuildParameter<int16_t>())
        );
        /*

        negate

        */
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
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_int32_t)
            ->registerParameter(BuildParameter<int32_t>())
        );
        /*

        negate

        */
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
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_int64_t)
            ->registerParameter(BuildParameter<int64_t>())
        );
        /*

        negate

        */
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
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_float)
            ->registerParameter(BuildParameter<float>())
        );
        /*

        negate

        */
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
        opHandler->registerOperator(
            std::make_shared<unary_fn>("!", not_double)
            ->registerParameter(BuildParameter<double>())
        );
        /*

        negate

        */
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
            ->registerParameter(BuildParameter<int8_t>())
            ->returns<int8_t>(),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_int16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->returns<int16_t>(),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_int32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->returns<int32_t>(),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(int32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_int64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->returns<int64_t>(),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_uint8_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->returns<uint8_t>(),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_uint16_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->returns<uint16_t>(),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_uint32_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->returns<uint32_t>(),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_uint64_t)
            ->registerParameter(BuildParameter<int8_t>())
            ->returns<uint64_t>(),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_float)
            ->registerParameter(BuildParameter<int8_t>())
            ->returns<float>(),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_double)
            ->registerParameter(BuildParameter<int8_t>())
            ->returns<double>(),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_string)
            ->registerParameter(BuildParameter<int8_t>())
            ->returns<std::string>(),
            "::(" + std::string(typeid(int8_t).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int8_t_bool)
            ->registerParameter(BuildParameter<int8_t>())
            ->returns<bool>(),
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
            ->registerParameter(BuildParameter<int16_t>())
            ->returns<int8_t>(),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_int16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->returns<int16_t>(),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_int32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->returns<int32_t>(),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(int32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_int64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->returns<int64_t>(),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_uint8_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->returns<uint8_t>(),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_uint16_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->returns<uint16_t>(),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_uint32_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->returns<uint32_t>(),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_uint64_t)
            ->registerParameter(BuildParameter<int16_t>())
            ->returns<uint64_t>(),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_float)
            ->registerParameter(BuildParameter<int16_t>())
            ->returns<float>(),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_double)
            ->registerParameter(BuildParameter<int16_t>())
            ->returns<double>(),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_string)
            ->registerParameter(BuildParameter<int16_t>())
            ->returns<std::string>(),
            "::(" + std::string(typeid(int16_t).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int16_t_bool)
            ->registerParameter(BuildParameter<int16_t>())
            ->returns<bool>(),
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
            ->registerParameter(BuildParameter<int32_t>())
            ->returns<int8_t>(),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_int16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->returns<int16_t>(),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_int32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->returns<int32_t>(),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(int32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_int64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->returns<int64_t>(),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_uint8_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->returns<uint8_t>(),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_uint16_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->returns<uint16_t>(),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_uint32_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->returns<uint32_t>(),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_uint64_t)
            ->registerParameter(BuildParameter<int32_t>())
            ->returns<uint64_t>(),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_float)
            ->registerParameter(BuildParameter<int32_t>())
            ->returns<float>(),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_double)
            ->registerParameter(BuildParameter<int32_t>())
            ->returns<double>(),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_string)
            ->registerParameter(BuildParameter<int32_t>())
            ->returns<std::string>(),
            "::(" + std::string(typeid(int32_t).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int32_t_bool)
            ->registerParameter(BuildParameter<int32_t>())
            ->returns<bool>(),
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
            ->registerParameter(BuildParameter<int64_t>())
            ->returns<int8_t>(),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_int16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->returns<int16_t>(),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_int32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->returns<int32_t>(),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(int32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_int64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->returns<int64_t>(),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_uint8_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->returns<uint8_t>(),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_uint16_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->returns<uint16_t>(),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_uint32_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->returns<uint32_t>(),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_uint64_t)
            ->registerParameter(BuildParameter<int64_t>())
            ->returns<uint64_t>(),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_float)
            ->registerParameter(BuildParameter<int64_t>())
            ->returns<float>(),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_double)
            ->registerParameter(BuildParameter<int64_t>())
            ->returns<double>(),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_string)
            ->registerParameter(BuildParameter<int64_t>())
            ->returns<std::string>(),
            "::(" + std::string(typeid(int64_t).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_int64_t_bool)
            ->registerParameter(BuildParameter<int64_t>())
            ->returns<bool>(),
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
            ->registerParameter(BuildParameter<uint8_t>())
            ->returns<int8_t>(),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_int16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->returns<int16_t>(),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_int32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->returns<int32_t>(),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(int32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_int64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->returns<int64_t>(),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_uint8_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->returns<uint8_t>(),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_uint16_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->returns<uint16_t>(),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_uint32_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->returns<uint32_t>(),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_uint64_t)
            ->registerParameter(BuildParameter<uint8_t>())
            ->returns<uint64_t>(),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_float)
            ->registerParameter(BuildParameter<uint8_t>())
            ->returns<float>(),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_double)
            ->registerParameter(BuildParameter<uint8_t>())
            ->returns<double>(),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_string)
            ->registerParameter(BuildParameter<uint8_t>())
            ->returns<std::string>(),
            "::(" + std::string(typeid(uint8_t).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint8_t_bool)
            ->registerParameter(BuildParameter<uint8_t>())
            ->returns<bool>(),
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
            ->registerParameter(BuildParameter<uint16_t>())
            ->returns<int8_t>(),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_int16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->returns<int16_t>(),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_int32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->returns<int32_t>(),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(int32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_int64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->returns<int64_t>(),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_uint8_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->returns<uint8_t>(),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_uint16_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->returns<uint16_t>(),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_uint32_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->returns<uint32_t>(),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_uint64_t)
            ->registerParameter(BuildParameter<uint16_t>())
            ->returns<uint64_t>(),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_float)
            ->registerParameter(BuildParameter<uint16_t>())
            ->returns<float>(),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_double)
            ->registerParameter(BuildParameter<uint16_t>())
            ->returns<double>(),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_string)
            ->registerParameter(BuildParameter<uint16_t>())
            ->returns<std::string>(),
            "::(" + std::string(typeid(uint16_t).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint16_t_bool)
            ->registerParameter(BuildParameter<uint16_t>())
            ->returns<bool>(),
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
            ->registerParameter(BuildParameter<uint32_t>())
            ->returns<int8_t>(),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_int16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->returns<int16_t>(),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_int32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->returns<int32_t>(),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(int32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_int64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->returns<int64_t>(),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_uint8_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->returns<uint8_t>(),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_uint16_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->returns<uint16_t>(),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_uint32_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->returns<uint32_t>(),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_uint64_t)
            ->registerParameter(BuildParameter<uint32_t>())
            ->returns<uint64_t>(),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_float)
            ->registerParameter(BuildParameter<uint32_t>())
            ->returns<float>(),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_double)
            ->registerParameter(BuildParameter<uint32_t>())
            ->returns<double>(),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_string)
            ->registerParameter(BuildParameter<uint32_t>())
            ->returns<std::string>(),
            "::(" + std::string(typeid(uint32_t).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint32_t_bool)
            ->registerParameter(BuildParameter<uint32_t>())
            ->returns<bool>(),
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
            ->registerParameter(BuildParameter<uint64_t>())
            ->returns<int8_t>(),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_int16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->returns<int16_t>(),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_int32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->returns<int32_t>(),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(int32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_int64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->returns<int64_t>(),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_uint8_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->returns<uint8_t>(),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_uint16_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->returns<uint16_t>(),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_uint32_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->returns<uint32_t>(),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_uint64_t)
            ->registerParameter(BuildParameter<uint64_t>())
            ->returns<uint64_t>(),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_float)
            ->registerParameter(BuildParameter<uint64_t>())
            ->returns<float>(),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_double)
            ->registerParameter(BuildParameter<uint64_t>())
            ->returns<double>(),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_string)
            ->registerParameter(BuildParameter<uint64_t>())
            ->returns<std::string>(),
            "::(" + std::string(typeid(uint64_t).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_uint64_t_bool)
            ->registerParameter(BuildParameter<uint64_t>())
            ->returns<bool>(),
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
            ->registerParameter(BuildParameter<float>())
            ->returns<int8_t>(),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_int16_t)
            ->registerParameter(BuildParameter<float>())
            ->returns<int16_t>(),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_int32_t)
            ->registerParameter(BuildParameter<float>())
            ->returns<int32_t>(),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(int32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_int64_t)
            ->registerParameter(BuildParameter<float>())
            ->returns<int64_t>(),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_uint8_t)
            ->registerParameter(BuildParameter<float>())
            ->returns<uint8_t>(),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_uint16_t)
            ->registerParameter(BuildParameter<float>())
            ->returns<uint16_t>(),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_uint32_t)
            ->registerParameter(BuildParameter<float>())
            ->returns<uint32_t>(),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_uint64_t)
            ->registerParameter(BuildParameter<float>())
            ->returns<uint64_t>(),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_float)
            ->registerParameter(BuildParameter<float>())
            ->returns<float>(),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_double)
            ->registerParameter(BuildParameter<float>())
            ->returns<double>(),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_string)
            ->registerParameter(BuildParameter<float>())
            ->returns<std::string>(),
            "::(" + std::string(typeid(float).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_float_bool)
            ->registerParameter(BuildParameter<float>())
            ->returns<bool>(),
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
            ->registerParameter(BuildParameter<double>())
            ->returns<int8_t>(),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(int8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_int16_t)
            ->registerParameter(BuildParameter<double>())
            ->returns<int16_t>(),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(int16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_int32_t)
            ->registerParameter(BuildParameter<double>())
            ->returns<int32_t>(),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(int32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_int64_t)
            ->registerParameter(BuildParameter<double>())
            ->returns<int64_t>(),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(int64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_uint8_t)
            ->registerParameter(BuildParameter<double>())
            ->returns<uint8_t>(),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(uint8_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_uint16_t)
            ->registerParameter(BuildParameter<double>())
            ->returns<uint16_t>(),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(uint16_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_uint32_t)
            ->registerParameter(BuildParameter<double>())
            ->returns<uint32_t>(),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(uint32_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_uint64_t)
            ->registerParameter(BuildParameter<double>())
            ->returns<uint64_t>(),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(uint64_t).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_float)
            ->registerParameter(BuildParameter<double>())
            ->returns<float>(),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(float).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_double)
            ->registerParameter(BuildParameter<double>())
            ->returns<double>(),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(double).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_string)
            ->registerParameter(BuildParameter<double>())
            ->returns<std::string>(),
            "::(" + std::string(typeid(double).name()) + "," + std::string(typeid(std::string).name()) + ")"
        );
        opHandler->registerOperator(
            std::make_shared<unary_fn>("::", cast_double_bool)
            ->registerParameter(BuildParameter<double>())
            ->returns<bool>(),
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

			tokenizer_rule(Keywords().ANY_T(), "_ty", std::make_shared<std::string>("")),
            tokenizer_rule(Keywords().NULLPTR_T(), "nullptr_t", std::make_shared<std::string>(typeid(nullptr).name())),
			
			tokenizer_rule(Keywords().NEW(), "new"),
			tokenizer_rule(TOKEN_TYPE_EOL_COMMENT, "//"),
            tokenizer_rule(TOKEN_TYPE_EOL_COMMENT, "#"),
            tokenizer_rule(TOKEN_TYPE_ML_COMMENT_START, "/*"),
            tokenizer_rule(TOKEN_TYPE_ML_COMMENT_ENCLOSING, "*/"),
			tokenizer_rule(TOKEN_TYPE_STRING_ENCLOSING, "\""),
			tokenizer_rule(Keywords().INJECT(), "inject"),
			tokenizer_rule(Keywords().DIRECTIVE(), "@"),
			tokenizer_rule(Keywords().UPCARAT(), "^"),
            tokenizer_rule(Keywords().LCARAT(), "<"),
            tokenizer_rule(Keywords().RCARAT(), ">")
		};
		return std::make_shared<tokenizer>(rules);
	}

private:
	static param BuildParameter(std::string szNativeType, std::string szName = "") {
		param p;
		p.szName = szName;
		p.szNativeType = szNativeType;
		return p;
	}

	template <typename Ty>
	static param BuildParameter(std::string szName = "", std::string szCustomType = "") {
		param p;
		p.szName = szName;
		p.szNativeType = typeid(Ty).name();
		p.szCustomType = szCustomType;
		return p;
	}
};

#endif