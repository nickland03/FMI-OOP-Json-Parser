#include "JsonParser.h"

JsonParser::JsonParser(const MyString &jsonFileName) {
    std::ifstream in(jsonFileName.c_str());
    if (!in.is_open()) {
        auto errorMsg = MyString("could not open ") + jsonFileName;
        throw std::runtime_error(errorMsg.c_str());
    }

    unsigned fileSize = getFileSize(in);
    char buffer[fileSize + 1];
    in.read(buffer, fileSize);
    in.close();
    buffer[fileSize] = '\0';

    auto minifedJson = minify(MyString(buffer));
    json = parseObject(new JsonObject(), minifedJson);
}

JsonParser::JsonParser(const char *jsonFileName) : JsonParser(MyString(jsonFileName)) {}

JsonParser::~JsonParser() {
    free();
}

unsigned JsonParser::getFileSize(std::ifstream &in) {
    in.seekg(0, std::ios::end);
    unsigned fileSize = in.tellg();
    in.seekg(0, std::ios::beg);
    return fileSize;
}

MyString JsonParser::minify(const MyString &jsonString) {
    MyString result;
    bool inString = false;
    for (unsigned i = 0; i < jsonString.length(); i++) {
        char c = jsonString[i];
        if (c == '"') {
            inString = !inString;
        }
        if (!inString && (c == ' ' || c == '\n' || c == '\r' || c == '\t')) {
            continue;
        }
        result += c;
    }
    return result;
}

JsonValueType JsonParser::getValueType(const MyString &value) {
    std::stringstream ss(value.c_str());
    char ch;
    if (ss >> ch && ch == '{') {
        return JsonValueType::OBJECT;
    } else if (ss.clear(), ss.str(value.c_str()), ss >> ch && ch == '[') {
        return JsonValueType::ARRAY;
    } else if (value == "null") {
        return JsonValueType::NULLVAL;
    } else if (value == "true" || value == "false") {
        return JsonValueType::BOOL;
    } else {
        double number;
        if (ss.clear(), ss.str(value.c_str()), ss >> number) {
            return JsonValueType::NUMBER;
        } else {
            return JsonValueType::STRING;
        }
    }
}

JsonBoolean *JsonParser::boolStringToJsonBoolean(const MyString &boolString) {
    if (boolString == "true") return new JsonBoolean(true);
    return new JsonBoolean(false);
}

JsonArray *JsonParser::parseArray(const MyString &arrayString) {
    auto arr = new JsonArray();
    auto parts = split(arrayString);

    for (unsigned i = 0; i < parts.size(); i++) {
        switch (getValueType(parts[i])) {
            case JsonValueType::OBJECT: {
                auto obj = new JsonObject();
                bool isObjectEmpty = parts[i] == globalConstants::EMPTY_OBJECT;
                if (!isObjectEmpty) {
                    obj = parseObject(obj, parts[i]);
                }
                arr->addValue(obj);
                break;
            }
            case JsonValueType::ARRAY: {
                auto innerArr = parseArray(parts[i]);
                arr->addValue(innerArr);
                break;
            }
            case JsonValueType::STRING: {
                MyString value = unwrap(parts[i], '"');
                arr->addValue(new JsonString(value));
                break;
            }
            case JsonValueType::NUMBER: {
                arr->addValue(new JsonNumber(parts[i]));
                break;
            }
            case JsonValueType::BOOL: {
                arr->addValue(new JsonBoolean(boolStringToJsonBoolean(parts[i])));
                break;
            }
            case JsonValueType::NULLVAL: {
                arr->addValue(new JsonNull());
                break;
            }
        }
    }
    return arr;
}

JsonObject *JsonParser::parseObject(JsonObject *root, const MyString &jsonString) {
    Vector<MyString> kvs = split(jsonString);

    for (unsigned i = 0; i < kvs.size(); i++) {
        auto kv = extractKeyValue(kvs[i]);
        MyString key = unwrap(kv.key, '"');
        auto type = getValueType(kv.value);
        switch (type) {
            case JsonValueType::OBJECT: {
                auto obj = new JsonObject();
                bool isObjectEmpty = kv.value == globalConstants::EMPTY_OBJECT;
                if (!isObjectEmpty) {
                    obj = parseObject(obj, kv.value);
                }
                root->addValue(key, obj, root);
                break;
            }
            case JsonValueType::ARRAY: {
                auto arr = parseArray(kv.value);
                root->addValue(key, arr, root);
                break;
            }
            case JsonValueType::STRING: {
                MyString value = unwrap(kv.value, '"');
                root->addValue(key, new JsonString(value), root);
                break;
            }
            case JsonValueType::NUMBER: {
                root->addValue(key, new JsonNumber(kv.value), root);
                break;
            }
            case JsonValueType::BOOL: {
                root->addValue(key, boolStringToJsonBoolean(kv.value), root);
                break;
            }
            case JsonValueType::NULLVAL: {
                root->addValue(key, new JsonNull(), root);
                break;
            }
        }
    }

    return root;
}

