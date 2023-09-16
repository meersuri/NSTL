#ifndef UPTR_H_
#define UPTR_H_

namespace nstd {

template <typename T>
class uptr {
    public:
        uptr(): raw_ptr_(nullptr) {}
        uptr(T* raw_ptr): raw_ptr_(raw_ptr) {}
        uptr(T* raw_ptr, bool is_array): raw_ptr_(raw_ptr), is_array_(is_array) {}
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
        bool is_array_{false};
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
        if (!is_array_) {
            delete raw_ptr_;
        }
        else {
            delete[] raw_ptr_;
        }
        raw_ptr_ = nullptr;
    }
}

template <typename T>
inline void ensure_alloc(T* raw_ptr) {
    if (raw_ptr == nullptr) {
        throw std::runtime_error("Call to new returned a nullptr");
    }
}

template <typename T, typename... Args>
auto make_uptr(Args&&... args) {
    if constexpr(!std::is_array_v<T>) {
        T* raw_ptr = new T(std::forward<Args>(args)...);
        ensure_alloc(raw_ptr);
        return uptr<T>(raw_ptr);
    }
    else {
        if (sizeof...(args) > 0) {
            auto raw_ptr = new std::remove_extent_t<T>[] {args...};
            ensure_alloc(raw_ptr);
            return uptr<std::remove_extent_t<T>>(raw_ptr, true);
        }
        else {
            auto raw_ptr = new std::remove_extent_t<T>[std::extent_v<T>];
            ensure_alloc(raw_ptr);
            return uptr<std::remove_extent_t<T>>(raw_ptr, true);
            }
    }
}


} // namespace nstd

#endif 
