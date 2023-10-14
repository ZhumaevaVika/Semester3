#include <iostream>

struct Foo {
    void say() const { std::cout << "Foo says: " << msg << "\n"; }
protected:
    Foo(const std::string& msg) : msg(msg) { }
private:
    const std::string& msg;
};

 struct B: public Foo {
    public:
      B(const std::string& msg) : Foo(msg) { }
 };

Foo get_foo(std::string msg) {
    B b(msg);
    Foo& foo = b;
    // B& dd() = static_cast<B&>(&b)
    return foo;
}

void foo_says(const Foo& foo) { foo.say(); }

int main(){
    std::string msg = "Hi";
    foo_says(get_foo(msg));
}
