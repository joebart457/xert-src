#pragma once


#include <any>
#include <memory>
#include "interpreter.h"



// Native supported types are numerics, std::string, --not char yet
// Custom supported types are list, map
// Supported binary operations are +, -, /, *, [], <, <=, >, >=, ==, !=,
// Supported unary operations are !, -


std::any type_of_any(std::shared_ptr<interpreter> i, std::any& rhs);

std::any index_list_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any index_list_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any index_list_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any index_list_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any index_list_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any index_list_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any index_list_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any index_list_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);


std::any index_string_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any index_string_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any index_string_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any index_string_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any index_string_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any index_string_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any index_string_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any index_string_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any index_map_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);


std::any not_string(std::shared_ptr<interpreter> i, std::any& rhs);
std::any not_null(std::shared_ptr<interpreter> i, std::any& rhs);

std::any add_string_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any equalequal_string_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_string_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any cast_string_int8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_string_int16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_string_int32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_string_int64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_string_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_string_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_string_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_string_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_string_float(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_string_double(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_string_string(std::shared_ptr<interpreter> i, std::any& lhs);

std::any not_bool(std::shared_ptr<interpreter> i, std::any& rhs);

std::any cast_bool_int8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_bool_int16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_bool_int32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_bool_int64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_bool_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_bool_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_bool_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_bool_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_bool_float(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_bool_double(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_bool_string(std::shared_ptr<interpreter> i, std::any& lhs);

std::any lessthan_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
