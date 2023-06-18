#pragma once
#include <iostream>

enum class JsonValueType {
    OBJECT,
    ARRAY,
    STRING,
    NUMBER,
    BOOL,
    NULLVAL
};

std::ostream &operator<<(std::ostream &os, const JsonValueType &type);