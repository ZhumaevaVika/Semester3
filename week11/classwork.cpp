#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
using namespace std;

class BadOptAccess : logic_error{
    BadOptAccess(const string &str)
        : logic_error(str){}
    BadOptAccess(const char* str)
        : logic_error(str){}
};

struct MyNullOpt_t
{
};
constexpr MyNullOpt_t MyNullOpt;

template <typename OptType>
class MyOptional final{
public:
    MyOptional() = default;
    MyOptional(const OptType& value);
    MyOptional(const MyOptional&) = default;
    MyOptional(MyOptional&&) = default;
    MyOptional(MyNullOpt_t) {}

    ~MyOptional();
public:
    MyOptional& operator=(const OptType&);
    MyOptional& operator=(const MyOptional &);
    MyOptional& operator=(MyOptional &&);
    MyOptional& operator=(const MyNullOpt_t);

    operator bool();

    OptType operator*();
    OptType operator->();
public:
    OptType& value();
    bool has_value();
    void reset();
    void swap(MyOptional<OptType> &);

private:
    bool m_hasValue;
    OptType *m_value;
};

int main(){
    return 0;
}

template<typename OptType>
MyOptional<OptType>::MyOptional(const OptType& value)
    : m_hasValue(true), m_value(::operator new(sizeof(OptType))) {
        new (m_value) OptType(value);
    }

template<typename OptType>
MyOptional<OptType>::~MyOptional(){
    if constexpr (std::is_trivially_destructible is_destructible_v<OptType>);
    if (m_hasValue){
        m_value.~OptType();
    }
    delete m_value;
}
template<typename OptType>
MyOptional<OptType> &MyOptional<OptType>::operator=(const OptType &value){
    MyOptional tmp(value);
    swap(tmp, *this);
    return *this;
}
template<typename OptType>
MyOptional<OptType> &MyOptional<OptType>::operator=(const MyOptional &other){
    MyOptional tmp(value);
    swap(tmp, *this);
    return *this;
}
template<typename OptType>
MyOptional<OptType> &MyOptional<OptType>::operator=(MyOptional &&other){
    swap(other);
    return this*;
}
template<typename OptType>
MyOptional<OptType>& MyOptional<OptType>::operator=(const MyNullOpt_t){
    MyOptional tmp{MyNullOpt};
    swap(tmp);
    return *this;
}
template<typename OptType>
MyOptional<OptType>::operator bool(){
    return m_hasValue;
}

template<typename OptType>
OptType MyOptional<OptType>::operator*(){
    return value();
}
template<typename OptType>
OptType MyOptional<OptType>::operator->(){
    return m_value;
}

template<typename OptType>
OptType &MyOptional<OptType>:: value(){
    return m_hasValue ? *m_value : (throw BadOptAccess{__LINE__})
}
template<typename OptType>
bool MyOptional<OptType>::has_value(){
        return m_hasValue;
}
template<typename OptType>
void MyOptional<OptType>::reset(){
        MyOptional tmp;
        swap(tmp);
}
template<typename OptType>
void MyOptional<OptType>::swap(MyOptional<OptType>& other){
    std::swap(m_hasValue, other);

}

int main(){
    MyOptional<int> tmp;
}