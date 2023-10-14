#include <iostream>
using namespace std;

enum class error_t { OVF_ERROR, UDF_ERROR }

int divide(int x, int y) {
    if (y == 0) throw error_t::OVF_ERROR;
    return x / y;
}
