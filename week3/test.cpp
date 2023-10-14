#include <iostream>



struct Base {

public:

    void hello() { std::cout << 1 << std::endl; }

};



class Derive: Base {

public:

    //void hello() { std::cout << 2 << std::endl; }

};



void call(Base b) {

    b.hello();

}



int main() {

    Base b;

    call(b);

}