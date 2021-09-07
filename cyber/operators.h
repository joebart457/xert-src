#pragma once


#include <any>
#include <memory>
#include "interpreter.h"



// Native supported types are int, unsigned long, float, double, bool, std::string, --not char yet
// Custom supported types are list
// Supported binary operations are +, -, /, *, [], <, <=, >, >=, ==, !=,
// Supported unary operations are !, -


std::any type_of_any(std::shared_ptr<interpreter> i, std::any& rhs);

std::any index_list_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any index_list_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any index_list_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);


std::any index_string_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any index_string_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);


// End Custom operators

/* Auto Generated using op_create.scrwl */


/*
-
- start not
-
*/

std::any not_int(std::shared_ptr<interpreter> i, std::any& rhs);
std::any not_unsignedlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any not_float(std::shared_ptr<interpreter> i, std::any& rhs);
std::any not_double(std::shared_ptr<interpreter> i, std::any& rhs);
std::any not_longlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any not_longdouble(std::shared_ptr<interpreter> i, std::any& rhs);
std::any not_bool(std::shared_ptr<interpreter> i, std::any& rhs);
std::any not_string(std::shared_ptr<interpreter> i, std::any& rhs);
std::any not_null(std::shared_ptr<interpreter> i, std::any& rhs);

/*
-
- end not
-
*/


/*
-
- start negate
-
*/

std::any negate_int(std::shared_ptr<interpreter> i, std::any& rhs);
std::any negate_unsignedlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any negate_float(std::shared_ptr<interpreter> i, std::any& rhs);
std::any negate_double(std::shared_ptr<interpreter> i, std::any& rhs);
std::any negate_longlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any negate_longdouble(std::shared_ptr<interpreter> i, std::any& rhs);
std::any negate_bool(std::shared_ptr<interpreter> i, std::any& rhs);
std::any negate_string(std::shared_ptr<interpreter> i, std::any& rhs);
std::any negate_null(std::shared_ptr<interpreter> i, std::any& rhs);

/*
-
- end negate
-
*/


/*
-
- start add
-
*/

std::any add_int_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_int_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any add_unsignedlong_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_unsignedlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_unsignedlong_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_unsignedlong_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_unsignedlong_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_unsignedlong_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_unsignedlong_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_unsignedlong_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_unsignedlong_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any add_float_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_float_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_float_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_float_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_float_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_float_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_float_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_float_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_float_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any add_double_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_double_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_double_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_double_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_double_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_double_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_double_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_double_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_double_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any add_longlong_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_longlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_longlong_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_longlong_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_longlong_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_longlong_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_longlong_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_longlong_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_longlong_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any add_longdouble_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_longdouble_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_longdouble_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_longdouble_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_longdouble_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_longdouble_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_longdouble_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_longdouble_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_longdouble_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any add_bool_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_bool_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_bool_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_bool_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_bool_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_bool_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_bool_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_bool_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any add_string_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_string_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_string_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_string_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_string_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_string_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_string_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_string_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_string_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any add_null_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_null_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_null_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_null_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_null_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_null_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_null_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_null_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any add_null_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);


/*
-
- end add
-
*/


/*
-
- start subtract
-
*/

std::any subtract_int_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_int_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any subtract_unsignedlong_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_unsignedlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_unsignedlong_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_unsignedlong_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_unsignedlong_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_unsignedlong_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_unsignedlong_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_unsignedlong_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_unsignedlong_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any subtract_float_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_float_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_float_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_float_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_float_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_float_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_float_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_float_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_float_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any subtract_double_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_double_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_double_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_double_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_double_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_double_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_double_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_double_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_double_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any subtract_longlong_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_longlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_longlong_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_longlong_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_longlong_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_longlong_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_longlong_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_longlong_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_longlong_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any subtract_longdouble_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_longdouble_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_longdouble_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_longdouble_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_longdouble_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_longdouble_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_longdouble_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_longdouble_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_longdouble_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any subtract_bool_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_bool_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_bool_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_bool_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_bool_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_bool_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_bool_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_bool_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any subtract_string_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_string_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_string_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_string_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_string_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_string_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_string_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_string_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_string_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any subtract_null_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_null_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_null_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_null_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_null_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_null_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_null_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_null_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any subtract_null_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);


