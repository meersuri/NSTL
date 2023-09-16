#ifndef UPTR_H_
#define UPTR_H_

namespace nstd {

template <typename T>
class uptr {
    public:
        uptr(): raw_ptr_(nullptr) {}
        uptr(T* raw_ptr): raw_ptr_(raw_ptr) {} 
        uptr(const uptr<T>& other) = delete;
        uptr<T> operator=(const uptr<T>& other) = delete;
        uptr(uptr<T>&& other);
        uptr<T>& operator=(uptr<T>&& other);
        bool operator==(std::nullptr_t p) const { return raw_ptr_ == p; }
        ~uptr();
        T& operator*() { return *raw_ptr_; }
        T* operator->() { return raw_ptr_; }
        T* get() { return raw_ptr_; }
        const T* get() const { return raw_ptr_; }
    private:
        T* raw_ptr_;
};

template <typename T>
uptr<T>::uptr(uptr<T>&& other) {
    raw_ptr_ = other.raw_ptr_;
    other.raw_ptr_ = nullptr;
}

template <typename T>
uptr<T>& uptr<T>::operator=(uptr<T>&& other) {
    if (this != &other) {
        raw_ptr_ = other.raw_ptr_;
        other.raw_ptr_ = nullptr;
    }
    return *this;
}

template <typename T>
uptr<T>::~uptr() {
    if (raw_ptr_ != nullptr) {
        delete raw_ptr_;
        raw_ptr_ = nullptr;
    }
}

template <typename T, typename... Args>
uptr<T> make_uptr(Args&&... args) {
    static_assert(!std::is_array_v<T>, "T[] not supported");
    T* raw_ptr = new T(std::forward<Args>(args)...);
    if (raw_ptr == nullptr) {
        throw std::runtime_error("Failed to new in make_uptr");
    }
    return uptr<T>(raw_ptr);
}

} // namespace nstd

#endif 