MyString JsonParser::unwrap(const MyString &value, char symbol) {
    if (value.front() != symbol && value.back() != symbol) {
        return value;
    }

    std::stringstream ss(value.c_str());
    MyString result;

    while (ss.peek() == symbol) {
        ss.ignore();
    }

    char c;
    while (ss.get(c) && c != symbol) {
        result += c;
    }

    while (!result.empty() && result.back() == symbol) {
        result.pop_back();
    }

    return result;
}


Vector<MyString> JsonParser::split(const MyString &s) {
    MyString innerString(s.substr(1, s.length() - 2).c_str());
    Vector<MyString> result;
    MyString current;

    int bracesCount = 0;
    for (unsigned i = 0; i < innerString.length(); i++) {
        if (innerString[i] == '{' || innerString[i] == '[') {
            bracesCount++;
        } else if (innerString[i] == '}' || innerString[i] == ']') {
            bracesCount--;
        }

        if (innerString[i] == ',' && bracesCount == 0) {
            result.push_back(current);
            current = MyString("");
        } else {
            current += innerString[i];
        }
    }

    result.push_back(current);
    return result;
}

JsonParser::KV JsonParser::extractKeyValue(const MyString &str) {
    KV kv;
    std::stringstream ss(str.c_str());

    char kvBuffer[1024];
    ss.getline(kvBuffer, 1024, ':');
    kv.key = MyString(kvBuffer);

    char valueBuffer[1024];
    ss >> std::ws;
    ss.getline(valueBuffer, 1024);
    kv.value = MyString(valueBuffer);
    return kv;
}

void JsonParser::free() {
    delete json;
}

void JsonParser::print() const {
    if (!json) return;
    json->print(0);
    std::cout << std::endl;
}

Vector<JsonObject::JsonPair *> JsonParser::searchArray(const MyString &key, const JsonArray *arr) {
    Vector<JsonObject::JsonPair *> result;
    if (!arr) return result;

    for (size_t i = 0; i < arr->getValues().size(); i++) {
        auto v = arr->getValues()[i];
        if (v->getType() == JsonValueType::OBJECT) {
            auto sub = searchObject(key, static_cast<JsonObject *>(v));
            for (size_t j = 0; j < sub.size(); j++) {
                result.push_back(sub[j]);
            }
        } else if (v->getType() == JsonValueType::ARRAY) {
            auto sub = searchArray(key, static_cast<JsonArray *>(v));
            for (size_t j = 0; j < sub.size(); j++) {
                result.push_back(sub[j]);
            }
        }
    }

    return result;
}

Vector<JsonObject::JsonPair *> JsonParser::searchObject(const MyString &key, const JsonObject *obj) {
    Vector<JsonObject::JsonPair *> result;
    if (!obj) return result;

    for (unsigned i = 0; i < obj->getValues().size(); i++) {
        if (obj->getValues()[i]->key == key) {
            result.push_back(obj->getValues()[i]);
        }
        if (obj->getValues()[i]->value->getType() == JsonValueType::OBJECT) {
            auto sub = searchObject(key, static_cast<JsonObject *>(obj->getValues()[i]->value));
            for (size_t j = 0; j < sub.size(); j++) {
                result.push_back(sub[j]);
            }
        } else if (obj->getValues()[i]->value->getType() == JsonValueType::ARRAY) {
            auto sub = searchArray(key, static_cast<JsonArray *>(obj->getValues()[i]->value));
            for (size_t j = 0; j < sub.size(); j++) {
                result.push_back(sub[j]);
            }
        }
    }

    return result;
}

void JsonParser::list(const MyString &key) const {
    auto values = searchObject(key, json);
    auto errorMessage = key + MyString(": ") + MyString(globalConstants::INVALID_JSON_KEY);
    if (values.empty()) throw std::runtime_error(errorMessage.c_str());

    for (int i = 0; i < values.size(); i++) {
        std::cout << values[i]->value->toString() << std::endl;
    }
}

void JsonParser::list(const char *key) const {
    list(MyString(key));
}

void JsonParser::remove(const MyString &path) {
    Vector<MyString> keys = path.split(globalConstants::FORWARD_SLASH);

    if (keys.empty())
        return;

    JsonObject *currentObj = json;
    for (size_t i = 0; i < keys.size() - 1; i++) {
        const MyString &key = keys[i];
        auto pairs = searchObject(key, currentObj);

        if (pairs.empty() || pairs[0]->value->getType() != JsonValueType::OBJECT)
            return;

        currentObj = static_cast<JsonObject *>(pairs[0]->value);
    }

    const MyString &lastKey = keys.back();
    if (currentObj->containsKey(lastKey))
        currentObj->removeByKey(lastKey);
}

void JsonParser::remove(const char *path) {
    remove(MyString(path));
}