#pragma once
#include <iostream>
#include <numeric>

class Rational final {
public:
    // конструктор инициализации
    Rational(int numerator = 0, int denominator = 1){
        m_numerator = numerator;
        m_denominator = denominator;
    }
    // Rational(int numerator): Rational(numerator, 1){}
    // Rational(): Rational(0){}

    // конструктор копирования
    Rational(const Rational& other){
        m_denominator = other.m_denominator;
        m_numerator = other.m_numerator;
    }

    // копмрующий оператор присваивания
    Rational& operator=(const Rational& other)
    {
        m_denominator = other.m_denominator;
        m_numerator = other.m_numerator;
        return *this;
    }

    Rational& operator+=(const Rational& other)
    {
        int a = m_numerator;
        int b = m_denominator;
        int c = other.m_numerator;
        int d = other.m_denominator;
        m_numerator = a*d + c*b;
        m_denominator = b*d;
        int q = std::gcd(m_numerator, m_denominator);
        m_numerator /= q;
        m_denominator /= q;
        return *this;
    }

    Rational& operator-=(const Rational& other)
    {
        int a = m_numerator;
        int b = m_denominator;
        int c = other.m_numerator;
        int d = other.m_denominator;
        m_numerator = a*d - c*b;
        m_denominator = b*d;
        int q = std::gcd(m_numerator, m_denominator);
        m_numerator /= q;
        m_denominator /= q;
        return *this;
    }

    Rational& operator*=(const Rational& other)
    {
        int a = m_numerator;
        int b = m_denominator;
        int c = other.m_numerator;
        int d = other.m_denominator;
        m_numerator = a*c;
        m_denominator = b*d;
        int q = std::gcd(m_numerator, m_denominator);
        m_numerator /= q;
        m_denominator /= q;
        return *this;
    }

    Rational& operator/=(const Rational& other)
    {
        int a = m_numerator;
        int b = m_denominator;
        int c = other.m_numerator;
        int d = other.m_denominator;
        m_numerator = a*d;
        m_denominator = b*c;
        int q = std::gcd(m_numerator, m_denominator);
        m_numerator /= q;
        m_denominator /= q;
        return *this;
    }

    explicit operator double() const {
        return static_cast<double>(m_numerator) / m_denominator;
    }

    double toDouble() const{
        return static_cast<double>(m_numerator)/m_denominator;
    }

private:

    friend Rational operator+(const Rational& lhs, const Rational& rhs){
        Rational sum = lhs;
        sum += rhs;
        return sum;
    };

    friend Rational operator+(const Rational& lhs){
        return lhs;
    };

    friend Rational operator-(const Rational& lhs, const Rational& rhs){
        Rational sum = lhs;
        sum -= rhs;
        return sum;
    };

    friend Rational operator-(const Rational& lhs){
        Rational sum = lhs;
        sum.m_denominator = lhs.m_denominator;
        sum.m_numerator = -lhs.m_numerator;
        return sum;
    };

    friend Rational operator*(const Rational& lhs, const Rational& rhs){
        Rational sum = lhs;
        sum *= rhs;
        return sum;
    };

    friend Rational operator/(const Rational& lhs, const Rational& rhs){
        Rational sum = lhs;
        sum /= rhs;
        return sum;
    };

    friend bool operator<(const Rational &lhs, const Rational &rhs){
        double a = lhs.toDouble();
        double b = rhs.toDouble();
        if (a<b) return true;
        else return false;
    };

    friend bool operator<=(const Rational &lhs, const Rational &rhs){
        double a = lhs.toDouble();
        double b = rhs.toDouble();
        if (a<=b) return true;
        else return false;
    };

    friend bool operator>(const Rational &lhs, const Rational &rhs){
        double a = lhs.toDouble();
        double b = rhs.toDouble();
        if (a>b) return true;
        else return false;
    };

    friend bool operator>=(const Rational &lhs, const Rational &rhs){
        double a = lhs.toDouble();
        double b = rhs.toDouble();
        if (a>=b) return true;
        else return false;
    };

    friend bool operator==(const Rational &lhs, const Rational &rhs){
        double a = lhs.toDouble();
        double b = rhs.toDouble();
        if (a==b) return true;
        else return false;
    };

    friend bool operator!=(const Rational &lhs, const Rational &rhs){
        double a = lhs.toDouble();
        double b = rhs.toDouble();
        if (a!=b) return true;
        else return false;
    };

    int m_numerator;
    int m_denominator;
};

int main(){
    Rational p(1, 2);
    Rational l(3, 4);
    if (p<l){
        std::cout << "ok" << std::endl;
    }
    std::cout << (-p+l).toDouble();
}