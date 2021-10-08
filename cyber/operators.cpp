#include "operators.h"

#include "klass_instance.h"
#include "exceptions.hpp"
#include "Utilities.h"

#include <stdexcept>

/*
* 
* Necessary for operator Auto Generation capabilites
*  
std::any equalequal_string_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    return std::any_cast<std::string>(lhs) == std::any_cast<std::string>(rhs);
}

std::any less_than_int_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    return std::any_cast<int>(lhs) < std::any_cast<int>(rhs);
}

std::any index_list_int(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    int index = std::any_cast<int>(rhs);
    klass_instance instance = std::any_cast<klass_instance>(lhs);
    return instance.Get(std::to_string(index), location());
}

std::any add_string_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    return std::any_cast<std::string>(lhs) + std::any_cast<std::string>(rhs);
}

*/

std::any type_of_any(std::shared_ptr<interpreter> i, std::any& rhs)
{
	return std::string(rhs.type().name());
}


std::any index_list_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    int8_t index = std::any_cast<int8_t>(rhs);
    klass_instance instance = std::any_cast<klass_instance>(lhs);
    auto raw = instance.Get<std::shared_ptr<std::vector<std::any>>>("__raw__", location());
    if (raw == nullptr) {
        throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "__raw__ was nullptr", Severity().HIGH());
    }
    if (raw->size() <= index) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "index " + std::to_string(index) + " out of range", Severity().MEDIUM());
    }
    return raw->at(index);
}
std::any index_list_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    int16_t index = std::any_cast<int16_t>(rhs);
    klass_instance instance = std::any_cast<klass_instance>(lhs);
    auto raw = instance.Get<std::shared_ptr<std::vector<std::any>>>("__raw__", location());
    if (raw == nullptr) {
        throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "__raw__ was nullptr", Severity().HIGH());
    }
    if (raw->size() <= index) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "index " + std::to_string(index) + " out of range", Severity().MEDIUM());
    }
    return raw->at(index);
}
std::any index_list_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    int32_t index = std::any_cast<int32_t>(rhs);
    klass_instance instance = std::any_cast<klass_instance>(lhs);
    auto raw = instance.Get<std::shared_ptr<std::vector<std::any>>>("__raw__", location());
    if (raw == nullptr) {
        throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "__raw__ was nullptr", Severity().HIGH());
    }
    if (raw->size() <= index) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "index " + std::to_string(index) + " out of range", Severity().MEDIUM());
    }
    return raw->at(index);
}
std::any index_list_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    int64_t index = std::any_cast<int64_t>(rhs);
    klass_instance instance = std::any_cast<klass_instance>(lhs);
    auto raw = instance.Get<std::shared_ptr<std::vector<std::any>>>("__raw__", location());
    if (raw == nullptr) {
        throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "__raw__ was nullptr", Severity().HIGH());
    }
    if (raw->size() <= index) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "index " + std::to_string(index) + " out of range", Severity().MEDIUM());
    }
    return raw->at(index);
}

std::any index_list_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    uint8_t index = std::any_cast<uint8_t>(rhs);
    klass_instance instance = std::any_cast<klass_instance>(lhs);
    auto raw = instance.Get<std::shared_ptr<std::vector<std::any>>>("__raw__", location());
    if (raw == nullptr) {
        throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "__raw__ was nullptr", Severity().HIGH());
    }
    if (raw->size() <= index) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "index " + std::to_string(index) + " out of range", Severity().MEDIUM());
    }
    return raw->at(index);
}
std::any index_list_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    uint16_t index = std::any_cast<uint16_t>(rhs);
    klass_instance instance = std::any_cast<klass_instance>(lhs);
    auto raw = instance.Get<std::shared_ptr<std::vector<std::any>>>("__raw__", location());
    if (raw == nullptr) {
        throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "__raw__ was nullptr", Severity().HIGH());
    }
    if (raw->size() <= index) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "index " + std::to_string(index) + " out of range", Severity().MEDIUM());
    }
    return raw->at(index);
}
std::any index_list_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    uint32_t index = std::any_cast<uint32_t>(rhs);
    klass_instance instance = std::any_cast<klass_instance>(lhs);
    auto raw = instance.Get<std::shared_ptr<std::vector<std::any>>>("__raw__", location());
    if (raw == nullptr) {
        throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "__raw__ was nullptr", Severity().HIGH());
    }
    if (raw->size() <= index) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "index " + std::to_string(index) + " out of range", Severity().MEDIUM());
    }
    return raw->at(index);
}
std::any index_list_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    uint64_t index = std::any_cast<uint64_t>(rhs);
    klass_instance instance = std::any_cast<klass_instance>(lhs);
    auto raw = instance.Get<std::shared_ptr<std::vector<std::any>>>("__raw__", location());
    if (raw == nullptr) {
        throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "__raw__ was nullptr", Severity().HIGH());
    }
    if (raw->size() <= index) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "index " + std::to_string(index) + " out of range", Severity().MEDIUM());
    }
    return raw->at(index);
}

