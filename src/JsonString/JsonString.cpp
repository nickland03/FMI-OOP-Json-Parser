#include "JsonString.h"

JsonString::JsonString(MyString value) : value(std::move(value)) {}

MyString JsonString::toString() const {
    return MyString("\"") + value + MyString("\"");
}

JsonValueType JsonString::getType() const {
    return JsonValueType::STRING;
}

JsonValue *JsonString::clone() const {
    return new JsonString(value);
}