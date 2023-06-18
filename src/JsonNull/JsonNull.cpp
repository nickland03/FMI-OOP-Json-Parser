#include "JsonNull.h"

MyString JsonNull::toString() const {
    return MyString("null");
}

JsonValueType JsonNull::getType() const {
    return JsonValueType::NULLVAL;
}

JsonValue *JsonNull::clone() const {
    return new JsonNull();
}