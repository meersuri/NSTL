#include <iostream>
#include <string>
#include <memory>

namespace nstd {

    template<typename T>
    class vector {
        size_t _size;
        size_t _capacity;
        std::unique_ptr<T[]> _data;
        public:
            vector<T>(): _size(0), _capacity(1),  _data(nullptr) { _data = std::make_unique<T[]>(1); }
            vector<T>(size_t n): _size(n), _capacity(n), _data(nullptr) { _data = std::make_unique<T[]>(n); }
            vector<T>(size_t n, const T &item);
            void append(const T &item);
            size_t size() const { return _size; }
            size_t capacity() const { return _capacity; }
            T &operator[](size_t idx);
            const T &operator[](size_t idx) const;
            T& _index_op(size_t idx) const;
    };
}
    
