#include <iostream>
using namespace std;

template<typename T, typename U>
T bit_cast(U value) {
    T result;
    result = static_cast<T>(value);
    //memcpy(&result, &value, sizeof(T));
    return result;
}

int main(){
    int a = 5;
    double b = bit_cast<double, int>(a);
    cout << b << ' ' << sizeof(b);
    return 0;
}