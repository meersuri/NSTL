#ifndef LIST_NODE_H_
#define LIST_NODE_H_

#include <memory>

namespace nstl {

template <typename T>
class list_node {
    public:
        list_node<T>() = default;
        list_node<T>(T data): data_(data) {}
        list_node<T>(T data, std::shared_ptr<list_node<T>> next, std::shared_ptr<list_node<T>> prev): data_(data), next_(next), prev_(prev) {}
        list_node<T>(const list_node& other) = default;
        list_node<T>(list_node<T>&& other) = default;
        list_node<T>& operator=(const list_node<T>& other) = default;
        list_node<T>& operator=(list_node<T>&& other) = default;
        const T& data() const { return data_; }
        T& data() { return data_; }
        const std::shared_ptr<list_node<T>> next() { return next_; }
        const std::shared_ptr<list_node<T>> prev() { return prev_; }
        void next(std::shared_ptr<list_node<T>> node) { next_ = node; }
        void prev(std::shared_ptr<list_node<T>> node) { prev_ = node; }
    private:
        T data_;
        std::shared_ptr<list_node<T>> next_;
        std::shared_ptr<list_node<T>> prev_;
};

}// namespace nstl

#endif


