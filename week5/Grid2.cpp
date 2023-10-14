#include <iostream>
using namespace std;

template<typename T, size_t N>
class Grid
{
public:
    using value_type = T;
    using size_type = size_t;

private:
    template<size_t M>
    using GridNMinusOne = Grid<T, M>;

    array<GridNMinusOne<N-1>, N> data;

public:
    Grid() = default;

    template<typename... Args>
    Grid(size_type size, Args... args)
    {
        static_assert(sizeof...(args) == N-1, "Number of arguments must match grid dimensions");
        for (size_type i = 0; i < N; ++i)
            data[i] = GridNMinusOne<N-1>(args...);
    }

    Grid(T const& t)
    {
        for (size_type i = 0; i < N; ++i)
            data[i] = GridNMinusOne<N-1>(t);
    }

    Grid(Grid const& other) = default;
    Grid(Grid&& other) = default;
    Grid& operator=(Grid const& other) = default;
    Grid& operator=(Grid&& other) = default;
    ~Grid() = default;

    GridNMinusOne<N-1>& operator[](size_type idx)
    {
        return data[idx];
    }

    GridNMinusOne<N-1> const& operator[](size_type idx) const
    {
        return data[idx];
    }

    T operator()(size_type idx) const
    {
        return data[idx / data[0].get_size()].operator()(idx % data[0].get_size());
    }

    T& operator()(size_type idx)
    {
        return data[idx / data[0].get_size()].operator()(idx % data[0].get_size());
    }

    T operator()(size_type idx, size_type... args) const
    {
        return data[idx].operator()(args...);
    }

    T& operator()(size_type idx, size_type... args)
    {
        return data[idx].operator()(args...);
    }

    size_type get_size() const
    {
        return data[0].get_size();
    }
};

template<typename T>
class Grid<T, 1>
{
public:
    using value_type = T;
    using size_type = size_t;

private:
    vector<T> data;

public:
    Grid() = default;

    template<typename... Args>
    Grid(size_type size, Args... args) : data(size, args...)
    {}

    Grid(T const& t) : data(1, t)
    {}

    Grid(Grid const& other) = default;
    Grid(Grid&& other) = default;
    Grid& operator=(Grid const& other) = default;
    Grid& operator=(Grid&& other) = default;
    ~Grid() = default;

    T operator()(size_type idx) const
    {
        return data[idx];
    }

    T& operator()(size_type idx)
    {
        return data[idx];
    }

    size_type get_size() const
    {
        return data.size();
    }
};

template<typename T>
class Grid<T, 0>;

#include <cassert>
int main(){
    //Grid<float, 3> const g3(2, 3, 4, 1.0f);
    //assert(1.0f == g3(1, 1, 1));

    Grid<float, 2> g2(2, 5, 2.0f);
    assert(2.0f == g2(1, 1));

    //g2 = g3[1];
    //assert(1.0f == g2(1, 1));

    return 0;
}