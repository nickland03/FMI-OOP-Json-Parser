// Taken from Angel's GitHub and extended by 1MI0600159
#pragma once

#include <iostream>
#include "../Vector/Vector.hpp"

class MyString {
    char *_data;
    size_t _length;

    void copyFrom(const MyString &data);

    void free();

    void moveFrom(MyString &&data);

    explicit MyString(size_t capacity);

public:

    MyString();

    explicit MyString(const char *data);

    MyString(char c, size_t count);

    MyString(const MyString &other);

    MyString &operator=(const MyString &other);

    MyString(MyString &&other) noexcept;

    MyString &operator=(MyString &&other) noexcept;

    ~MyString();

    size_t length() const;

    MyString substr(size_t begin, size_t howMany) const;

    Vector<MyString> split(char splitBy) const;

    char &operator[](size_t index);

    char operator[](size_t index) const;

    const char *c_str() const;

    char &front();

    const char &front() const;

    char &back();

    const char &back() const;

    bool empty() const;

    void pop_back();

    MyString &operator+=(const MyString &other);

    MyString &operator+=(char c);

    friend MyString operator+(const MyString &lhs, const MyString &rhs);

    friend std::istream &operator>>(std::istream &is, MyString &str);
};

std::ostream &operator<<(std::ostream &os, const MyString &str);

bool operator<(const MyString &lhs, const MyString &rhs);

bool operator<=(const MyString &lhs, const MyString &rhs);

bool operator>=(const MyString &lhs, const MyString &rhs);

bool operator>(const MyString &lhs, const MyString &rhs);

bool operator==(const MyString &lhs, const MyString &rhs);

bool operator==(const MyString &lhs, const char *rhs);

bool operator!=(const MyString &lhs, const MyString &rhs);