#pragma once

#include "../JsonValue/JsonValue.h"

struct JsonString final : public JsonValue {
private:
    MyString value;

public:
    JsonString() = default;

    explicit JsonString(MyString value);

    MyString toString() const override;

    JsonValueType getType() const override;

    JsonValue *clone() const override;
};