/*
-
- end subtract
-
*/


/*
-
- start multiply
-
*/

std::any multiply_int_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_int_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any multiply_unsignedlong_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_unsignedlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_unsignedlong_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_unsignedlong_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_unsignedlong_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_unsignedlong_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_unsignedlong_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_unsignedlong_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_unsignedlong_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any multiply_float_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_float_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_float_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_float_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_float_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_float_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_float_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_float_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_float_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any multiply_double_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_double_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_double_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_double_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_double_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_double_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_double_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_double_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_double_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any multiply_longlong_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_longlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_longlong_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_longlong_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_longlong_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_longlong_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_longlong_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_longlong_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_longlong_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any multiply_longdouble_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_longdouble_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_longdouble_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_longdouble_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_longdouble_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_longdouble_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_longdouble_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_longdouble_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_longdouble_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any multiply_bool_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_bool_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_bool_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_bool_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_bool_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_bool_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_bool_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_bool_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any multiply_string_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_string_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_string_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_string_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_string_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_string_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_string_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_string_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_string_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any multiply_null_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_null_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_null_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_null_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_null_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_null_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_null_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_null_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any multiply_null_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);


/*
-
- end multiply
-
*/


/*
-
- start divide
-
*/

std::any divide_int_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_int_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any divide_unsignedlong_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_unsignedlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_unsignedlong_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_unsignedlong_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_unsignedlong_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_unsignedlong_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_unsignedlong_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_unsignedlong_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_unsignedlong_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any divide_float_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_float_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_float_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_float_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_float_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_float_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_float_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_float_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_float_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any divide_double_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_double_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_double_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_double_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_double_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_double_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_double_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_double_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_double_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any divide_longlong_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_longlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_longlong_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_longlong_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_longlong_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_longlong_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_longlong_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_longlong_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_longlong_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any divide_longdouble_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_longdouble_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_longdouble_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_longdouble_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_longdouble_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_longdouble_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_longdouble_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_longdouble_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_longdouble_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any divide_bool_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_bool_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_bool_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_bool_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_bool_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_bool_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_bool_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_bool_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any divide_string_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_string_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_string_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_string_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_string_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_string_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_string_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_string_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_string_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any divide_null_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_null_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_null_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_null_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_null_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_null_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_null_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_null_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any divide_null_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);


/*
-
- end divide
-
*/


/*
-
- start lessthan
-
*/

std::any lessthan_int_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_int_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any lessthan_unsignedlong_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_unsignedlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_unsignedlong_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_unsignedlong_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_unsignedlong_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_unsignedlong_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_unsignedlong_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_unsignedlong_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_unsignedlong_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any lessthan_float_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_float_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_float_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_float_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_float_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_float_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_float_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_float_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_float_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any lessthan_double_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_double_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_double_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_double_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_double_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_double_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_double_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_double_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_double_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any lessthan_longlong_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_longlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_longlong_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_longlong_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_longlong_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_longlong_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_longlong_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_longlong_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_longlong_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any lessthan_longdouble_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_longdouble_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_longdouble_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_longdouble_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_longdouble_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_longdouble_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_longdouble_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_longdouble_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_longdouble_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any lessthan_bool_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_bool_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_bool_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_bool_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_bool_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_bool_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_bool_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_bool_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any lessthan_string_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_string_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_string_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_string_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_string_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_string_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_string_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_string_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_string_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any lessthan_null_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_null_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_null_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_null_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_null_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_null_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_null_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_null_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthan_null_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);


/*
-
- end lessthan
-
*/


/*
-
- start lessthanequal
-
*/

