#include "JsonValueType.h"

std::ostream &operator<<(std::ostream &os, const JsonValueType &type) {
    switch (type) {
        case JsonValueType::OBJECT:
            os << "object";
            break;
        case JsonValueType::ARRAY:
            os << "array";
            break;
        case JsonValueType::STRING:
            os << "string";
            break;
        case JsonValueType::NUMBER:
            os << "number";
            break;
        case JsonValueType::BOOL:
            os << "boolean";
            break;
        case JsonValueType::NULLVAL:
            os << "null";
            break;
    }
    return os;
}