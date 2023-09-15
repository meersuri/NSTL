#ifndef SPTR_H_
#define SPTR_H_

namespace nstd {

template <typename T>
class sptr {
    public:
        sptr(): raw_ptr_(nullptr), ref_count_(nullptr) {}
        explicit sptr(T* ptr);
        sptr(const sptr& other);
        sptr& operator=(const sptr& other);
        sptr(sptr&& other) noexcept;
        sptr& operator=(sptr<T>&& other);
        bool operator==(const sptr& other) const;
        bool operator==(std::nullptr_t) const { return raw_ptr_ == nullptr && ref_count_ == nullptr;}
        T& operator*();
        T* operator->();
        ~sptr();
        int ref_count() const;
        T* get() { return raw_ptr_; }
        const T* get() const { return raw_ptr_; }
    private:
        T* raw_ptr_;
        int* ref_count_;
        void decref();
};

template <typename T>
int sptr<T>::ref_count() const {
    if (ref_count_ == nullptr) {
        return 0;
    }
    return *ref_count_;
}


template <typename T>
inline bool sptr<T>::operator==(const sptr& other) const {
    return (raw_ptr_ == other.get() && ref_count() == other.ref_count());
}

template <typename T>
inline void sptr<T>::decref() {
    if (ref_count_ != nullptr && *ref_count_ > 0) {
        (*ref_count_)--;
        if (*ref_count_ == 0 && raw_ptr_ != nullptr) {
            if constexpr (std::is_array_v<T>) {
                delete[] raw_ptr_;
            }
            else {
                delete raw_ptr_;
            }
            raw_ptr_ = nullptr;
        }
    }
}

template <typename T>
sptr<T>& sptr<T>::operator=(const sptr& other) {
    if (&other != this) {
        decref();
        raw_ptr_ = other.raw_ptr_;
        ref_count_ = other.ref_count_;
        if (ref_count_ != nullptr) {
            (*ref_count_)++;
        }
    }
    return *this;
}

template <typename T>
sptr<T>::sptr(const sptr& other): raw_ptr_(nullptr), ref_count_(nullptr) {
    *this = other;
}

template <typename T>
inline sptr<T>::sptr(T* p): raw_ptr_(p), ref_count_(nullptr) {
    if (p != nullptr) {
        ref_count_ = new int{1};
    }
}

template <typename T>
sptr<T>& sptr<T>::operator=(sptr&& other){
    if (&other != this) {
        decref();
        raw_ptr_ = other.raw_ptr_;
        ref_count_ = other.ref_count_;
        other.raw_ptr_ = nullptr;
        other.ref_count_ = nullptr;
    }
    return *this;
}

template <typename T>
sptr<T>::sptr(sptr&& other) noexcept: raw_ptr_(nullptr), ref_count_(nullptr){
    *this = std::move(other);
}

template <typename T>
T& sptr<T>::operator*() {
    return *raw_ptr_;
}

template <typename T>
T* sptr<T>::operator->() {
    return raw_ptr_;
}

template <typename T>
sptr<T>::~sptr() {
    if (raw_ptr_ == nullptr) {
        return;
    }
    decref();
}

template <typename T, typename... Args>
sptr<T> make_sptr(Args&&... args) {
    static_assert(!std::is_array_v<T>, "T[] not supported");
    T* raw_ptr = new T(std::forward<Args>(args)...);
    return sptr<T>(raw_ptr);
}

} // namespace nstd

#endif