std::any lessthanequal_int_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_int_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any lessthanequal_unsignedlong_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_unsignedlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_unsignedlong_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_unsignedlong_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_unsignedlong_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_unsignedlong_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_unsignedlong_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_unsignedlong_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_unsignedlong_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any lessthanequal_float_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_float_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_float_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_float_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_float_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_float_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_float_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_float_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_float_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any lessthanequal_double_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_double_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_double_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_double_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_double_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_double_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_double_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_double_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_double_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any lessthanequal_longlong_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_longlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_longlong_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_longlong_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_longlong_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_longlong_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_longlong_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_longlong_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_longlong_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any lessthanequal_longdouble_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_longdouble_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_longdouble_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_longdouble_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_longdouble_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_longdouble_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_longdouble_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_longdouble_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_longdouble_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any lessthanequal_bool_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_bool_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_bool_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_bool_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_bool_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_bool_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_bool_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_bool_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any lessthanequal_string_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_string_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_string_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_string_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_string_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_string_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_string_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_string_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_string_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any lessthanequal_null_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_null_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_null_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_null_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_null_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_null_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_null_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_null_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any lessthanequal_null_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);


/*
-
- end lessthanequal
-
*/


/*
-
- start greaterthan
-
*/

std::any greaterthan_int_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_int_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any greaterthan_unsignedlong_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_unsignedlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_unsignedlong_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_unsignedlong_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_unsignedlong_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_unsignedlong_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_unsignedlong_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_unsignedlong_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_unsignedlong_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any greaterthan_float_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_float_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_float_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_float_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_float_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_float_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_float_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_float_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_float_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any greaterthan_double_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_double_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_double_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_double_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_double_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_double_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_double_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_double_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_double_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any greaterthan_longlong_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_longlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_longlong_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_longlong_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_longlong_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_longlong_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_longlong_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_longlong_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_longlong_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any greaterthan_longdouble_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_longdouble_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_longdouble_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_longdouble_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_longdouble_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_longdouble_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_longdouble_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_longdouble_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_longdouble_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any greaterthan_bool_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_bool_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_bool_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_bool_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_bool_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_bool_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_bool_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_bool_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any greaterthan_string_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_string_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_string_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_string_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_string_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_string_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_string_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_string_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_string_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any greaterthan_null_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_null_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_null_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_null_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_null_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_null_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_null_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_null_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthan_null_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);


/*
-
- end greaterthan
-
*/


/*
-
- start greaterthanequal
-
*/

std::any greaterthanequal_int_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_int_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any greaterthanequal_unsignedlong_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_unsignedlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_unsignedlong_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_unsignedlong_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_unsignedlong_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_unsignedlong_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_unsignedlong_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_unsignedlong_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_unsignedlong_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any greaterthanequal_float_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_float_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_float_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_float_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_float_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_float_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_float_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_float_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_float_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any greaterthanequal_double_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_double_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_double_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_double_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_double_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_double_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_double_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_double_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_double_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any greaterthanequal_longlong_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_longlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_longlong_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_longlong_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_longlong_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_longlong_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_longlong_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_longlong_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_longlong_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any greaterthanequal_longdouble_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_longdouble_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_longdouble_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_longdouble_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_longdouble_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_longdouble_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_longdouble_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_longdouble_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_longdouble_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any greaterthanequal_bool_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_bool_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_bool_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_bool_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_bool_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_bool_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_bool_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_bool_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any greaterthanequal_string_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_string_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_string_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_string_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_string_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_string_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_string_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_string_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_string_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any greaterthanequal_null_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_null_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_null_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_null_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_null_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_null_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_null_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_null_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any greaterthanequal_null_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);


/*
-
- end greaterthanequal
-
*/


/*
-
- start equalequal
-
*/

std::any equalequal_int_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_int_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any equalequal_unsignedlong_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_unsignedlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_unsignedlong_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_unsignedlong_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_unsignedlong_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_unsignedlong_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_unsignedlong_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_unsignedlong_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_unsignedlong_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any equalequal_float_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_float_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_float_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_float_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_float_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_float_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_float_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_float_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_float_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any equalequal_double_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_double_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_double_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_double_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_double_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_double_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_double_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_double_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_double_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any equalequal_longlong_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_longlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_longlong_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_longlong_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_longlong_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_longlong_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_longlong_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_longlong_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_longlong_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any equalequal_longdouble_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_longdouble_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_longdouble_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_longdouble_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_longdouble_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_longdouble_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_longdouble_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_longdouble_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_longdouble_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any equalequal_bool_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_bool_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_bool_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_bool_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_bool_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_bool_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_bool_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_bool_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any equalequal_string_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_string_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_string_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_string_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_string_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_string_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_string_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_string_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_string_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any equalequal_null_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_null_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_null_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_null_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_null_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_null_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_null_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_null_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any equalequal_null_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);


