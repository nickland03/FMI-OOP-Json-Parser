#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include "../../third-party/Vector/Vector.hpp"
#include "../../constants/globalConstants.h"
#include "../../enums/JsonValueType/JsonValueType.h"
#include "../JsonValue/JsonValue.h"
#include "../JsonString/JsonString.h"
#include "../JsonNumber/JsonNumber.h"
#include "../JsonBoolean/JsonBoolean.h"
#include "../JsonNull/JsonNull.h"
#include "../JsonObject/JsonObject.h"
#include "../JsonArray/JsonArray.h"

class JsonParser final {
    struct KV final {
        MyString key, value;
    };

private:
    JsonObject *json = nullptr;

    void free();

    static unsigned getFileSize(std::ifstream &in);

    static MyString minify(const MyString &jsonString);

    static JsonValueType getValueType(const MyString &value);

    static JsonBoolean *boolStringToJsonBoolean(const MyString &boolString);

    static MyString unwrap(const MyString &value, char symbol);

    static Vector<MyString> split(const MyString &s);

    static KV extractKeyValue(const MyString &str);

    static JsonArray *parseArray(const MyString &arrayString);

    static JsonObject *parseObject(JsonObject *root, const MyString &jsonString);

    static Vector<JsonObject::JsonPair *> searchArray(const MyString &key, const JsonArray *arr);

    static Vector<JsonObject::JsonPair *> searchObject(const MyString &key, const JsonObject *obj);

public:
    explicit JsonParser(const MyString &jsonFileName);

    explicit JsonParser(const char *jsonFileName);

    ~JsonParser();

    void print() const;

    void list(const MyString &key) const;

    void list(const char *key) const;

    void remove(const MyString& path);

    void remove(const char* path);
};