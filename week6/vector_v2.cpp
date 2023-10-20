#include <iostream>
#include <string>
using namespace std;

template <typename T>
void construct(T *p, const T &rhs) {
    new (p) T(rhs);
}

template <class T>
void destroy(T *p) noexcept {
    p->~T();
}

template <typename FwdIter>
void destroy(FwdIter first, FwdIter last) noexcept {
    while (first != last) {
        destroy(&*first);
        ++first;
    }
}

template <typename T>
struct MyVectorBuffer {
protected:
    T *arr_;
    size_t size_, used_ = 0;

protected:
    MyVectorBuffer() = default;

    MyVectorBuffer(MyVectorBuffer &&rhs) noexcept
        : arr_(rhs.arr_), size_(rhs.size_), used_(rhs.used_) {
        rhs.arr_ = nullptr;
        rhs.size_ = 0;
        rhs.used_ = 0;
    }

    MyVectorBuffer &operator=(MyVectorBuffer &&rhs) noexcept {
        swap(arr_, rhs.arr_);
        swap(size_, rhs.size_);
        swap(used_, rhs.used_);
        return *this;
    }

    explicit MyVectorBuffer(size_t sz) : arr_(new T[sz]), size_(sz) {}

    ~MyVectorBuffer() {
        destroy(arr_, arr_ + used_);
        delete[] arr_;
    }
};

template <typename T>
struct MyVector : private MyVectorBuffer<T> {
    using MyVectorBuffer<T>::arr_;
    using MyVectorBuffer<T>::size_;
    using MyVectorBuffer<T>::used_;

public:
    explicit MyVector(size_t sz = 0) : MyVectorBuffer<T>(sz) {}

    MyVector(const MyVector &rhs) : MyVectorBuffer<T>(rhs.size_) {
        try {
            for (size_t i = 0; i < rhs.used_; ++i) {
                construct(&arr_[i], rhs.arr_[i]);
            }
            used_ = rhs.used_;
        } catch (...) {
            destroy(arr_, arr_ + used_);
            delete[] arr_;
            throw;
        }
    }

    MyVector &operator=(const MyVector &rhs) {
        if (this != &rhs) {
            MyVector tmp(rhs);
            swap(*this, tmp);
        }
        return *this;
    }

    T top() const {
        if (used_ < 1)
            throw runtime_error("Vector is empty");
        return arr_[used_ - 1];
    }

    void pop() {
        if (used_ < 1)
            throw runtime_error("Vector is empty");
        destroy(&arr_[used_ - 1]);
        --used_;
    }

    void push(const T &t) {
        if (used_ == size_) {
            size_t newsz = size_ * 2 + 1;
            MyVector tmp(newsz);
            for (size_t i = 0; i < used_; ++i) {
                construct(&tmp.arr_[i], arr_[i]);
            }
            tmp.used_ = used_;
            swap(*this, tmp);
        }
        construct(&arr_[used_], t);
        ++used_;
    }

    size_t size() const { return used_; }

    size_t capacity() const { return size_; }

    ~MyVector() { destroy(arr_, arr_ + used_); }
};