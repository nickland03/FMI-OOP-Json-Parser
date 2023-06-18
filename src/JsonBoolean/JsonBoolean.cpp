#include "JsonBoolean.h"

JsonBoolean::JsonBoolean(bool value) : value(value) {}

MyString JsonBoolean::toString() const {
    return value ? MyString("true") : MyString("false");
}

JsonValueType JsonBoolean::getType() const {
    return JsonValueType::BOOL;
}

JsonValue *JsonBoolean::clone() const {
    return new JsonBoolean(value);
}