#pragma once


/* Auto-generated */
#include <any>
#include <memory>
#include <cstdint>
class interpreter;


/*

int8_t

*/
/*

not

*/
std::any not_int8_t(std::shared_ptr<interpreter> i, std::any& rhs);
/*

negate

*/
std::any negate_int8_t(std::shared_ptr<interpreter> i, std::any& rhs);
/*

int16_t

*/
/*

not

*/
std::any not_int16_t(std::shared_ptr<interpreter> i, std::any& rhs);
/*

negate

*/
std::any negate_int16_t(std::shared_ptr<interpreter> i, std::any& rhs);
/*

int32_t

*/
/*

not

*/
std::any not_int32_t(std::shared_ptr<interpreter> i, std::any& rhs);
/*

negate

*/
std::any negate_int32_t(std::shared_ptr<interpreter> i, std::any& rhs);
/*

int64_t

*/
/*

not

*/
std::any not_int64_t(std::shared_ptr<interpreter> i, std::any& rhs);
/*

negate

*/
std::any negate_int64_t(std::shared_ptr<interpreter> i, std::any& rhs);
/*

uint8_t

*/
/*

not

*/
std::any not_uint8_t(std::shared_ptr<interpreter> i, std::any& rhs);
/*

uint16_t

*/
/*

not

*/
std::any not_uint16_t(std::shared_ptr<interpreter> i, std::any& rhs);
/*

uint32_t

*/
/*

not

*/
std::any not_uint32_t(std::shared_ptr<interpreter> i, std::any& rhs);
/*

uint64_t

*/
/*

not

*/
std::any not_uint64_t(std::shared_ptr<interpreter> i, std::any& rhs);
/*

float

*/
/*

not

*/
std::any not_float(std::shared_ptr<interpreter> i, std::any& rhs);
/*

negate

*/
std::any negate_float(std::shared_ptr<interpreter> i, std::any& rhs);
/*

double

*/
/*

not

*/
std::any not_double(std::shared_ptr<interpreter> i, std::any& rhs);
/*

negate

*/
std::any negate_double(std::shared_ptr<interpreter> i, std::any& rhs);



/* Binary Operators*/


/*

int8_t

*/
/*

add

*/
std::any add_int8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int8_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int8_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

subtract

*/
std::any subtract_int8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int8_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int8_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

multiply

*/
std::any multiply_int8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int8_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int8_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

divide

*/
std::any divide_int8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int8_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int8_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

lessthan

*/
std::any lessthan_int8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int8_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int8_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

lessthanequal

*/
std::any lessthanequal_int8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int8_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int8_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

greaterthan

*/
std::any greaterthan_int8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int8_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int8_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

greaterthanequal

*/
std::any greaterthanequal_int8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int8_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int8_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

equalequal

*/
std::any equalequal_int8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int8_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int8_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

notequal

*/
std::any notequal_int8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int8_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int8_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

cast

