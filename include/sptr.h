#ifndef SPTR_H_
#define SPTR_H_

namespace nstd {

template <typename T>
class sptr {
    public:
        sptr(): raw_ptr_(nullptr), ref_count_(nullptr) {}
        sptr(T* ptr): raw_ptr_(ptr), ref_count_(nullptr) { ref_count_ = new int{1}; }
        sptr(const sptr& other);
        sptr& operator=(const sptr& other);
        sptr(sptr&& other) noexcept;
        sptr& operator=(sptr&& other);
        T& operator*();
        ~sptr();
        int ref_count();
    private:
        T* raw_ptr_;
        int* ref_count_;
};

template <typename T>
int sptr<T>::ref_count() {
    if (ref_count_ == nullptr) {
        return 0;
    }
    return *ref_count_;
}

template <typename T>
sptr<T>& sptr<T>::operator=(const sptr& other) {
    if (&other != this) {
        if (ref_count_ != nullptr && *ref_count_ > 0) {
            (*ref_count_)--;
        }
        if (ref_count_ != nullptr && *ref_count_ == 0 && raw_ptr_ != nullptr) {
            delete raw_ptr_;
            raw_ptr_ = nullptr;
        }
        raw_ptr_ = other.raw_ptr_;
        ref_count_ = other.ref_count_;
        (*ref_count_)++;
    }
    return *this;
}

template <typename T>
sptr<T>::sptr(const sptr& other): raw_ptr_(nullptr), ref_count_(nullptr) {
    *this = other;
}

template <typename T>
sptr<T>& sptr<T>::operator=(sptr&& other) {
    if (&other != this) {
        (*ref_count_)--;
        if (*ref_count_ == 0 && raw_ptr_ != nullptr) {
            delete raw_ptr_;
            raw_ptr_ = nullptr;
        }
        raw_ptr_ = other.raw_ptr_;
        ref_count_ = other.ref_count_;
        other.raw_ptr_ = nullptr;
        other.ref_count_ = nullptr;
    }
    return *this;
}

template <typename T>
sptr<T>::sptr(sptr&& other) noexcept {
    *this = std::move(other);
}

template <typename T>
T& sptr<T>::operator*() {
    return *raw_ptr_;
}

template <typename T>
sptr<T>::~sptr() {
    (*ref_count_)--;
    if (*ref_count_ == 0 && raw_ptr_ != nullptr) {
        delete raw_ptr_;
        raw_ptr_ = nullptr;
    }
}

template <typename T, typename... Args>
sptr<T> make_sptr(Args&&... args) {
    T* raw_ptr = new T(std::forward<Args>(args)...);
    return sptr<T>(raw_ptr);
}

} // namespace nstd

#endif
