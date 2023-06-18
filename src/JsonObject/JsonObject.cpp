#include "JsonObject.h"

JsonObject::JsonObject(const JsonObject &other) {
    copyFrom(other);
}

JsonObject::JsonObject(JsonObject &&other) noexcept {
    moveFrom(std::move(other));
}

JsonObject &JsonObject::operator=(const JsonObject &other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

JsonObject &JsonObject::operator=(JsonObject &&other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

JsonObject::~JsonObject() {
    free();
}

void JsonObject::addValue(const MyString &key, JsonValue *value, JsonObject *parent) {
    values.push_back(new JsonPair(key, value->clone(), parent));
}

JsonValueType JsonObject::getType() const {
    return JsonValueType::OBJECT;
}

MyString JsonObject::toString() const {
    MyString str("{");
    for (int i = 0; i < values.size(); i++) {
        if (i > 0) {
            str += MyString(",");
        }
        str += MyString("\"") + values[i]->key + MyString("\":");
        str += values[i]->value->toString();
    }
    str += MyString("}");
    return str;
}

JsonValue *JsonObject::clone() const {
    auto obj = new JsonObject();
    for (unsigned i = 0; i < values.size(); i++) {
        obj->values.push_back(new JsonPair(values[i]->key, values[i]->value, values[i]->parent));
    }
    return obj;
}

void JsonObject::copyFrom(const JsonObject &other) {
    for (unsigned i = 0; i < other.values.size(); i++) {
        values.push_back(new JsonPair(other.values[i]->key, other.values[i]->value->clone(), other.values[i]->parent));
    }
}

void JsonObject::moveFrom(JsonObject &&other) {
    values = std::move(other.values);
    other.values = {};
}

void JsonObject::free() {
    for (unsigned i = 0; i < values.size(); i++) {
        delete values[i]->value;
    }
    values.clear();
}

void JsonObject::print(unsigned indentationLevel) const {
    std::cout << "{\n";
    for (size_t i = 0; i < values.size(); i++) {
        std::cout << MyString(' ', indentationLevel + 2) << "\"" << values[i]->key << "\": ";
        if (values[i]->value->getType() == JsonValueType::OBJECT) {
            static_cast<JsonObject *>(values[i]->value)->print(indentationLevel + 2);
        } else if (values[i]->value->getType() == JsonValueType::ARRAY) {
            static_cast<JsonArray *>(values[i]->value)->print(indentationLevel + 2);
        } else {
            std::cout << values[i]->value->toString();
        }
        if (i != values.size() - 1) {
            std::cout << ",";
        }
        std::cout << "\n";
    }
    std::cout << MyString(' ', indentationLevel) << "}";
}

void JsonObject::removeByKey(const MyString &key) {
    Vector<JsonPair *> newValues;
    for (unsigned i = 0; i < values.size(); i++) {
        if (values[i]->key == key) {
            delete values[i];
            continue;
        }
        newValues.push_back(values[i]);
    }
    values = newValues;
}

bool JsonObject::containsKey(const MyString &key) const {
    for (unsigned i = 0; i < values.size(); i++) {
        if (values[i]->key == key) {
            return true;
        }
    }
    return false;
}