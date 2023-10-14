#include <iostream>
using namespace std;

template<typename T>
struct Array{
    void resize(size_t n){
        T *ndata = new T[n];
        for (size_t i = 0; i!= n && i != size; ++i){
            ndata[i] = m_data[i];
        }
        delete[] m_data;
        m_data = ndata;
        m_size = n;
    }
    T *m_data;
    size_t m_size;
};

template<typename T>
struct Stack{
    void push(const T &value){
        m_data.push_back(value);
    }
    T top(){
        return m_data.back();
    }
    void pop(){
        m_data.pop_back();
    }
    T pop(){
        T tmp = m_data.back();
        m_data.pop_back();
        return tmp;
    }
};