/*
-
- end equalequal
-
*/


/*
-
- start notequal
-
*/

std::any notequal_int_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_int_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any notequal_unsignedlong_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_unsignedlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_unsignedlong_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_unsignedlong_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_unsignedlong_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_unsignedlong_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_unsignedlong_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_unsignedlong_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_unsignedlong_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any notequal_float_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_float_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_float_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_float_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_float_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_float_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_float_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_float_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_float_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any notequal_double_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_double_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_double_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_double_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_double_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_double_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_double_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_double_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_double_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any notequal_longlong_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_longlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_longlong_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_longlong_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_longlong_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_longlong_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_longlong_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_longlong_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_longlong_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any notequal_longdouble_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_longdouble_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_longdouble_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_longdouble_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_longdouble_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_longdouble_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_longdouble_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_longdouble_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_longdouble_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any notequal_bool_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_bool_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_bool_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_bool_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_bool_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_bool_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_bool_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_bool_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any notequal_string_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_string_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_string_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_string_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_string_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_string_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_string_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_string_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_string_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);

std::any notequal_null_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_null_unsignedlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_null_float(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_null_double(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_null_longlong(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_null_longdouble(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_null_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_null_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);
std::any notequal_null_null(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);


/*
-
- end notequal
-
*/


/*
-
- start cast
-
*/

std::any cast_int_int(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_int_unsignedlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_int_float(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_int_double(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_int_longlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_int_longdouble(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_int_bool(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_int_string(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_int_null(std::shared_ptr<interpreter> i, std::any& rhs);

std::any cast_unsignedlong_int(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_unsignedlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_unsignedlong_float(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_unsignedlong_double(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_unsignedlong_longlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_unsignedlong_longdouble(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_unsignedlong_bool(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_unsignedlong_string(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_unsignedlong_null(std::shared_ptr<interpreter> i, std::any& rhs);

std::any cast_float_int(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_float_unsignedlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_float_float(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_float_double(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_float_longlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_float_longdouble(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_float_bool(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_float_string(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_float_null(std::shared_ptr<interpreter> i, std::any& rhs);

std::any cast_double_int(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_double_unsignedlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_double_float(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_double_double(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_double_longlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_double_longdouble(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_double_bool(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_double_string(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_double_null(std::shared_ptr<interpreter> i, std::any& rhs);

std::any cast_longlong_int(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_longlong_unsignedlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_longlong_float(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_longlong_double(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_longlong_longlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_longlong_longdouble(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_longlong_bool(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_longlong_string(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_longlong_null(std::shared_ptr<interpreter> i, std::any& rhs);

std::any cast_longdouble_int(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_longdouble_unsignedlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_longdouble_float(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_longdouble_double(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_longdouble_longlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_longdouble_longdouble(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_longdouble_bool(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_longdouble_string(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_longdouble_null(std::shared_ptr<interpreter> i, std::any& rhs);

std::any cast_bool_int(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_bool_unsignedlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_bool_float(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_bool_double(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_bool_longlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_bool_longdouble(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_bool_bool(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_bool_string(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_bool_null(std::shared_ptr<interpreter> i, std::any& rhs);

std::any cast_string_int(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_string_unsignedlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_string_float(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_string_double(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_string_longlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_string_longdouble(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_string_bool(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_string_string(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_string_null(std::shared_ptr<interpreter> i, std::any& rhs);

std::any cast_null_int(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_null_unsignedlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_null_float(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_null_double(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_null_longlong(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_null_longdouble(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_null_bool(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_null_string(std::shared_ptr<interpreter> i, std::any& rhs);
std::any cast_null_null(std::shared_ptr<interpreter> i, std::any& rhs);


/*
-
- end cast
-
*/

/* End Auto Generation */