#include <iostream>
using namespace std;

template <int P, int base>
struct rec_pow{
    static const unsigned value = base*rec_pow<P-1, base>::value;
};

template <int base>
struct rec_pow<0, base>{
    static const unsigned value = 1;
};

int main(){
    cout << rec_pow<3, 2>::value;
    return 0;
}