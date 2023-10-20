#include <iostream>
#include <string>
#include <sstream>
#include <exception>
using namespace std;

// исключение bad_from_string
class bad_from_string : public exception
{
public:
    bad_from_string(const char* msg) noexcept : message(msg) {}
    bad_from_string(const string& msg) noexcept : message(msg) {}

    const char* what() const noexcept override
    {
        return message.c_str();
    }

private:
    string message;
};

// функция from_string
template<class T>
T from_string(string const& s)
{
    istringstream iss(s);
    iss >> noskipws;

    T result;
    if (iss >> result && iss.eof())
        return result;
    else
        throw bad_from_string("Error converting string to type");
}


int main(){
    string s1("123");
    int a1 = from_string<int>   (s1); // a1 = 123
    double b1 = from_string<double>(s1); // b1 = 123.0
    string c1 = from_string<string>(s1); // c1 = "123"

    string s2("12.3");
    int    a2 = from_string<int>   (s2); // исключение
    double b2 = from_string<double>(s2); // b2 = 12.3
    string c2 = from_string<string>(s2); // c2 = "12.3"

    string s3("abc");
    int    a3 = from_string<int>   (s3); // исключение
    double b3 = from_string<double>(s3); // исключение
    string c3 = from_string<string>(s3); // c3 = "abc"
    //cout << typeid(b2).name() << ' ' << typeid(c2).name() << endl;
    return 0;
}