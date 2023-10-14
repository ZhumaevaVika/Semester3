#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

struct SegmentAbstract {
    virtual int beg() const = 0;
    virtual int end() const = 0;

    virtual ~SegmentAbstract() { }
};

struct SegmentSimple final: SegmentAbstract {
    int beg() const override { return _beg; }
    int end() const override { return _end; }
    SegmentSimple(int beg, int end): _beg(beg), _end(end) { }
private:
    int const _beg, _end;
};

struct SegmentSumm final : SegmentAbstract {
    int beg() const override { return _beg; }
    int end() const override { return _end; }

    SegmentSumm() : _beg(0), _end(0) {}
    SegmentSumm(SegmentAbstract const *a, SegmentAbstract const *b) {
        if (a->beg() > a->end())
            std::swap(a, b);
        if (b->beg() > b->end()) {
            _beg = a->beg();
            _end = a->end();
        } else {
            _beg = std::min(a->beg(), b->beg());
            _end = std::max(a->end(), b->end());
        }
    }

private:
    int _beg, _end;
};

struct SegmentMultiply final : SegmentAbstract {
    int beg() const override { return _beg; }
    int end() const override { return _end; }

    SegmentMultiply() : _beg(1), _end(0) {}
    SegmentMultiply(SegmentAbstract const *a, SegmentAbstract const *b) {
        if (a->beg() > a->end())
            std::swap(a, b);
        if (b->beg() > b->end()) {
            _beg = 1;
            _end = 0;
        } else {
            _beg = std::max(1, std::min(a->end(), b->end()) - std::max(a->beg(), b->beg()) + 1);
            _end = _beg > 0 ? _beg : 0;
        }
    }

private:
    int _beg, _end;
};

int main() {
    SegmentAbstract const *s1 = new SegmentSimple(1, 10);
    SegmentAbstract const *s2 = new SegmentSimple(5, 15);
    SegmentAbstract const *e  = new SegmentSimple(25, 20);

    SegmentAbstract const *summ_s1_s2 = new SegmentSumm(s1, s2);
    SegmentAbstract const *mult_s1_s2 = new SegmentMultiply(s1, s2);
    SegmentAbstract const *summ_s1_e = new SegmentSumm(s1, e);
    SegmentAbstract const *mult_s1_e = new SegmentMultiply(s1, e);
    
    assert(1 == summ_s1_s2->beg() and 15 == summ_s1_s2->end());
    assert(5 == mult_s1_s2->beg() and 10 == mult_s1_s2->end());
    assert(1 == summ_s1_e->beg() and 10 == summ_s1_e->end());
    assert(mult_s1_e->beg() > mult_s1_e->end());
    
    delete mult_s1_e;
    delete summ_s1_e;
    delete mult_s1_s2;
    delete summ_s1_s2;
    delete e;
    delete s2;
    delete s1;
    return 0;
}