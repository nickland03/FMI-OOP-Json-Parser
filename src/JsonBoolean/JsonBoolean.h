#pragma once

#include "../JsonValue/JsonValue.h"

struct JsonBoolean final : public JsonValue {
private:
    bool value{};

public:
    JsonBoolean() = default;

    explicit JsonBoolean(bool value);

    MyString toString() const override;

    JsonValueType getType() const override;

    JsonValue *clone() const override;
};