#include <iostream>
#include <string>
#include <sstream>

#include "uptr.h"

#ifndef INCLUDE_VECTOR_H
#define INCLUDE_VECTOR_H

namespace nstd {

template<typename T>
class vector {
    size_t _size;
    size_t _capacity;
    nstd::uptr<T> _data;
    public:
        vector<T>(): _size(0), _capacity(1),  _data(nullptr) { _data = nstd::make_uptr<T[]>(1); }
        vector<T>(size_t n): _size(n), _capacity(n), _data(nullptr) { _data = nstd::make_uptr<T[]>(n); }
        vector<T>(size_t n, const T &item);
        vector<T>(const vector<T> &other);
        vector<T>(vector<T> &&other) noexcept;
        void append(const T &item);
        size_t size() const { return _size; }
        size_t capacity() const { return _capacity; }
        T &operator[](int idx);
        const T &operator[](int idx) const;
};

template<typename T>
nstd::vector<T>::vector(size_t n, const T &item): _size(n), _capacity(n), _data(nullptr) {
    _data = nstd::make_uptr<T[]>(n);
    for (int i = 0; i < n; ++i) {
        _data[i] = item;
    }
}

template<typename T>
void nstd::vector<T>::append(const T &item) {
    if (_size < _capacity) {
        _data[_size++] = item;
        return;
    }
    _capacity *= 2;
    auto _new_data = nstd::make_uptr<T[]>(_capacity);
    std::copy(_data.get(), _data.get() + _size, _new_data.get());
    _data.reset();
    _data = std::move(_new_data);
    _data[_size++] = item;
}
        
template<typename T>
T& nstd::vector<T>::operator[](int idx) {
    if (idx > _size || idx < 0) {
        std::stringstream ss;
        ss << "idx: " << std::to_string(idx) << " is out of range for size of "
            << std::to_string(_size);
        throw std::out_of_range(ss.str());
    }
    return _data[idx];
}

template<typename T>
const T& nstd::vector<T>::operator[](int idx) const {
    if (idx > _size || idx < 0) {
        std::stringstream ss;
        ss << "idx: " << std::to_string(idx) << " is out of range for size of "
            << std::to_string(_size);
        throw std::out_of_range(ss.str());
    }
    return _data[idx];
}

template<typename T>
nstd::vector<T>::vector(const vector<T> &other): _size(other._size), _capacity(other._capacity), _data(nullptr) {
    _data = nstd::make_uptr<T[]>(_capacity);
    std::copy(other._data.get(), other._data.get() + other._capacity, _data.get());
}

template<typename T>
nstd::vector<T>::vector(vector<T> &&other) noexcept: _size(other._size), _capacity(other._capacity), _data(nullptr) {
    _data = std::move(other._data);
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
}

template<typename T>
std::ostream& operator<<(std::ostream &os, const nstd::vector<T> &v) {
    std::cout << '[';
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i < v.size() - 1)
            std::cout << ",";
    }
    std::cout << "]\n";
    return os;
}

} // namespace nstd

#endif
