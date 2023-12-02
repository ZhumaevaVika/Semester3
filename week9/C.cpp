#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;

vector<string> findRepeatedDnaSequences(string s) {
    vector<string> result;
    if ( s.size() < 10 ) return {};
    unordered_map<string, int> substrMap;

    for (int i = 0; i <= s.length() - 10; ++i) {
        string substr = s.substr(i, 10);
        substrMap[substr]++;
    }

    for (auto substr : substrMap) {
        if (substr.second > 1) {
            result.push_back(substr.first);
        }
    }

    return result;
}