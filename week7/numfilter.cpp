#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
using namespace std;

class numfilterbuf : public streambuf {
private:
	istream *in;
	ostream *out;
	
	int cur; //последнее считанное значение, используется в underflow()
protected:

	/* функции записи в поток: */
	
	virtual int overflow(int c) override {
      if (c != traits_type::eof()) {
        if (isdigit(c) || isspace(c)) {
        *out << static_cast<char>(c);
        }
    }
    return traits_type::eof();
    }

	
	/* функции чтения из потока: */
	
	//реализация по-умолчанию инкрементирует позицию указателя в буфере и вызывает segmentation fault
	virtual int uflow() override {
    int c = underflow();
    while (c != traits_type::eof() && !isdigit(c) && !isspace(c)) {
        c = underflow();
    }
    return c;
    }
	
	virtual int underflow() override {
    if (cur == traits_type::eof()) {
        string str;
        getline(*in, str);
        if (!in->good()) {
        return traits_type::eof();
        }
        stringstream ss(str);
        ss >> noskipws;
        copy(istream_iterator<char>(ss), istream_iterator<char>(), eback());
        setg(eback(), eback(), egptr());
    }
    cur = *gptr();
    return cur;
    }
public:
	numfilterbuf(istream &_in, ostream &_out)
		: in(&_in), out(&_out), cur(traits_type::eof())
	{}
};

int main(int argc, char **argv){
	const char str1[] = "In 4 bytes contains 32 bits";
	const char str2[] = "Unix time starts from Jan 1, 1970";
	istringstream str(str1);
	
	numfilterbuf buf(str, cout); // читать из stringstream, выводить в консоль
	iostream numfilter(&buf); // таким образом обходимся без реализации своего наследника iostream
	
	string val;
	getline(numfilter, val);
	numfilter.clear(); // сбросить невалидное состояние после EOF в процессе чтения из stringstream
	
	cout << "Original: '" << str1 << "'" << endl;
	cout << "Read from numfilter: '" << val << "'" << endl;
	
	cout << "Original: '" << str2 << "'" << endl;
	cout << "Written to numfilter: '";
	numfilter << str2;
	cout << "'" << endl;
	
	return 0;
}