std::any index_string_int8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    std::string lhsVal = std::any_cast<std::string>(lhs);
    auto rhsVal = std::any_cast<int8_t>(rhs);

    if (rhsVal < lhsVal.size()) {
        return std::string(lhsVal.at(rhsVal), 1);
    }
    throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "string index out of range", Severity().MEDIUM());
}
std::any index_string_int16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    std::string lhsVal = std::any_cast<std::string>(lhs);
    auto rhsVal = std::any_cast<int16_t>(rhs);

    if (rhsVal < lhsVal.size()) {
        return std::string(lhsVal.at(rhsVal), 1);
    }
    throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "string index out of range", Severity().MEDIUM());
}
std::any index_string_int32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    std::string lhsVal = std::any_cast<std::string>(lhs);
    auto rhsVal = std::any_cast<int32_t>(rhs);

    if (rhsVal < lhsVal.size()) {
        return std::string(lhsVal.at(rhsVal), 1);
    }
    throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "string index out of range", Severity().MEDIUM());
}
std::any index_string_int64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    std::string lhsVal = std::any_cast<std::string>(lhs);
    auto rhsVal = std::any_cast<int64_t>(rhs);

    if (rhsVal < lhsVal.size()) {
        return std::string(lhsVal.at(rhsVal), 1);
    }
    throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "string index out of range", Severity().MEDIUM());
}
std::any index_string_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    std::string lhsVal = std::any_cast<std::string>(lhs);
    auto rhsVal = std::any_cast<uint8_t>(rhs);

    if (rhsVal < lhsVal.size()) {
        return std::string(lhsVal.at(rhsVal), 1);
    }
    throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "string index out of range", Severity().MEDIUM());
}
std::any index_string_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    std::string lhsVal = std::any_cast<std::string>(lhs);
    auto rhsVal = std::any_cast<uint16_t>(rhs);

    if (rhsVal < lhsVal.size()) {
        return std::string(lhsVal.at(rhsVal), 1);
    }
    throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "string index out of range", Severity().MEDIUM());
}
std::any index_string_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    std::string lhsVal = std::any_cast<std::string>(lhs);
    auto rhsVal = std::any_cast<uint32_t>(rhs);

    if (rhsVal < lhsVal.size()) {
        return std::string(lhsVal.at(rhsVal), 1);
    }
    throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "string index out of range", Severity().MEDIUM());
}
std::any index_string_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    std::string lhsVal = std::any_cast<std::string>(lhs);
    auto rhsVal = std::any_cast<uint64_t>(rhs);

    if (rhsVal < lhsVal.size()) {
        return std::string(lhsVal.at(rhsVal), 1);
    }
    throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "string index out of range", Severity().MEDIUM());
}


std::any index_map_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    std::string szName = std::any_cast<std::string>(rhs);

    klass_instance instance = std::any_cast<klass_instance>(lhs);
    return instance.Get(szName, location());
}

std::any not_string(std::shared_ptr<interpreter> i, std::any& rhs)
{
    return !Utilities().isTruthy(rhs);
}
std::any not_null(std::shared_ptr<interpreter> i, std::any& rhs)
{
    return !Utilities().isTruthy(rhs);
}

std::any add_string_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    return std::any_cast<std::string>(lhs) + std::any_cast<std::string>(rhs);
}

std::any equalequal_string_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    return std::any_cast<std::string>(lhs) == std::any_cast<std::string>(rhs);
}

std::any notequal_string_string(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)\
{
    return std::any_cast<std::string>(lhs) != std::any_cast<std::string>(rhs);
}

