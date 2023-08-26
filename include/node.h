#ifndef LIST_NODE_H_
#define LIST_NODE_H_

namespace nstd {

template <typename T>
class list_node {
    public:
        list_node<T>(): data_{}, next_(nullptr), prev_(nullptr) {}
        list_node<T>(T data): data_(data), next_(nullptr), prev_(nullptr) {}
        list_node<T>(T data, list_node<T>* next, list_node<T>* prev): data_(data), next_(next), prev_(prev) { next->prev(this); prev->next(this); }
        list_node<T>(const list_node& other) = default;
        list_node<T>(list_node<T>&& other) = default;
        list_node<T>& operator=(const list_node<T>& other) = default;
        list_node<T>& operator=(list_node<T>&& other) = default;
        const T& data() const { return data_; }
        T& data() { return data_; }
        const list_node<T>* next() { return next_; }
        const list_node<T>* prev() { return prev_; }
        void next(list_node<T>* node) { next_ = node; }
        void prev(list_node<T>* node) { prev_ = node; }
    private:
        T data_;
        list_node<T>* next_;
        list_node<T>* prev_;
};

}// namespace nstd

#endif


