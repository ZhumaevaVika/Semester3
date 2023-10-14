#include <iostream>

struct Base { }; 

struct D1 : Base { };

struct D2 : Base { }; 

struct D3 : D1, D2 { };

Base const * D1BaseToD2Base(Base const * base) {
    D3 const * d3 = dynamic_cast<D3 const *>(base);
    D2 const * d2 = d3;
    base = d2;
    return base;
}