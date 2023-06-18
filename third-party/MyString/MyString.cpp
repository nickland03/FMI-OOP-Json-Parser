#include "MyString.h"

MyString::MyString(size_t capacity) {
    _length = capacity - 1;
    _data = new char[capacity];
}

MyString::MyString() : MyString(1) {
    _data[0] = '\0';
}

MyString::MyString(const char *data) : MyString(strlen(data) + 1) {
    strcpy(_data, data);
}

MyString::MyString(char c, size_t count) : MyString(count + 1) {
    for (unsigned i = 0; i < length(); i++) {
        _data[i] = c;
    }
    _data[count] = '\0';
}

MyString::MyString(const MyString &other) {
    copyFrom(other);
}

MyString::MyString(MyString &&other) noexcept {
    moveFrom(std::move(other));
}

MyString &MyString::operator=(const MyString &other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

MyString &MyString::operator=(MyString &&other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

MyString::~MyString() {
    free();
}

void MyString::free() {
    delete[] _data;
    _data = nullptr;
}

void MyString::copyFrom(const MyString &other) {
    _length = other._length;
    _data = new char[_length + 1];
    strcpy(_data, other._data);
}

void MyString::moveFrom(MyString &&data) {
    this->_length = data._length;
    this->_data = data._data;
    data._data = nullptr;
}

size_t MyString::length() const {
    return _length;
}

MyString MyString::substr(size_t pos, size_t len) const {
    if (pos > _length) {
        throw std::out_of_range("pos is out of range");
    }
    const size_t new_len = std::min(len, _length - pos);
    MyString result(new_len + 1);
    std::memcpy(result._data, _data + pos, new_len);
    result._data[new_len] = '\0';
    return result;
}

Vector<MyString> MyString::split(char splitBy) const {
    Vector<MyString> v;
    unsigned startPos = 0;
    unsigned endPos = 0;
    unsigned length = this->length();

    while (endPos < length) {
        if (_data[endPos] == splitBy) {
            v.push_back(substr(startPos, endPos - startPos));
            startPos = endPos + 1;
        }
        endPos++;
    }

    if (startPos < length) {
        v.push_back(substr(startPos, endPos - startPos));
    }

    return v;
}

char &MyString::operator[](size_t index) {
    return _data[index];
}

char MyString::operator[](size_t index) const {
    return _data[index];
}

const char *MyString::MyString::c_str() const {
    return _data;
}

char &MyString::front() {
    return _data[0];
}

const char &MyString::front() const {
    return _data[0];
}

char &MyString::back() {
    return _data[_length - 1];
}

const char &MyString::back() const {
    return _data[_length - 1];
}

bool MyString::empty() const {
    return _length == 0;
}

void MyString::pop_back() {
    if (_length > 0) {
        _length--;
        _data[_length] = '\0';
    }
}

MyString &MyString::operator+=(char c) {
    char *new_data = new char[_length + 2];
    strcpy(new_data, _data);
    new_data[_length] = c;
    new_data[_length + 1] = '\0';
    delete[] _data;
    _data = new_data;
    ++_length;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const MyString &str) {
    return os << str.c_str();
}

std::istream &operator>>(std::istream &is, MyString &str) {
    char buff[1024];
    is >> buff;

    delete[] str._data;
    str._length = strlen(buff);
    str._data = new char[str._length + 1];
    strcpy(str._data, buff);
    return is;
}

MyString operator+(const MyString &lhs, const MyString &rhs) {
    MyString result(lhs._length + rhs._length + 1);

    result[0] = '\0';
    strcat(result._data, lhs._data);
    strcat(result._data, rhs._data);

    return result;
}

MyString &MyString::operator+=(const MyString &other) {
    char *result = new char[(_length += other._length) + 1];
    result[0] = '\0';
    strcat(result, _data);
    strcat(result, other._data);

    delete[] _data;
    _data = result;

    return *this;
}

bool operator<(const MyString &lhs, const MyString &rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const MyString &lhs, const MyString &rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>=(const MyString &lhs, const MyString &rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

bool operator>(const MyString &lhs, const MyString &rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator==(const MyString &lhs, const MyString &rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator==(const MyString &lhs, const char *rhs) {
    return strcmp(lhs.c_str(), rhs) == 0;
}

bool operator!=(const MyString &lhs, const MyString &rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}