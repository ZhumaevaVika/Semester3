#include <queue>
#include <vector>

bool possibleBipartition(int N, std::vector<std::vector<int>>& dislikes) {
    std::vector<std::vector<int>> graph(N+1);
    for (auto dislike : dislikes){
        graph[dislike[0]].push_back(dislike[1]);
        graph[dislike[1]].push_back(dislike[0]);
    }

    std::vector<int> colors(N+1, 0);

    for (int i = 1; i <= N; i++){
        if (colors[i] != 0) continue;

        colors[i] = 1;
        std::queue<int> q;
        q.push(i);

        while (!q.empty()){
            int cur = q.front();
            q.pop();

            for (int neighbor : graph[cur]) {
                if (colors[neighbor] == 0){
                    colors[neighbor] = -colors[cur];
                    q.push(neighbor);
                }
                else if (colors[neighbor] == colors[cur]) return false;
            }
        }
    }

    return true;
}