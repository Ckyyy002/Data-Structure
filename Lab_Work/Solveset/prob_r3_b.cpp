#include <bits/stdc++.h>
using namespace std;

struct graph {
    long vertexCount, edgeCount;
    vector<vector<long>> adjList;

    void init(long v) {
        vertexCount = v;
        edgeCount = 0;
        adjList.resize(v);
    }

    void add_edge(long vertex1, long vertex2) {
        adjList[vertex1].push_back(vertex2);
        adjList[vertex2].push_back(vertex1);
        edgeCount++;
    }

    long bfs(long start, long end) {
        if (start == end) {
            return 0;
        }
        
        vector<long> distance(vertexCount, -1);
        queue<long> q;
        
        distance[start] = 0;
        q.push(start);
        
        while (!q.empty()) {
            long current = q.front();
            q.pop();
            
            for (long neighbor : adjList[current]) {
                if (distance[neighbor] == -1) {
                    distance[neighbor] = distance[current] + 1;
                    q.push(neighbor);
                    
                    if (neighbor == end) {
                        return distance[end];
                    }
                }
            }
        }
        
        return -1;
    }
};

int main() {
    graph g;
    long n, m, s, t;
    cin >> n >> m >> s >> t;

    g.init(n);
    for (long i = 0; i < m; i++) {
        long u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }

    long result = g.bfs(s, t);
    cout << result << endl;

    return 0;
}