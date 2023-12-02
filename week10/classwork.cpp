#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Iterator{
public:
    using iterator_category = random_access_iterator_tag;
    using value_type = int;
    using pointerf_type = int*;
    using reference_type = int8_t;
    using difference_type = ptrdiff_t;
};

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void printVectorsWithPrimes(const vector<vector<int>>& vec) {
    for (const auto& innerVec : vec) {
        if (any_of(innerVec.begin(), innerVec.end(), isPrime)) {
            for (int num : innerVec) {
                cout << num << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    vector<vector<int>> vec = {{1, 2, 3, 4, 5}, {6, 8, 9, 10}, {11, 12, 13, 14, 15}};
    printVectorsWithPrimes(vec);
    return 0;
}