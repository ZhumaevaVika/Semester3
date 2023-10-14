#include <iostream>

using namespace std;

void qsort(void *base, size_t nmeb, size_t size, int (*compar)(const void *, const void *));

template<typename T>
bool compare(const T&l, const T&r){
    return l<r;
}

struct S{
    string name;
};

bool compare(const S&l, const S&r){
    return l.name < r.name;
}


class Complex{
public:
    Complex(const double re, const double im) : m_re(re), m_im(im)
    {
    }

    Complex() = default;

    Complex(const Complex& other) : Complex(other.m_re, other.m_im)
    {
    }
    

    double getRe() const {return m_re;}
    double getIm() const {return m_im;}

    void setRe(const double re) {m_re = re;}
    void setIm(const double im) {m_im = im;}

    Complex& operator=(const Complex& other)
    {
        m_re = other.m_re;
        m_im = other.m_im;
        return *this;
    }

    Complex& operator+=(const Complex& other){
        m_re += other.m_re;
        m_im += other.m_im;
        return *this;
    }

    //Complex operator+(const Complex& other){
        //Complex sum = *this;
        //sum += other;
        //return sum;
    //}

    // Complex& operator++(){
    //     return *this += 1;
    // }
    // Complex operator++(int){
    //     Complex tmp = *this;
    //     ++*this;
    //     return tmp;
    // }

    ~Complex() = default;
private:
    double m_re {0};
    double m_im {0};
};

Complex operator+(const Complex& lhs, const Complex& rhs){
        Complex sum = lhs;
        sum += rhs;
        return sum;
}

class Foo{
public:
    Foo(size_t size) : m_size(size), m_x(new int[m_size])
    {
    }
    ~Foo()
    {
        delete [] m_x;
    }
private:
    size_t m_size;
    int* m_x;

};

ostream& operator<<(ostream& os, const Complex c){
    os << c.getRe() << '+' << c.getIm() << 'i';
    return os;
}

struct Foo
{
    Foo() {cout << 'A' << endl;}
    ~Foo() {cout << "~A" << endl;}
};
struct Bar{
    Foo f;
    Bar() {cout << 'B' << endl;}
    ~Bar() {cout << "~B" << endl;}
};

int main(){
    //cout << compare<int>(3, 5);
    Complex c1(37, 13);
    Complex c2(3, 1);
    cout << c1 << endl;
    c2 += c1;
    cout << c2 << endl;
    Complex c3(c2);
    cout << c3 << endl;

    return 0;
}