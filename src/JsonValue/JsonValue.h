#pragma  once

#include "../../third-party/MyString/MyString.h"
#include "../../enums/JsonValueType/JsonValueType.h"

struct JsonValue {
public:
    virtual ~JsonValue() = default;

    virtual MyString toString() const = 0;

    virtual JsonValueType getType() const = 0;

    virtual JsonValue *clone() const = 0;
};