#include "JsonNumber.h"

JsonNumber::JsonNumber(MyString value) : value(std::move(value)) {}

MyString JsonNumber::toString() const {
    return value;
}

JsonValueType JsonNumber::getType() const {
    return JsonValueType::NUMBER;
}

JsonValue *JsonNumber::clone() const {
    return new JsonNumber(value);
}