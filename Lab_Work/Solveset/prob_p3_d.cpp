#include <bits/stdc++.h>
using namespace std;

struct graph {
    long vertexCount, edgeCount;
    vector<vector<long>> adjList;
    vector<long> parent;
    vector<bool> visited;
    vector<long> cycleVertices;

    void init(long v) {
        vertexCount = v;
        edgeCount = 0;
        adjList.resize(vertexCount);
        parent.resize(vertexCount, -1);
        visited.resize(vertexCount, false);
    }

    void add_edge(long vertex1, long vertex2) {
        adjList[vertex1].push_back(vertex2);
        adjList[vertex2].push_back(vertex1);
        edgeCount++;
    }

    bool cycleCheck(long v, long p) {
        visited[v] = true;
        for (auto neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                parent[neighbor] = v;
                if (cycleCheck(neighbor, v)) {
                    return true;
                }
            } else if (neighbor != p) {
                long current = v;
                while (current != neighbor) {
                    cycleVertices.push_back(current);
                    current = parent[current];
                }
                cycleVertices.push_back(neighbor);
                return true;
            }
        }
        return false;
    }

    bool hasCycle() {
        for (long i = 0; i < vertexCount; ++i) {
            if (!visited[i] && cycleCheck(i, -1)) {
                return true;
            }
        }
        return false;
    }

    void printYes() {
        sort(cycleVertices.begin(), cycleVertices.end());
        cout << "VOCALOID CYCLE PROGRAM (VCP) : CYCLE DETECTED";
        for (auto v : cycleVertices) {
            cout << " " << v;
        }
        cout << endl;
    }

    void printNo() {
        cout << "VOCALOID CYCLE PROGRAM (VCP) : NO CYCLE DETECTED" << endl;
    }
};

int main() {
    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        long V, N;
        cin >> V >> N;

        graph g;
        g.init(V);

        for (long i = 0; i < N; ++i) {
            long v1, v2;
            cin >> v1 >> v2;
            g.add_edge(v1, v2);
        }

        if (g.hasCycle()) {
            g.printYes();
        } 
        else {
            g.printNo();
        }
    }

    return 0;
}