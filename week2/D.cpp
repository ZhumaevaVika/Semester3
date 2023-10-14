#include <iostream>

struct Cls {
    Cls(char c, double d, std::int32_t i)
        : m_c(c)
        , m_d(d)
        , m_i(i)
    {}
private:
    char m_c;
    double m_d;
    std::int32_t m_i;
};

 struct B {
  B(char c, double d, int i) : c1( c ), d1( d ), i1( i ) {}
  public:
      char c1;
      double d1;
      int i1;
 };

char &get_c(Cls &cls) {
    void *p = &cls;
    B *pb = static_cast<B*>( p );
    return pb->c1;
}

double& get_d(Cls& cls) {
    void *p = &cls;
    B *pb = static_cast<B*>( p );
    return pb->d1;
}

int& get_i(Cls& cls) {
    void *p = &cls;
    B *pb = static_cast<B*>( p );
    return pb->i1;
}