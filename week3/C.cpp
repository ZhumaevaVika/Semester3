#include <iostream>

class Expression {
public:
    virtual double evaluate() const = 0;
    virtual ~Expression() {}
};

class Number : public Expression {
public:
    Number(double value) : value(value) {}
    double evaluate() const { return value; }
private:
    double value;
};

class BinaryOperation : public Expression {
public:
    BinaryOperation(Expression const * left, char op, Expression const * right)
        : left(left), right(right), op(op) {}
    double evaluate() const {
        double left_val = left->evaluate();
        double right_val = right->evaluate();
        switch (op) {
            case '+': return left_val + right_val;
            case '-': return left_val - right_val;
            case '*': return left_val * right_val;
            case '/': return left_val / right_val;
            default: return 0.0;
        }
    }
    ~BinaryOperation() {
        delete left;
        delete right;
    }
private:
    Expression const * left;
    Expression const * right;
    char op;
};