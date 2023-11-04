#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

struct MyClass{int a, b, c;};

istream &operator>>(istream is, MyClass mc){
    is >> mc.a >> mc.b >> mc.c;

    return is;
}

int main(){
    // cout << "Hello, wolrld!";
    // abort();
    // int n = 123;
    // cout << dec << n << endl;
    // cout << hex << n << endl;
    // cout << oct << n << endl;

    // cout << setw(10) << setfill('.') << right << 123 << endl;
    // for (int i=0; i<10001; i++){
    //     int n = i/100;
    //     cout << "[";
    //     cout << setw(n/5) << setfill('#') << "";
    //     cout << setw(20-n/5) << setfill('.') << "";
    //     cout << "]   " << n << "%" << "\r";
    // }
    // cout << endl;

    ifstream file ("tmp.txt");
    if (!file.is_open()){
        cout << "Can't open file";
        exit(0);
    }
    string str;
    while (!file.eof()){
        getline(file, str);
        cout << str << endl;
    }

    return 0;
}