*/
std::any cast_int8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int8_t_float(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int8_t_double(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int8_t_string(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int8_t_bool(std::shared_ptr<interpreter> i, std::any& lhs);
/*

int16_t

*/
/*

add

*/
std::any add_int16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int16_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int16_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

subtract

*/
std::any subtract_int16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int16_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int16_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

multiply

*/
std::any multiply_int16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int16_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int16_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

divide

*/
std::any divide_int16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int16_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int16_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

lessthan

*/
std::any lessthan_int16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int16_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int16_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

lessthanequal

*/
std::any lessthanequal_int16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int16_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int16_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

greaterthan

*/
std::any greaterthan_int16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int16_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int16_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

greaterthanequal

*/
std::any greaterthanequal_int16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int16_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int16_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

equalequal

*/
std::any equalequal_int16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int16_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int16_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

notequal

*/
std::any notequal_int16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int16_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int16_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

cast

*/
std::any cast_int16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int16_t_float(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int16_t_double(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int16_t_string(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int16_t_bool(std::shared_ptr<interpreter> i, std::any& lhs);
/*

int32_t

*/
/*

add

*/
std::any add_int32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int32_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int32_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

subtract

*/
std::any subtract_int32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int32_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int32_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

multiply

*/
std::any multiply_int32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int32_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int32_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

divide

*/
std::any divide_int32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int32_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int32_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

lessthan

*/
std::any lessthan_int32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int32_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int32_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

lessthanequal

*/
std::any lessthanequal_int32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int32_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int32_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

greaterthan

*/
std::any greaterthan_int32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int32_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int32_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

greaterthanequal

*/
std::any greaterthanequal_int32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int32_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int32_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

equalequal

*/
std::any equalequal_int32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int32_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int32_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

notequal

*/
std::any notequal_int32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int32_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int32_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

cast

*/
std::any cast_int32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int32_t_float(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int32_t_double(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int32_t_string(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int32_t_bool(std::shared_ptr<interpreter> i, std::any& lhs);
/*

int64_t

*/
/*

add

*/
std::any add_int64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int64_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int64_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

subtract

*/
std::any subtract_int64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int64_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int64_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

multiply

*/
std::any multiply_int64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int64_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int64_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

divide

*/
std::any divide_int64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int64_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int64_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

lessthan

*/
std::any lessthan_int64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int64_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int64_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

lessthanequal

*/
std::any lessthanequal_int64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int64_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int64_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

greaterthan

*/
std::any greaterthan_int64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int64_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int64_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

greaterthanequal

*/
std::any greaterthanequal_int64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int64_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int64_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

equalequal

*/
std::any equalequal_int64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int64_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int64_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

notequal

*/
std::any notequal_int64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int64_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int64_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

cast

*/
std::any cast_int64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int64_t_float(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int64_t_double(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int64_t_string(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_int64_t_bool(std::shared_ptr<interpreter> i, std::any& lhs);
/*

uint8_t

*/
/*

add

*/
std::any add_uint8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint8_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint8_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

subtract

*/
std::any subtract_uint8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint8_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint8_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

multiply

*/
std::any multiply_uint8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint8_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint8_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

divide

*/
std::any divide_uint8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint8_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint8_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

lessthan

*/
std::any lessthan_uint8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint8_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint8_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

lessthanequal

*/
std::any lessthanequal_uint8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint8_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint8_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

greaterthan

*/
std::any greaterthan_uint8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint8_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint8_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

greaterthanequal

*/
std::any greaterthanequal_uint8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint8_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint8_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

equalequal

*/
std::any equalequal_uint8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint8_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint8_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

notequal

*/
std::any notequal_uint8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint8_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint8_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

cast

*/
std::any cast_uint8_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint8_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint8_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint8_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint8_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint8_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint8_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint8_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint8_t_float(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint8_t_double(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint8_t_string(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint8_t_bool(std::shared_ptr<interpreter> i, std::any& lhs);
/*

uint16_t

*/
/*

add

*/
std::any add_uint16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint16_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint16_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

subtract

*/
std::any subtract_uint16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint16_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint16_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

multiply

*/
std::any multiply_uint16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint16_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint16_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

divide

*/
std::any divide_uint16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint16_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint16_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

lessthan

*/
std::any lessthan_uint16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint16_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint16_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

lessthanequal

*/
std::any lessthanequal_uint16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint16_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint16_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

greaterthan

*/
std::any greaterthan_uint16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint16_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint16_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

greaterthanequal

*/
std::any greaterthanequal_uint16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint16_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint16_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

equalequal

*/
std::any equalequal_uint16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint16_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint16_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

notequal

*/
std::any notequal_uint16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint16_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint16_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

cast

*/
std::any cast_uint16_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint16_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint16_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint16_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint16_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint16_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint16_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint16_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint16_t_float(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint16_t_double(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint16_t_string(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint16_t_bool(std::shared_ptr<interpreter> i, std::any& lhs);
/*

uint32_t

*/
/*

add

*/
std::any add_uint32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint32_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint32_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

subtract

*/
std::any subtract_uint32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint32_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint32_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

multiply

*/
std::any multiply_uint32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint32_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint32_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

divide

*/
std::any divide_uint32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint32_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint32_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

lessthan

*/
std::any lessthan_uint32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint32_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint32_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

lessthanequal

*/
std::any lessthanequal_uint32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint32_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint32_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

greaterthan

*/
std::any greaterthan_uint32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint32_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint32_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

greaterthanequal

*/
std::any greaterthanequal_uint32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint32_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint32_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

equalequal

*/
std::any equalequal_uint32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint32_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint32_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

notequal

*/
std::any notequal_uint32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint32_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint32_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

cast

*/
std::any cast_uint32_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint32_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint32_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint32_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint32_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint32_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint32_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint32_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint32_t_float(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint32_t_double(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint32_t_string(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint32_t_bool(std::shared_ptr<interpreter> i, std::any& lhs);
/*

uint64_t

*/
/*

add

*/
std::any add_uint64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint64_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_uint64_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

subtract

*/
std::any subtract_uint64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint64_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_uint64_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

multiply

*/
std::any multiply_uint64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint64_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_uint64_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

divide

*/
std::any divide_uint64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint64_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_uint64_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

lessthan

*/
std::any lessthan_uint64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint64_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_uint64_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

lessthanequal

*/
std::any lessthanequal_uint64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint64_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_uint64_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

greaterthan

*/
std::any greaterthan_uint64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint64_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_uint64_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

greaterthanequal

*/
std::any greaterthanequal_uint64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint64_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_uint64_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

equalequal

*/
std::any equalequal_uint64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint64_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_uint64_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

notequal

*/
std::any notequal_uint64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint64_t_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_uint64_t_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

cast

*/
std::any cast_uint64_t_int8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint64_t_int16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint64_t_int32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint64_t_int64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint64_t_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint64_t_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint64_t_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint64_t_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint64_t_float(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint64_t_double(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint64_t_string(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_uint64_t_bool(std::shared_ptr<interpreter> i, std::any& lhs);
/*

float

*/
/*

add

*/
std::any add_float_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_float_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_float_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_float_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_float_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_float_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_float_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_float_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_float_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_float_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

subtract

*/
std::any subtract_float_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_float_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_float_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_float_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_float_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_float_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_float_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_float_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_float_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_float_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

multiply

*/
std::any multiply_float_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_float_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_float_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_float_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_float_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_float_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_float_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_float_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_float_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_float_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

divide

*/
std::any divide_float_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_float_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_float_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_float_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_float_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_float_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_float_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_float_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_float_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_float_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

lessthan

*/
std::any lessthan_float_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_float_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_float_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_float_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_float_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_float_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_float_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_float_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_float_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_float_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

lessthanequal

*/
std::any lessthanequal_float_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_float_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_float_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_float_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_float_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_float_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_float_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_float_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_float_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_float_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

greaterthan

*/
std::any greaterthan_float_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_float_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_float_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_float_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_float_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_float_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_float_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_float_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_float_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_float_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

greaterthanequal

*/
std::any greaterthanequal_float_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_float_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_float_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_float_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_float_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_float_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_float_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_float_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_float_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_float_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

equalequal

*/
std::any equalequal_float_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_float_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_float_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_float_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_float_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_float_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_float_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_float_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_float_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_float_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

notequal

*/
std::any notequal_float_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_float_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_float_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_float_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_float_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_float_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_float_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_float_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_float_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_float_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

cast

*/
std::any cast_float_int8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_float_int16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_float_int32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_float_int64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_float_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_float_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_float_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_float_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_float_float(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_float_double(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_float_string(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_float_bool(std::shared_ptr<interpreter> i, std::any& lhs);
/*

double

*/
/*

add

*/
std::any add_double_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_double_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_double_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_double_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_double_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_double_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_double_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_double_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_double_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_double_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

subtract

*/
std::any subtract_double_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_double_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_double_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_double_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_double_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_double_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_double_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_double_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_double_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_double_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

multiply

*/
std::any multiply_double_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_double_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_double_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_double_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_double_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_double_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_double_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_double_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_double_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_double_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

divide

*/
std::any divide_double_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_double_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_double_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_double_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_double_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_double_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_double_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_double_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_double_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_double_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

lessthan

*/
std::any lessthan_double_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_double_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_double_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_double_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_double_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_double_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_double_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_double_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_double_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_double_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

lessthanequal

*/
std::any lessthanequal_double_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_double_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_double_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_double_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_double_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_double_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_double_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_double_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_double_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_double_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

greaterthan

*/
std::any greaterthan_double_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_double_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_double_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_double_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_double_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_double_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_double_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_double_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_double_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_double_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

greaterthanequal

*/
std::any greaterthanequal_double_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_double_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_double_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_double_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_double_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_double_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_double_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_double_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_double_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_double_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

equalequal

*/
std::any equalequal_double_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_double_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_double_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_double_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_double_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_double_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_double_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_double_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_double_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_double_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

notequal

*/
std::any notequal_double_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_double_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_double_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_double_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_double_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_double_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_double_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_double_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_double_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_double_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
/*

cast

*/
std::any cast_double_int8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_double_int16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_double_int32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_double_int64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_double_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_double_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_double_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_double_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_double_float(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_double_double(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_double_string(std::shared_ptr<interpreter> i, std::any& lhs);
std::any cast_double_bool(std::shared_ptr<interpreter> i, std::any& lhs);
