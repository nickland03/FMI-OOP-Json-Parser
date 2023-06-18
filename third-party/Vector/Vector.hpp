#pragma once

#include <iostream>

template<typename T>
class Vector {
private:
    T *_data;
    size_t _capacity{};
    size_t _size{};

    void copyFrom(const Vector &other) {
        _data = new T[other._capacity];
        _capacity = other._capacity;
        _size = other._size;
        for (size_t i = 0; i < _size; i++) {
            _data[i] = other._data[i];
        }
    }

    void moveFrom(Vector &&other) {
        _data = other._data;
        _capacity = other._capacity;
        _size = other._size;
        other._data = nullptr;
        other._capacity = 0;
        other._size = 0;
    }

    void free() {
        delete[] _data;
    }

public:
    Vector() : _data(nullptr), _capacity(0), _size(0) {}

    explicit Vector(size_t init_size) : _data(new T[init_size]), _capacity(init_size), _size(init_size) {}

    Vector(const Vector &other) {
        copyFrom(other);
    }

    Vector(Vector &&other) noexcept {
        moveFrom(std::move(other));
    }

    Vector &operator=(const Vector &other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }

    Vector &operator=(Vector &&other) noexcept {
        if (this != &other) {
            free();
            moveFrom(std::move(other));
        }
        return *this;
    }

    ~Vector() {
        free();
    }

    T &operator[](size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }

    T &operator[](size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }

    void push_back(T &&value) {
        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : 2 * _capacity);
        }
        _data[_size++] = std::move(value);
    }

    void push_back(const T &value) {
        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : 2 * _capacity);
        }
        _data[_size++] = value;
    }

    void pop_back() {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        _size--;
    }

    void clear() {
        _size = 0;
    }

    size_t size() const {
        return _size;
    }

    size_t capacity() const {
        return _capacity;
    }

    bool empty() const {
        return _size == 0;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > _capacity) {
            T *new_data = new T[new_capacity];
            for (size_t i = 0; i < _size; i++) {
                new_data[i] = _data[i];
            }
            delete[] _data;
            _data = new_data;
            _capacity = new_capacity;
        }
    }

    T &front() {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return _data[0];
    }

    const T &front() const {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return _data[0];
    }

    T &back() {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return _data[_size - 1];
    }

    const T &back() const {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return _data[_size - 1];
    }
};