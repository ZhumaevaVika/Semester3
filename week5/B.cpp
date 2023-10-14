#include <iostream>
#include <cmath>
using namespace std;

template <unsigned i, unsigned N>
struct primal{
    static const unsigned value = (N%i == 0) ? primal<i-1, N>:false::value;
};

template <unsigned N>
struct primal<1, N>{
    static const unsigned value = true;
};

int main(){
    cout << primal<4, 5>::value;
    return 0;
}