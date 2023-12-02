#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <string>
using namespace std;

class RandomizedSet {
public:
    RandomizedSet() {}

    bool insert(int val) {
        if (valToIndex.find(val) != valToIndex.end()) {
            return false;
        }
        values.push_back(val);
        valToIndex[val] = values.size() - 1;
        return true;
    }

    bool remove(int val) {
        if (valToIndex.find(val) == valToIndex.end()) {
            return false;
        }
        int index = valToIndex[val];
        int lastVal = values.back();
        values[index] = lastVal;
        valToIndex[lastVal] = index;
        values.pop_back();
        valToIndex.erase(val);
        return true;
    }

    int getRandom() {
        int randomIndex = rand() % values.size();
        return values[randomIndex];
    }

private:
    vector<int> values;
    unordered_map<int, int> valToIndex;
};

int main(){
    return 0;
}