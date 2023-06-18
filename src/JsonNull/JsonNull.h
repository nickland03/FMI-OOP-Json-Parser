#pragma once

#include "../JsonValue/JsonValue.h"

struct JsonNull final : public JsonValue {
public:
    JsonNull() = default;

    MyString toString() const override;

    JsonValueType getType() const override;

    JsonValue *clone() const override;
};