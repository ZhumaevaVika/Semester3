#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

vector<int> majorityKElements(const vector<int>& nums, const int k) {
    unordered_map<int, int> count;
    for (int num : nums) {
        count[num]++;
    }
    
    auto comp = [](pair<int, int>& a, pair<int, int>& b) {
        return a.second < b.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> pq(comp);
    
    for (auto it : count) {
        pq.push(it);
        if (pq.size() > k) {
            pq.pop();
        }
    }
    
    vector<int> result;
    while (!pq.empty()) {
        result.push_back(pq.top().first);
        pq.pop();
    }
    
    return result;
}
