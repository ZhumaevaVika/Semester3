#include <iostream>
using namespace std;
// class Zoo{
//     vector<Animals*>m_animals;
// }

// class Animal{
// public:
//     string myName() const {m_name;}
//     unsigned myAge() const {m_age;}
// private:
//     string m_name;
//     unsigned m_age;
// }

// class Cat: public Animal{
//     void jump(){}
// }

class Base{
public:
    void foo() {cout << "Foo" << endl;}
protected:
    char m_c;
private:
     int m_x;
};
class PublicDerived : public Base{
    PublicDerived() : m_y(m_c){}
private:
    double m_y;
};

class PrivateDerived : private PublicDerived{
public:
    //PrivateDerived() : m_y(m_c){} 
private:
    int m_pd;

};

//запретить классам наследоваться от него
class Bar final{};

int main(){
    PublicDerived PublicDerived;
    PublicDerived.foo();
    return 0;
}