#pragma once
#include "BuildDefinitions.h"

#ifdef BUILD_WINDOWS

#include <any>
#include <memory>

#include "callable.h"
#include "interpreter.h"



// DB Methods
std::any db_open(std::shared_ptr<interpreter> i, _args args);

// Lib
std::any win_lib_constructor(std::shared_ptr<interpreter> i, _args args);
std::any win_lib_valid(std::shared_ptr<interpreter> i, _args args);
std::any win_lib_get_function(std::shared_ptr<interpreter> i, _args args);

#endif