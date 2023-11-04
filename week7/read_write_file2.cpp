#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream file("input.txt");
    ofstream fout("output.txt");
    string content;

    if (file.is_open()) {
        while (getline(file, content)) {
            fout << content << endl;
        }
        file.close();
        fout.close();
    }
    return 0;
}