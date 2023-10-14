#include <iostream>
using namespace std;

template<typename T>
class Grid final
{
public:
    using value_type = T;
    using size_type = unsigned;
private:
    T* data;
    size_type y_size, x_size;

    class Proxy
    {
    private:
        T* row;
        size_type x_size;
    public:
        Proxy(T* row, size_type x_size) : row(row), x_size(x_size) {}

        T& operator[](size_type x_idx)
        {
            return row[x_idx];
        }
    };

public:
    Grid() : data(nullptr), y_size(0), x_size(0) {}

    Grid(size_type y_size, size_type x_size)
        : data(new T[y_size * x_size]), y_size(y_size), x_size(x_size)
    {
        for (size_type i = 0; i < y_size * x_size; ++i)
            data[i] = T();
    }

    Grid(size_type y_size, size_type x_size, T const& t)
        : data(new T[y_size * x_size]), y_size(y_size), x_size(x_size)
    {
        for (size_type i = 0; i < y_size * x_size; ++i)
            data[i] = t;
    }

    Grid(T const& t) : data(new T[1]), y_size(1), x_size(1)
    {
        data[0] = t;
    }

    Grid(Grid const& other) : data(new T[other.y_size * other.x_size]), y_size(other.y_size), x_size(other.x_size)
    {
        std::copy(other.data, other.data + other.y_size * other.x_size, data);
    }

    Grid(Grid&& other) : data(nullptr), y_size(0), x_size(0)
    {
        swap(other);
    }

    Grid& operator=(Grid const& other)
    {
        if (this != &other)
        {
            Grid tmp(other);
            swap(tmp);
        }
        return *this;
    }

    Grid& operator=(Grid&& other)
    {
        if (this != &other)
        {
            swap(other);
            other.clear();
        }
        return *this;
    }

    ~Grid()
    {
        clear();
    }

    void swap(Grid& other)
    {
        std::swap(data, other.data);
        std::swap(y_size, other.y_size);
        std::swap(x_size, other.x_size);
    }

    void clear()
    {
        delete[] data;
        data = nullptr;
        y_size = 0;
        x_size = 0;
    }

    T operator()(size_type y_idx, size_type x_idx) const
    {
        return data[y_idx * x_size + x_idx];
    }

    T& operator()(size_type y_idx, size_type x_idx)
    {
        return data[y_idx * x_size + x_idx];
    }

    Grid<T>& operator=(T const& t)
    {
        for (auto it = data, end = data + x_size * y_size; it != end; ++it)
            *it = t;
        return *this;
    }

    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }

    Proxy operator[](size_type y_idx)
    {
        return Proxy(data + y_idx * x_size, x_size);
    }
};

#include<cassert>

int main()
{
    Grid<float> g(3, 2, 0.0f);
    assert(3 == g.get_y_size());
    assert(2 == g.get_x_size());

    using gsize_t = Grid<int>::size_type;

    for(gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
    for(gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
        assert(0.0f == g[y_idx][x_idx]);

    for(gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
    for(gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
        g[y_idx][x_idx] = 1.0f;

    for(gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
    for(gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
        assert(1.0f == g(y_idx , x_idx));
    return 0;
}
