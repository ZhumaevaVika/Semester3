#include <iostream>
using namespace std;

template<typename T, typename U>
void copy_n(T* dest, const U* src, size_t count) {
    for(size_t i = 0; i < count; ++i) {
        dest[i] = static_cast<T>(src[i]);
    }
}

int main(){
    int ints[] = {1, 2, 3, 4};
    double doubles[4] = {};
    copy_n(doubles, ints, 4);
    for (int i=0; i<4; i++){
        cout << sizeof(doubles[i]);
    }
}