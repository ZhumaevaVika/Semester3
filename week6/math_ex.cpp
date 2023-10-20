#include <iostream>
#include <string>
using namespace std;

class MathException {
public:
    virtual string what() const {
        return "Mathematical error";
    }
};

class DivisionByZeroException : public MathException {
public:
    string what() const override {
        return "Division by zero";
    }
};

class OverflowException : public MathException {
public:
    string what() const override {
        return "Overflow error";
    }
};

class UnderflowException : public MathException {
public:
    string what() const override {
        return "Underflow error";
    }
};

int divide(int x, int y) {
    if (y == 0) throw DivisionByZeroException();
    if (x > 0 && y > 0 && x > INT_MAX / y) throw OverflowException();
    if (x < 0 && y < 0 && x < INT_MAX / y) throw UnderflowException();
    return x / y;
}

int main() {
    try {
        int result = divide(10, 0);
    }
    catch (const MathException& e) {
        cout << e.what() << endl;
    }
    // try {
    //     int result = divide(2147483646, 2147483646);
    // }
    // catch (const MathException& e) {
    //     cout << e.what() << endl;
    // }
    return 0;
}