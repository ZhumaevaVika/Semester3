#include <iostream>
using namespace std;

struct IntAbstractQueue {
    virtual void push(int x) = 0;
    virtual int pop() = 0;
    virtual int peek() const = 0;
    virtual bool is_empty() const = 0;
    virtual bool is_full() const = 0;

    virtual ~IntAbstractQueue() { }
};

struct IntStackWithMax final: IntAbstractQueue {
    void push(int x) override {
        data.push(x);
        if (max_data.empty() || x >= max_data.top())
            max_data.push(x);
    }
    int pop() override {
        int top = data.top();
        data.pop();
        if (top == max_data.top())
            max_data.pop();
        return top;
    }
    int peek() const override {
        return data.top();
    }
    bool is_empty() const override {
        return data.empty();
    }
    bool is_full() const override {
        return data.size() == 10;
    }
    int get_max() const {
        return max_data.top();
    }

    ~IntStackWithMax() { }
private:
    std::stack<int> data;
    std::stack<int> max_data;
};

#include <cassert>
void with_queue_do(IntAbstractQueue &q) {
    assert(q.is_empty());
    q.push(1);
    assert(!q.is_empty());
    assert(1 == q.peek());
    assert(!q.is_empty());
    assert(1 == q.pop());
    assert(q.is_empty());
    for (int cnt = 0; cnt != 10; ++cnt)
        q.push(cnt);
    assert(q.is_full());
}
void with_stackwithmax_do(IntStackWithMax &swm) {
    with_queue_do(swm);
    for (int cnt = 10; cnt != 0; --cnt)
        assert(cnt - 1 == swm.get_max() and cnt - 1 == swm.pop());
    assert(swm.is_empty()); 
}

int main() {
    IntStackWithMax swm;
    with_stackwithmax_do(swm);
    return 0;
}