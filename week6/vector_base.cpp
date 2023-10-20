#include <iostream>
#include <string>
using namespace std;

template <typename T>
T *safe_copy(const T *src, size_t srcsize, size_t dstsize) {
    T *dst = new T[dstsize];
    try {
        for (size_t i = 0; i < srcsize; ++i) {
            dst[i] = src[i];
        }
    } catch (...) {
        delete[] dst;
        throw;
    }
    return dst;
}

template <typename T>
class MyVector {
    T *arr_ = nullptr;
    size_t size_ = 0, used_ = 0;

public:
    explicit MyVector(size_t sz = 0) : arr_(new T[sz]), size_(sz) {}

    MyVector(const MyVector &rhs)
        : arr_(safe_copy(rhs.arr_, rhs.used_, rhs.size_)),
          size_(rhs.size_), used_(rhs.used_) {}

    MyVector(MyVector &&rhs) noexcept
        : arr_(rhs.arr_), size_(rhs.size_), used_(rhs.used_) {
        rhs.arr_ = nullptr;
        rhs.size_ = 0;
        rhs.used_ = 0;
    }

    MyVector &operator=(MyVector &&rhs) noexcept {
        swap(arr_, rhs.arr_);
        swap(size_, rhs.size_);
        swap(used_, rhs.used_);
        return *this;
    }

    MyVector &operator=(const MyVector &rhs) {
        if (this != &rhs) {
            T *tmp = safe_copy(rhs.arr_, rhs.used_, rhs.size_);
            delete[] arr_;
            arr_ = tmp;
            size_ = rhs.size_;
            used_ = rhs.used_;
        }
        return *this;
    }

    ~MyVector() { delete[] arr_; }

    void pop() {
        if (used_ < 1)
            throw runtime_error("Vector is empty");
        used_ -= 1;
    }

    T &top() {
        if (used_ < 1)
            throw runtime_error("Vector is empty");
        return arr_[used_ - 1];
    }

    void push(const T &t) {
        if (used_ == size_) {
            size_t newsz = size_ * 2 + 1;
            T *newarr = safe_copy(arr_, used_, newsz);
            delete[] arr_;
            arr_ = newarr;
            size_ = newsz;
        }
        arr_[used_] = t;
        ++used_;
    }

    T &at(size_t idx) {
        if (idx >= used_)
            throw out_of_range("Index is out of range");
        return arr_[idx];
    }

    T &operator[](size_t idx) { return arr_[idx]; }

    size_t size() const { return used_; }

    size_t capacity() const { return size_; }
};

// Проверка

struct Controllable {
    static int control;
    int *resource_;
    Controllable() : resource_(new int(42)) {}

    Controllable(Controllable &&rhs) noexcept : resource_(rhs.resource_) {
        rhs.resource_ = nullptr;
    }
    Controllable &operator=(Controllable &&rhs) noexcept {
        swap(resource_, rhs.resource_);
        return *this;
    }
    Controllable(const Controllable &rhs) : resource_(new int(*rhs.resource_)) {
        if (control == 0) {
            control = 5;
            cout << "Control reached\n";
            throw bad_alloc{};
        }
        control -= 1;
    }
    Controllable &operator=(const Controllable &rhs) {
        Controllable tmp(rhs);
        swap(*this, tmp);
        return *this;
    }

    ~Controllable() { delete resource_; }
};

int Controllable::control = 0;

int main() {
    try {
        MyVector<Controllable> v(1);
        v.push(Controllable{});
        v.push(Controllable{});
    } catch (const exception &e) {
        cerr << e.what() << '\n';
    }
    return 0;
}