#pragma once
#include "BuildDefinitions.hpp"

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

// Misc

std::any win_SetConsoleOpacity(std::shared_ptr<interpreter> i, _args args);
std::any win_SetOutputColor(std::shared_ptr<interpreter> i, _args args);
std::any win_ResetOutputColor(std::shared_ptr<interpreter> i, _args args);
std::any win_SetCursorPosition(std::shared_ptr<interpreter> i, _args args);
std::any win_GetCursorPosition(std::shared_ptr<interpreter> i, _args args);
std::any win_SetCursorVisibility(std::shared_ptr<interpreter> i, _args args);
std::any win_GetWindowSize(std::shared_ptr<interpreter> i, _args args);
std::any win_SetTitle(std::shared_ptr<interpreter> i, _args args);
std::any win_SetWindowSize(std::shared_ptr<interpreter> i, _args args);

// View

std::any win_view_contructor(std::shared_ptr<interpreter> i, _args args);
std::any win_view_contruct(std::shared_ptr<interpreter> i, _args args);
std::any win_view_start(std::shared_ptr<interpreter> i, _args args);
std::any win_view_DrawStringDecal(std::shared_ptr<interpreter> i, _args args);
std::any win_view_FillRect(std::shared_ptr<interpreter> i, _args args);

std::any win_view_vf2d(std::shared_ptr<interpreter> i, _args args);
std::any win_view_vi2d(std::shared_ptr<interpreter> i, _args args);
std::any win_view_pixel(std::shared_ptr<interpreter> i, _args args);

#endif