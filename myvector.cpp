#include <stdexcept>
#include <sstream>

#include "myvector.hpp"

template<typename T>
MyVector<T>::MyVector(size_t n, const T &item): _size(n), _capacity(n), _data(nullptr) {
    _data = std::make_unique<T[]>(n);
    for (int i = 0; i < n; ++i) {
        _data[i] = item;
    }
}

template<typename T>
void MyVector<T>::append(const T &item) {
    if (_size < _capacity) {
        _data[_size++] = item;
        return;
    }
    _capacity *= 2;
    auto _new_data = std::make_unique<T[]>(_capacity);
    std::copy(_data.get(), _data.get() + _size, _new_data.get());
    _data.reset();
    _data = std::move(_new_data);
    _data[_size++] = item;
}
        
template<typename T>
T &MyVector<T>::operator[](size_t idx) {
    if (idx > _size) {
        std::stringstream ss;
        ss << "idx: " << std::to_string(idx) << " is out of range for size of " 
            << std::to_string(_size);
        throw std::out_of_range(ss.str());
    }
    return _data[idx];
}

int main() {
    MyVector<int> vec;
    vec.append(1);
    std::cout << vec.size() << std::endl;
    std::cout << vec[0] << std::endl;
    vec.append(2);
    std::cout << vec[1] << std::endl;
    vec.append(3);
    std::cout << vec[2] << std::endl;
    return 0;
}

