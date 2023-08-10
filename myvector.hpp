#include <iostream>
#include <string>
#include <memory>

template<typename T>
class MyVector {
    size_t _size;
    size_t _capacity;
    std::unique_ptr<T[]> _data;
    public:
        MyVector<T>(): _size(0), _capacity(1),  _data(nullptr) { _data = std::make_unique<T[]>(1); }
        MyVector<T>(size_t n): _size(n), _capacity(n), _data(nullptr) { _data = std::make_unique<T[]>(n); }
        MyVector<T>(size_t n, const T &item);
        void append(const T &item);
        size_t size() { return _size; }
        T &operator[](size_t idx);
};
    
