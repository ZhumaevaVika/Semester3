#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int numRabbits(vector<int>& answers) {
    unordered_map<int, int> count;
    for (int ans : answers) {
        count[ans]++;
    }
    
    int result = 0;
    for (auto it : count) {
        int group = it.first + 1;
        int num = it.second;
        result += (num + group - 1) / group * group;
    }
    
    return result;
}

int main(){
    vector<int> answers = {10,10,10};
    cout << numRabbits(answers);
    return 0;
}