std::any cast_string_int8_t(std::shared_ptr<interpreter> i, std::any& lhs)
{
    try {
        std::string lhsVal = std::any_cast<std::string>(lhs);
        return static_cast<int8_t>(std::stoi(lhsVal));
    }
    catch (std::invalid_argument) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to cast " + Utilities().stringify(lhs) + " to type int8_t", Severity().MEDIUM());
    }
    catch (std::out_of_range) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to cast " + Utilities().stringify(lhs) + " to type int8_t", Severity().MEDIUM());
    }
}
std::any cast_string_int16_t(std::shared_ptr<interpreter> i, std::any& lhs)
{
    try {
        std::string lhsVal = std::any_cast<std::string>(lhs);
        return static_cast<int16_t>(std::stoi(lhsVal));
    }
    catch (std::invalid_argument) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to cast " + Utilities().stringify(lhs) + " to type int16_t", Severity().MEDIUM());
    }
    catch (std::out_of_range) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to cast " + Utilities().stringify(lhs) + " to type int16_t", Severity().MEDIUM());
    }
}
std::any cast_string_int32_t(std::shared_ptr<interpreter> i, std::any& lhs)
{
    try {
        std::string lhsVal = std::any_cast<std::string>(lhs);
        return static_cast<int32_t>(std::stoi(lhsVal));
    }
    catch (std::invalid_argument) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to cast " + Utilities().stringify(lhs) + " to type int32_t", Severity().MEDIUM());
    }
    catch (std::out_of_range) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to cast " + Utilities().stringify(lhs) + " to type int32_t", Severity().MEDIUM());
    }
}
std::any cast_string_int64_t(std::shared_ptr<interpreter> i, std::any& lhs)
{
    try {
        std::string lhsVal = std::any_cast<std::string>(lhs);
        return static_cast<int64_t>(std::stoll(lhsVal));
    }
    catch (std::invalid_argument) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to cast " + Utilities().stringify(lhs) + " to type int64_t", Severity().MEDIUM());
    }
    catch (std::out_of_range) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to cast " + Utilities().stringify(lhs) + " to type int64_t", Severity().MEDIUM());
    }
}
std::any cast_string_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs)
{
    try {
        std::string lhsVal = std::any_cast<std::string>(lhs);
        return static_cast<uint8_t>(std::stoi(lhsVal));
    }
    catch (std::invalid_argument) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to cast " + Utilities().stringify(lhs) + " to type uint8_t", Severity().MEDIUM());
    }
    catch (std::out_of_range) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to cast " + Utilities().stringify(lhs) + " to type uint8_t", Severity().MEDIUM());
    }
}
std::any cast_string_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs)
{
    try {
        std::string lhsVal = std::any_cast<std::string>(lhs);
        return static_cast<uint16_t>(std::stoi(lhsVal));
    }
    catch (std::invalid_argument) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to cast " + Utilities().stringify(lhs) + " to type uint16_t", Severity().MEDIUM());
    }
    catch (std::out_of_range) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to cast " + Utilities().stringify(lhs) + " to type uint16_t", Severity().MEDIUM());
    }
}
std::any cast_string_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs)
{
    try {
        std::string lhsVal = std::any_cast<std::string>(lhs);
        return static_cast<uint32_t>(std::stoi(lhsVal));
    }
    catch (std::invalid_argument) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to cast " + Utilities().stringify(lhs) + " to type uint32_t", Severity().MEDIUM());
    }
    catch (std::out_of_range) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to cast " + Utilities().stringify(lhs) + " to type uint32_t", Severity().MEDIUM());
    }
}
std::any cast_string_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs)
{
    try {
        std::string lhsVal = std::any_cast<std::string>(lhs);
        return static_cast<uint64_t>(std::stoull(lhsVal));
    }
    catch (std::invalid_argument) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to cast " + Utilities().stringify(lhs) + " to type uint64_t", Severity().MEDIUM());
    }
    catch (std::out_of_range) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to cast " + Utilities().stringify(lhs) + " to type uint64_t", Severity().MEDIUM());
    }
}
std::any cast_string_float(std::shared_ptr<interpreter> i, std::any& lhs)
{
    try {
        std::string lhsVal = std::any_cast<std::string>(lhs);
        return static_cast<float>(std::stof(lhsVal));
    }
    catch (std::invalid_argument) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to cast " + Utilities().stringify(lhs) + " to type float", Severity().MEDIUM());
    }
    catch (std::out_of_range) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to cast " + Utilities().stringify(lhs) + " to type float", Severity().MEDIUM());
    }
}
std::any cast_string_double(std::shared_ptr<interpreter> i, std::any& lhs)
{
    try {
        std::string lhsVal = std::any_cast<std::string>(lhs);
        return static_cast<double>(std::stod(lhsVal));
    }
    catch (std::invalid_argument) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to cast " + Utilities().stringify(lhs) + " to type double", Severity().MEDIUM());
    }
    catch (std::out_of_range) {
        throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "unable to cast " + Utilities().stringify(lhs) + " to type double", Severity().MEDIUM());
    }
}
std::any cast_string_string(std::shared_ptr<interpreter> i, std::any& lhs)
{
    return std::any_cast<std::string>(lhs);
}

