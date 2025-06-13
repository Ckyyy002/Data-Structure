#include <bits/stdc++.h>
using namespace std;

struct graph {
    long vertexCount, edgeCount;
    vector<vector<pair<long, long>>> adjList;
    vector<pair<long, pair<long, long>>> edgeList;

    void init(long v) {
        vertexCount = v;
        edgeCount = 0;
        adjList.clear();
        adjList.resize(vertexCount);
    }

    void add_edge(long vertex1, long vertex2, long weight) {
        adjList[vertex1].push_back(make_pair(vertex2, weight));
        adjList[vertex2].push_back(make_pair(vertex1, weight));
        edgeList.push_back(make_pair(weight, make_pair(vertex1, vertex2)));
        edgeCount++;
    }

    void bfs(long start, long L, vector<long> &result) const {
        vector<bool> visited(vertexCount, false);
        vector<long> distance(vertexCount, -1);
        queue<long> q;

        q.push(start);
        visited[start] = true;
        distance[start] = 0;

        while (!q.empty()) {
            long temp = q.front();
            q.pop();

            for (auto neighbor : adjList[temp]) {
                long next = neighbor.first;
                if (!visited[next]) {
                    visited[next] = true;
                    distance[next] = distance[temp] + 1;
                    q.push(next);
                }
            }
        }

        for (long i = 0; i < vertexCount; ++i) {
            if (distance[i] == L) {
                result.push_back(i);
            }
        }
    }
};

int main() {
    long n, m, L, s;
    cin >> n >> m >> L >> s;

    graph g;
    g.init(n);

    for (long i = 0; i < m; ++i) {
        long u, v;
        cin >> u >> v;
        g.add_edge(u, v, 1);
    }

    vector<long> hasil;
    g.bfs(s, L, hasil);

    if (hasil.empty()) {
        cout << "Not Found" << endl;
    } 
    else {
        sort(hasil.begin(), hasil.end());
        for (auto node : hasil) {
            cout << node << endl;
        }
    }

    return 0;
}
