#ifndef LIST_H
#define LIST_H

#include "node.h"

namespace nstd{

template <typename T>
class list {
    public:
        list<T>(): size_(0), head_(new list_node<T>()), tail_(new list_node<T>()) { head_->next(tail_); tail_->prev(head_); }
        list<T>(const list<T>& other) = default;
        list<T>(list<T>&& other) = default;
        list<T>& operator=(const list<T>& other) = default;
        list<T>& operator=(list<T>&& other) = default;
        ~list<T>();
        void append(const T& data);
        T& pop();
        T& pop_left();
        size_t size() { return size_;}
        const T& front() const { return get_front(); }
        T& front() { return get_front(); }
        const T& back() const { return get_back(); }
        T& back() { return get_back(); }
    private:
        size_t calc_size();
        T& get_front();
        T& get_back();
        size_t size_;
        list_node<T>* head_;
        list_node<T>* tail_;
};

template <typename T>
list<T>::~list<T>() {
    auto curr = tail_;
    while (curr->prev()) {
        auto prev = curr->prev();
        if (curr != nullptr)
            delete curr;
        curr = prev;
    }
    if (head_ != nullptr)
        delete head_;
}

template <typename T>
size_t list<T>::calc_size() {
    auto curr = head_;
    size_t count = 0;
    while (curr->next() != tail_) {
        count++;
        curr = curr->next();
    }
    return count;
}

template <typename T>
inline T& list<T>::get_front() {
    if (size_ == 0)
        throw std::runtime_error("front() called on an empty list");
    return head_->next()->data();
}

template <typename T>
inline T& list<T>::get_back() {
    if (size_ == 0)
        throw std::runtime_error("back() called on an empty list");
    return tail_->prev()->data();
}

template <typename T>
void list<T>::append(const T& data) {
    auto node = new nstd::list_node<T>(data);
    auto last = tail_->prev();
    last->next(node);
    node->prev(last);
    node->next(tail_);
    tail_->prev(node);
    size_++;
}

template <typename T>
T& list<T>::pop() {
    if (head_->next() == tail_)
        throw std::runtime_error("Pop from empty list");
    if (head_->next()->next() == tail_) {
        auto node = head_->next();
        head_->next(tail_);
        tail_->prev(head_);
        size_--;
        return node->data();
    }
    auto last = tail_->prev();
    auto second_last = last->prev();
    second_last->next(tail_);
    tail_->prev(second_last);
    size_--;
    return last->data();
}

template <typename T>
T& list<T>::pop_left() {
    if (head_->next() == tail_)
        throw std::runtime_error("Pop from empty list");
    if (head_->next()->next() == tail_) {
        auto node = head_->next();
        head_->next(tail_);
        tail_->prev(head_);
        size_--;
        return node->data();
    }
    auto first = head_->next();
    auto second = first->next();
    second->prev(head_);
    head_->next(second);
    size_--;
    return first->data();
}

} // namespace nstd

#endif
