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
        uptr(uptr<T>&& other) noexcept;
        uptr<T>& operator=(uptr<T>&& other) noexcept;
        bool operator==(std::nullptr_t p) const { return raw_ptr_ == p; }
        ~uptr();
        T& operator*() { return *raw_ptr_; }
        T& operator[](size_t idx) { return raw_ptr_[idx]; }
        const T& operator[](size_t idx) const { return raw_ptr_[idx]; }
        T* operator->() { return raw_ptr_; }
        T* get() { return raw_ptr_; }
        const T* get() const { return raw_ptr_; }
        void reset();
    private:
        T* raw_ptr_;
        bool is_array_{false};
        void free();
};

template <typename T>
uptr<T>::uptr(uptr<T>&& other) noexcept {
    raw_ptr_ = other.raw_ptr_;
    other.raw_ptr_ = nullptr;
}

template <typename T>
uptr<T>& uptr<T>::operator=(uptr<T>&& other) noexcept {
    if (this != &other) {
        raw_ptr_ = other.raw_ptr_;
        other.raw_ptr_ = nullptr;
    }
    return *this;
}

template <typename T>
uptr<T>::~uptr() {
    free();
}

template <typename T>
void uptr<T>::reset() {
    free();
}

template <typename T>
inline void uptr<T>::free() {
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
uptr<T> make_uptr(Args&&... args) {
    static_assert(!std::is_array_v<T>, "T[] only supported with a single arg for size");
    T* raw_ptr = new T(std::forward<Args>(args)...);
    ensure_alloc(raw_ptr);
    return uptr<T>(raw_ptr);
}

template <typename T>
auto make_uptr(size_t N) {
    if constexpr(!std::is_array_v<T>) {
        return uptr<T>(new T(std::forward<int>(N)));
    }
    auto raw_ptr = new std::remove_extent_t<T>[N];
    ensure_alloc(raw_ptr);
    return uptr<std::remove_extent_t<T>>(raw_ptr, true);
}

template <typename T>
auto make_uptr(int N) {
    if constexpr(!std::is_array_v<T>) {
        return uptr<T>(new T(std::forward<int>(N)));
    }
    if (N < 0) {
        throw std::bad_array_new_length();
    }
    auto raw_ptr = new std::remove_extent_t<T>[N];
    ensure_alloc(raw_ptr);
    return uptr<std::remove_extent_t<T>>(raw_ptr, true);
}

} // namespace nstd

#endif 
