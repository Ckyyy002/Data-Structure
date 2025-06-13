#include <bits/stdc++.h>
using namespace std;

const int MAX = 100;

struct graph {
    vector<vector<pair<int, int>>> adj;

    void init() {
        adj.resize(MAX);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    bool dfs(int u, int target_weight, int sum, set<pair<int, int>> &visitedEdge) {
        if (sum == target_weight) {
            return true;
        }
        if (sum > target_weight) {
            return false;
        }

        for (auto it : adj[u]) {
            int v = it.first;
            int w = it.second;
            pair<int, int> edge1 = {u, v};
            pair<int, int> edge2 = {v, u}; 

            if (visitedEdge.count(edge1) == 0 && visitedEdge.count(edge2) == 0) {
                visitedEdge.insert(edge1);
                visitedEdge.insert(edge2);
                if (dfs(v, target_weight, sum + w, visitedEdge)) {
                    return true;
                }
                visitedEdge.erase(edge1);
                visitedEdge.erase(edge2);
            }
        }

        return false;
    }
};

int main() {
    graph g;
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        g.init();

        while (1) {
            int u, v, w;
            cin >> u >> v >> w;
            if (u == 0 && v == 0 && w == 0) {
                break;
            }
            g.addEdge(u, v, w);
            g.addEdge(v, u, w); 
        }

        int target;
        cin >> target;

        bool found = false;
        for (int i = 0; i < MAX; i++) {
            set<pair<int, int>> visitedEdge;
            if (g.dfs(i, target, 0, visitedEdge)) {
                found = true;
                break;
            }
        }

        if(found) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }

    return 0;
}