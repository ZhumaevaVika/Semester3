#include <iostream>
using namespace std;

struct IntAbstractQueue {
    virtual void push(int x) = 0;
    virtual int pop() = 0;
    virtual bool is_empty() const = 0;
    virtual bool is_full() const = 0;

    virtual ~IntAbstractQueue() { }
};

struct IntStack: IntAbstractQueue {
    void push(int x) override {
        data[top++] = x;
    }
    int pop() override {
        return data[--top];
    }
    bool is_empty() const override {
        return 0 == top;
    }
    bool is_full() const override {
        return 10 == top;
    }
private:
    unsigned top = 0;
    int data[10];
};

struct IntStackWithMax: IntStack {
    unsigned &get_top(IntStack &stack){
        void *p = &stack;
        IntStackWithMax *pb = static_cast<IntStackWithMax*>( p );
        return pb->top_m;
    }

    int get_max() const {
        int max_val = data_m[0];
        for (unsigned i = 1; i < top_m; ++i)
            if (data_m[i] > max_val)
                max_val = data_m[i];
        return max_val;
    }

    unsigned top_m = 0;
    int data_m[10];
};

#include <cassert>
void with_queue_do(IntAbstractQueue &q) {
    assert(q.is_empty());
    q.push(1);
    assert(!q.is_empty());
    assert(1 == q.pop());
    assert(q.is_empty());
    for (int cnt = 0; cnt != 10; ++cnt)
        q.push(cnt);
    assert(q.is_full());
}
void with_stack_do(IntStack &s) {
    with_queue_do(s); 
    for (int cnt = 10; cnt != 0; --cnt)
        assert(cnt - 1 == s.pop());
    assert(s.is_empty());
}
void with_stackwithmax_do(IntStackWithMax &swm) {
    with_queue_do(swm);
    for (int cnt = 10; cnt != 0; --cnt)
        assert(cnt - 1 == swm.get_max() and cnt - 1 == swm.pop());
    assert(swm.is_empty()); 
}

int main() {
    IntStackWithMax swm;
    with_stack_do(swm);
    with_stackwithmax_do(swm);
    return 0;
}