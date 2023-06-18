#pragma once

#include "../../third-party/Vector/Vector.hpp"
#include "../JsonValue/JsonValue.h"
#include "../JsonArray/JsonArray.h"

struct JsonObject final : public JsonValue {
    struct JsonPair final {
        MyString key;
        JsonValue *value{};
        JsonObject *parent{};

        JsonPair(const MyString &k, JsonValue *v, JsonObject *parent) {
            this->key = k;
            this->value = v;
            this->parent = parent;
        }

        JsonPair(const JsonPair &other) = delete;

        JsonPair(JsonPair &&other) = delete;

        JsonPair &operator=(const JsonPair &other) = delete;

        JsonPair &operator=(JsonPair &&other) = delete;

        ~JsonPair() {
            value = nullptr;
            parent = nullptr;
        }
    };

private:
    Vector<JsonPair *> values;

    void copyFrom(const JsonObject &other);

    void moveFrom(JsonObject &&other);

    void free();

public:
    JsonObject() = default;

    JsonObject(const JsonObject &other);

    JsonObject(JsonObject &&other) noexcept;

    JsonObject &operator=(const JsonObject &other);

    JsonObject &operator=(JsonObject &&other) noexcept;

    ~JsonObject() override;

    void addValue(const MyString &key, JsonValue *value, JsonObject *parent);

    const Vector<JsonPair *> &getValues() const { return values; };

    JsonValueType getType() const override;

    MyString toString() const override;

    JsonValue *clone() const override;

    void print(unsigned indentationLevel) const;

    void removeByKey(const MyString& key);

    bool containsKey(const MyString& key) const;
};