/* Boolean support */

std::any not_bool(std::shared_ptr<interpreter> i, std::any& rhs)
{
    return !Utilities().isTruthy(rhs);
}

std::any cast_bool_int8_t(std::shared_ptr<interpreter> i, std::any& lhs)
{
    bool lhsVal = std::any_cast<bool>(lhs);
    return static_cast<int8_t>(lhsVal);
}
std::any cast_bool_int16_t(std::shared_ptr<interpreter> i, std::any& lhs)
{
    bool lhsVal = std::any_cast<bool>(lhs);
    return static_cast<int16_t>(lhsVal);
}
std::any cast_bool_int32_t(std::shared_ptr<interpreter> i, std::any& lhs)
{
    bool lhsVal = std::any_cast<bool>(lhs);
    return static_cast<int32_t>(lhsVal);
}
std::any cast_bool_int64_t(std::shared_ptr<interpreter> i, std::any& lhs)
{
    bool lhsVal = std::any_cast<bool>(lhs);
    return static_cast<int64_t>(lhsVal);
}
std::any cast_bool_uint8_t(std::shared_ptr<interpreter> i, std::any& lhs)
{
    bool lhsVal = std::any_cast<bool>(lhs);
    return static_cast<uint8_t>(lhsVal);
}
std::any cast_bool_uint16_t(std::shared_ptr<interpreter> i, std::any& lhs)
{
    bool lhsVal = std::any_cast<bool>(lhs);
    return static_cast<uint16_t>(lhsVal);
}
std::any cast_bool_uint32_t(std::shared_ptr<interpreter> i, std::any& lhs)
{
    bool lhsVal = std::any_cast<bool>(lhs);
    return static_cast<uint32_t>(lhsVal);
}
std::any cast_bool_uint64_t(std::shared_ptr<interpreter> i, std::any& lhs)
{
    bool lhsVal = std::any_cast<bool>(lhs);
    return static_cast<uint64_t>(lhsVal);
}
std::any cast_bool_float(std::shared_ptr<interpreter> i, std::any& lhs)
{
    bool lhsVal = std::any_cast<bool>(lhs);
    return static_cast<float>(lhsVal);
}
std::any cast_bool_double(std::shared_ptr<interpreter> i, std::any& lhs)
{
    bool lhsVal = std::any_cast<bool>(lhs);
    return static_cast<double>(lhsVal);
}
std::any cast_bool_string(std::shared_ptr<interpreter> i, std::any& lhs)
{
    bool lhsVal = std::any_cast<bool>(lhs);
    return std::to_string(lhsVal);
}


std::any lessthan_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    return std::any_cast<bool>(lhs) < std::any_cast<bool>(rhs);
}
std::any lessthanequal_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    return std::any_cast<bool>(lhs) <= std::any_cast<bool>(rhs);
}
std::any greaterthan_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    return std::any_cast<bool>(lhs) > std::any_cast<bool>(rhs);
}
std::any greaterthanequal_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    return std::any_cast<bool>(lhs) >= std::any_cast<bool>(rhs);
}
std::any equalequal_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    return std::any_cast<bool>(lhs) == std::any_cast<bool>(rhs);
}
std::any notequal_bool_bool(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)
{
    return std::any_cast<bool>(lhs) != std::any_cast<bool>(rhs);
}

/* End Custom Defined Binary Operators */
