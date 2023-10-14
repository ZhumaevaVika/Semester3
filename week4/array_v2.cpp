#include <iostream>
using namespace std;

class S{
    public:
    S() = delete;
    S(const S&) = default;
    S&operator=(const S&) = delete;
    S(int){}
};

template <typename T>
class Array
{
public: 
    // Список операций:
    //
    explicit Array(size_t size, const T& val):m_size(size){
        m_data = static_cast<T*>(::operator new[](m_size* sizeof(T)));
        for(size_t i = 0; i<size; i++){
            new(m_data+i) T(val);
        }
    }
    //   конструктор класса, который создает
    //   Array размера size, заполненный значениями
    //   value типа T. Считайте что у типа T есть
    //   конструктор, который можно вызвать без
    //   без параметров, либо он ему не нужен.
    //
    Array(const Array & other):m_size(other.m_size){
        m_data = static_cast<T*>(::operator new[](m_size* sizeof(T)));
        for(size_t i = 0; i<m_size; i++){
            new(m_data+i) T(other.m_data[i]);
        }
    }
    //   конструктор копирования, который создает
    //   копию параметра. Считайте, что для типа
    //   T определен оператор присваивания.
    //
    Array(const Array && other):m_size(other.m_size), m_data(other.m_data){
    }
    //   конструктор перемещения
    //
    ~Array(){
        if (m_data){
            for (size_t i = 0; i<m_size; i++){
                m_data[i].~T();
            }
            operator delete[](m_data);
        }
    }
    //   деструктор, если он вам необходим.
    //
    Array& operator=(const Array & other){
        if(this != &other){
            Array tmp(other);
            swap(m_size, tmp.m_size);
            swap(m_data, tmp.m_data);
        }
        return *this;
    }
    //   оператор копирующего присваивания.
    //
    Array& operator=(Array && other){
        if (this != &other){
            delete[] m_data;
            m_size = other.m_size;
            m_data = other.m_data;
            other.m_size = 0;
            other.m_data = nullptr;
        }
        return *this;
    }
    //   оператор перемещающего присваивания.
    //
    size_t size() const{
        return m_size;
    }
    //   возвращает размер массива (количество
    //                              элементов).
    //
    T& operator[](size_t idx){
        return m_data[idx];
    }
    const T& operator[](size_t idx) const{
        return m_data[idx];
    }
    //   две версии оператора доступа по индексу.
    void print() {
        for (size_t i = 0; i < m_size; i++) {
            printf("%d ", m_data[i]);
        }
        cout << endl;
    }
public:
    // поля определите сами
    size_t m_size{0};
    T* m_data{nullptr};
};

int main(){
    S a = 1;
    S b = 2;
    S c = 3;
    Array arr1(3, a);
    Array arr2(10, b);
    Array arr3(5,c);
    arr1 = arr2;
    arr3 = std::move(arr2);
    cout << arr1.size();
}