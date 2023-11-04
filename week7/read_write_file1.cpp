#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream file("input.txt");
    string content;

    if (file.is_open()) {
        while (getline(file, content)) {
            cout << content << endl;
        }
        file.close();
    }
    return 0;
}