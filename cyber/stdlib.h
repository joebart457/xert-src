#pragma once

#include <any>
#include <memory>

#include "callable.h"
#include "interpreter.h"

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
std::any list_constructor(std::shared_ptr<interpreter> i, _args args);

// Map methods
std::any map_add(std::shared_ptr<interpreter> i, _args args);
std::any map_delete(std::shared_ptr<interpreter> i, _args args);
std::any map_constructor(std::shared_ptr<interpreter> i, _args args);
std::any map_exists(std::shared_ptr<interpreter> i, _args args);


// stdlib
std::any print(std::shared_ptr<interpreter> i, _args args);
std::any to_string(std::shared_ptr<interpreter> i, std::any& rhs);

// String

std::any string_split(std::shared_ptr<interpreter> i, _args args);
std::any string_rtrim(std::shared_ptr<interpreter> i, _args args);
std::any string_ltrim(std::shared_ptr<interpreter> i, _args args);
std::any string_trim(std::shared_ptr<interpreter> i, _args args);
std::any string_find(std::shared_ptr<interpreter> i, _args args);
std::any string_substr(std::shared_ptr<interpreter> i, _args args);
std::any string_pad(std::shared_ptr<interpreter> i, _args args);
std::any string_to_char(std::shared_ptr<interpreter> i, _args args);


// Language
std::any print_environment(std::shared_ptr<interpreter> i, _args args);
std::any flush_imports(std::shared_ptr<interpreter> i, _args args);
std::any flush_import(std::shared_ptr<interpreter> i, _args args);


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
