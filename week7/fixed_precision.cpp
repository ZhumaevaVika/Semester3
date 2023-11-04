#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

int main() {
    ifstream file("input.txt");
    double num;
    while (file >> num) {
        cout << fixed << setprecision(3) << num << endl;
    }
    return 0;
} 