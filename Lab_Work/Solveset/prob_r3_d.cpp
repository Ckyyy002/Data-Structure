#include <bits/stdc++.h>
using namespace std;

struct graph {
    long vertexCount, edgeCount;
    vector<vector<pair<long, long>>> adjList;
    
    void init(long v) {
        vertexCount = v;
        edgeCount = 0;
        adjList.resize(v+1);
    }

    void add_edge(long vertex1, long vertex2, long weight) {
        adjList[vertex1].push_back(make_pair(vertex2, weight));
        edgeCount++;
    }

    void dijkstra(vector<long> &result, long start) {
        vector<bool> visited(vertexCount+1, false); 
        priority_queue<pair<long, long>, vector<pair<long, long>>, greater<pair<long, long>>> pq;
        result = vector<long>(vertexCount+1, LONG_MAX); 
        
        pq.push(make_pair(0, start));
        result[start] = 0;

        while(!pq.empty()) {
            auto temp = pq.top();
            pq.pop();

            if (visited[temp.second]) {
                continue;
            }
            visited[temp.second] = true;

            for (auto vertex : adjList[temp.second]) {
                long nextVertex = vertex.first;
                long weight = vertex.second;

                if (!visited[nextVertex]) {
                    if (temp.first + weight < result[nextVertex]) {
                        result[nextVertex] = temp.first + weight;
                        pq.push(make_pair(result[nextVertex], nextVertex));
                    }
                }
            }
        }
    }
};

int main() {
    graph g;
    
    int n, k;
    cin >> n >> k;

    g.init(n);
    
    while(1) {
        long vertex1, vertex2, weight;
        cin >> vertex1 >> vertex2 >> weight;
        if (vertex1 == 0 && vertex2 == 0 && weight == 0) {
            break;
        }
        g.add_edge(vertex1, vertex2, weight);
    }

    vector<long> dijkstra_result;
    g.dijkstra(dijkstra_result, k);

    long max_distance = 0;
    bool cant = false;
    
    for (int i = 1; i <= n; i++) {
        if (i == k) {
            continue;
        }

        if (dijkstra_result[i] == LONG_MAX) {
            cant = true;
            break;
        } 
        else {
            max_distance = max(max_distance, dijkstra_result[i]);
        }
    }

    if (cant) {
        cout << -1 << endl;
    } 
    else {
        cout << max_distance << endl;
    }

    return 0;
}