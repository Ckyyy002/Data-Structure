#include <bits/stdc++.h>
using namespace std;

struct graph {
    long vertexCount, edgeCount;
    vector<vector<pair<long, long>>> adjList;
    vector<pair<long, pair<long, long>>> edgeList;

    void init(long v) {
        vertexCount = v;
        edgeCount = 0;
        adjList.resize(v+1);
    }

    void add_edge(long vertex1, long vertex2, long weight) {
        adjList[vertex1].push_back(make_pair(vertex2, weight));
        adjList[vertex2].push_back(make_pair(vertex1, weight));
        edgeList.push_back(make_pair(weight, make_pair(vertex1, vertex2)));
        edgeCount++;
    }

    long find_parent(vector<long> &parent, long v) {
        if (v == parent[v]) {
            return v;
        }
        return parent[v] = find_parent(parent, parent[v]);
    }

    void union_set(vector<long> &parent, long vertex1, long vertex2) {
        long parent1 = find_parent(parent, vertex1);
        long parent2 = find_parent(parent, vertex2);
        if (parent1 != parent2) {
            parent[parent2] = parent1;
        }
    }

    void kruskal(vector<pair<long, pair<long, long>>> &result) {
        vector<long> parent(vertexCount+1); 
        for (long i = 1; i <= vertexCount; i++) {
            parent[i] = i;
        }
        sort(edgeList.begin(), edgeList.end());

        for (auto edge : edgeList) {
            long vertex1 = edge.second.first;
            long vertex2 = edge.second.second;
            if (find_parent(parent, vertex1) != find_parent(parent, vertex2)) {
                result.push_back(edge);
                union_set(parent, vertex1, vertex2);
                if (result.size() == vertexCount - 1) {
                    break;
                }
            }
        }
    }
};

int main() {
    graph g;
    long v, e;
    cin >> v >> e;

    g.init(v); 
    for (long i = 0; i < e; i++) {
        long v1, v2, w;
        cin >> v1 >> v2 >> w;
        g.add_edge(v1, v2, w);
    }

    long budget;
    cin >> budget;

    vector<pair<long, pair<long, long>>> mst;
    g.kruskal(mst);

    long total_weight = 0;
    for (auto &edge : mst) {
        total_weight += edge.first;
    }

    if (budget >= total_weight) {
        cout << "Budgetnya cukup Bos! Ada sisa " << budget - total_weight << endl;
    } else {
        cout << "Waduh budgetnya kurang bos" << endl;
    }

    return 0;
}