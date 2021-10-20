#pragma once

#include <any>
#include <memory>

#include "callable.h"
#include "interpreter.h"


// clArgs
std::any clArgs_constructor(std::shared_ptr<interpreter> i, _args args);
std::any clArgs_size(std::shared_ptr<interpreter> i, _args args);
std::any clArgs_getbooleanoption(std::shared_ptr<interpreter> i, _args args);
std::any clArgs_getstringoption(std::shared_ptr<interpreter> i, _args args);
std::any clArgs_getint32option(std::shared_ptr<interpreter> i, _args args);
std::any clArgs_getuint32option(std::shared_ptr<interpreter> i, _args args);
std::any clArgs_getdoubleoption(std::shared_ptr<interpreter> i, _args args);

// Thread
std::any thread_sleep(std::shared_ptr<interpreter> i, _args args);

// Time
std::any time_timestamp(std::shared_ptr<interpreter> i, _args args);
std::any time_timestamp_to_timestring(std::shared_ptr<interpreter> i, _args args);
std::any time_timestamp_to_timestring_f(std::shared_ptr<interpreter> i, _args args);


// DB Methods
std::any db_open(std::shared_ptr<interpreter> i, _args args);
std::any db_get(std::shared_ptr<interpreter> i, _args args);
std::any db_run_prepared_query(std::shared_ptr<interpreter> i, _args args);

// List methods
std::any list_push(std::shared_ptr<interpreter> i, _args args);
std::any list_remove(std::shared_ptr<interpreter> i, _args args);
std::any list_size(std::shared_ptr<interpreter> i, _args args);
std::any list_constructor(std::shared_ptr<interpreter> i, _args args);
std::any list_join(std::shared_ptr<interpreter> i, _args args);

// Map methods
std::any map_add(std::shared_ptr<interpreter> i, _args args);
std::any map_delete(std::shared_ptr<interpreter> i, _args args);
std::any map_constructor(std::shared_ptr<interpreter> i, _args args);
std::any map_exists(std::shared_ptr<interpreter> i, _args args);


// stdlib
std::any print(std::shared_ptr<interpreter> i, _args args);
std::any to_string(std::shared_ptr<interpreter> i, std::any& rhs);

// Null
std::any null_isNullType(std::shared_ptr<interpreter> i, _args args);


// String
std::any string_split(std::shared_ptr<interpreter> i, _args args);
std::any string_rtrim(std::shared_ptr<interpreter> i, _args args);
std::any string_ltrim(std::shared_ptr<interpreter> i, _args args);
std::any string_trim(std::shared_ptr<interpreter> i, _args args);
std::any string_find(std::shared_ptr<interpreter> i, _args args);
std::any string_substr(std::shared_ptr<interpreter> i, _args args);
std::any string_pad(std::shared_ptr<interpreter> i, _args args);
std::any string_to_char(std::shared_ptr<interpreter> i, _args args);
std::any string_length(std::shared_ptr<interpreter> i, _args args);

// Console
std::any console_write(std::shared_ptr<interpreter> i, _args args);
std::any console_writeline(std::shared_ptr<interpreter> i, _args args);
std::any console_readKey(std::shared_ptr<interpreter> i, _args args);
std::any console_readLine(std::shared_ptr<interpreter> i, _args args);


// Language
std::any print_environment(std::shared_ptr<interpreter> i, _args args);
std::any print_operators(std::shared_ptr<interpreter> i, _args args);
std::any flush_imports(std::shared_ptr<interpreter> i, _args args);
std::any flush_import(std::shared_ptr<interpreter> i, _args args);
std::any language_object_exists(std::shared_ptr<interpreter> i, _args args);


// FileSystem
std::any fs_relative_path(std::shared_ptr<interpreter> i, _args args);
std::any fs_copy_file(std::shared_ptr<interpreter> i, _args args);
std::any fs_remove_all(std::shared_ptr<interpreter> i, _args args);
std::any fs_read_file(std::shared_ptr<interpreter> i, _args args);
std::any fs_real_file_to_string(std::shared_ptr<interpreter> i, _args args);
std::any fs_read_line_from_file(std::shared_ptr<interpreter> i, _args args);
std::any fs_write_to_file(std::shared_ptr<interpreter> i, _args args);
std::any fs_write_line_to_file(std::shared_ptr<interpreter> i, _args args); 
std::any fs_count_lines(std::shared_ptr<interpreter> i, _args args);
std::any fs_current_path(std::shared_ptr<interpreter> i, _args args);
std::any fs_parent_path(std::shared_ptr<interpreter> i, _args args);
std::any fs_absolute_path(std::shared_ptr<interpreter> i, _args args);
std::any fs_rename_file(std::shared_ptr<interpreter> i, _args args);
std::any fs_file_size(std::shared_ptr<interpreter> i, _args args);
std::any fs_exists(std::shared_ptr<interpreter> i, _args args);
std::any fs_replace_line(std::shared_ptr<interpreter> i, _args args);
std::any fs_get_unique_name(std::shared_ptr<interpreter> i, _args args);
std::any fs_create_dir(std::shared_ptr<interpreter> i, _args args);

// Network

std::any net_create_client(std::shared_ptr<interpreter> i, _args args);
std::any net_client_send(std::shared_ptr<interpreter> i, _args args);
std::any net_client_isconnected(std::shared_ptr<interpreter> i, _args args);
std::any net_client_connect(std::shared_ptr<interpreter> i, _args args);
std::any net_client_disconnect(std::shared_ptr<interpreter> i, _args args);
std::any net_client_start(std::shared_ptr<interpreter> i, _args args);
std::any net_client_stop(std::shared_ptr<interpreter> i, _args args);
std::any net_client_start_async(std::shared_ptr<interpreter> i, _args args);
std::any net_client_port(std::shared_ptr<interpreter> i, _args args);
std::any net_client_host(std::shared_ptr<interpreter> i, _args args);
std::any net_client_getlasterror(std::shared_ptr<interpreter> i, _args args);

std::any net_create_server(std::shared_ptr<interpreter> i, _args args);
std::any net_server_messageclient(std::shared_ptr<interpreter> i, _args args);
std::any net_server_messageall(std::shared_ptr<interpreter> i, _args args);
std::any net_server_getconnectionbyid(std::shared_ptr<interpreter> i, _args args);
std::any net_server_start(std::shared_ptr<interpreter> i, _args args);
std::any net_server_stop(std::shared_ptr<interpreter> i, _args args);
std::any net_server_update(std::shared_ptr<interpreter> i, _args args);
std::any net_server_getlasterror(std::shared_ptr<interpreter> i, _args args);
std::any net_server_port(std::shared_ptr<interpreter> i, _args args);


