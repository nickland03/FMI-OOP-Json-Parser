#include "JsonArray.h"

JsonArray::JsonArray(const JsonArray &other) {
    copyFrom(other);
}

JsonArray::JsonArray(JsonArray &&other) noexcept {
    moveFrom(std::move(other));
}

JsonArray &JsonArray::operator=(const JsonArray &other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

JsonArray &JsonArray::operator=(JsonArray &&other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

JsonArray::~JsonArray() {
    free();
}

void JsonArray::addValue(JsonValue *value) {
    values.push_back(value);
}

JsonValueType JsonArray::getType() const {
    return JsonValueType::ARRAY;
}

MyString JsonArray::toString() const {
    MyString str("[");
    for (unsigned i = 0; i < values.size(); i++) {
        auto value = values[i];
        if (value != values.front()) {
            str += MyString(",");
        }
        str += value->toString();
    }
    str += MyString("]");
    return str;
}

JsonValue *JsonArray::clone() const {
    auto obj = new JsonArray();
    for (unsigned i = 0; i < values.size(); i++) {
        obj->addValue(values[i]->clone());
    }
    return obj;
}

void JsonArray::copyFrom(const JsonArray &other) {
    values = other.values;
}

void JsonArray::moveFrom(JsonArray &&other) {
    values = std::move(other.values);
    other.values = {};
}

void JsonArray::free() {
    for (unsigned i = 0; i < values.size(); i++) {
        delete values[i];
    }
    values.clear();
}

void JsonArray::print(unsigned indentationLevel) const {
    std::cout << "[\n";
    for (size_t i = 0; i < values.size(); i++) {
        std::cout << MyString(' ', indentationLevel + 2);
        if (values[i]->getType() == JsonValueType::OBJECT) {
            static_cast<JsonObject *>(values[i])->print(indentationLevel + 2);
        } else if (values[i]->getType() == JsonValueType::ARRAY) {
            static_cast<JsonArray *>(values[i])->print(indentationLevel + 2);
        } else {
            std::cout << values[i]->toString();
        }
        if (i != values.size() - 1) {
            std::cout << ",";
        }
        std::cout << "\n";
    }
    std::cout << MyString(' ', indentationLevel) << "]";
}