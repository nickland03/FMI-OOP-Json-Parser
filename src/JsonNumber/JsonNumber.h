#pragma once

#include "../JsonValue/JsonValue.h"

struct JsonNumber final : public JsonValue {
private:
    MyString value;
public:
    JsonNumber() = default;

    explicit JsonNumber(MyString value);

    MyString toString() const override;

    JsonValueType getType() const override;

    JsonValue *clone() const override;
};