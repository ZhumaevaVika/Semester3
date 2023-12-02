#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include<string>
using namespace std;

vector<vector<string>> groupByName(vector<string>& strs) {
    vector<vector<string>> result;
    unordered_map<string, int> strToIndex;

    for (const auto& str : strs) {
        string sortedStr = str;
        sort(sortedStr.begin(), sortedStr.end());
        if (strToIndex.find(sortedStr) == strToIndex.end()) {
            strToIndex[sortedStr] = result.size();
            result.push_back({str});
        } else {
            result[strToIndex[sortedStr]].push_back(str);
        }
    }

    return result;
}

void printGroupedStrings(const vector<vector<string>>& groupedStrings) {
    for (const auto& group : groupedStrings) {
        for (const auto& str : group) {
            cout << str << " ";
        }
        cout << endl;
    }
}

int main(){
    vector<string> strs = {"eat","tea","tan","ate","nat","bat"};
    vector<vector<string>> grouped = groupByName(strs);
    printGroupedStrings(grouped);
    
}