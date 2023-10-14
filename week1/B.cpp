#include <iostream>
using namespace std;

template<typename T, size_t arr_size>
void print_array(T* arr){
    for (int i=0; i<arr_size-1; i++){
        cout << arr[i] << ' ';
    }
    cout << arr[arr_size-1] << endl;
}


int main() {
  int arr[12] = {1, 0, 2, -1, 3, -2, 4, -5, 6, -7, 8, -9};
  print_array<int, 12>(arr);
  return 0;
}