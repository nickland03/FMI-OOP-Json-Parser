#pragma once

#include "../../third-party/Vector/Vector.hpp"
#include "../JsonValue/JsonValue.h"
#include "../JsonObject/JsonObject.h"

struct JsonArray final : public JsonValue {
private:
    Vector<JsonValue *> values;

    void copyFrom(const JsonArray &other);

    void moveFrom(JsonArray &&other);

    void free();

public:
    JsonArray() = default;

    JsonArray(const JsonArray &other);

    JsonArray(JsonArray &&other) noexcept;

    JsonArray &operator=(const JsonArray &other);

    JsonArray &operator=(JsonArray &&other) noexcept;

    ~JsonArray() override;

    void addValue(JsonValue *value);

    JsonValueType getType() const override;

    MyString toString() const override;

    JsonValue *clone() const override;

    const Vector<JsonValue *> &getValues() const { return values; };

    void print(unsigned indentationLevel) const;
};