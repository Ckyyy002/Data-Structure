#include <bits/stdc++.h>
using namespace std;
 
struct graph{
    long vertexCount, edgeCount;
    vector<vector<pair<long, long>>> adjList;
   
    void init(long v){
        vertexCount = v;
        edgeCount = 0;
 
 
        adjList.resize(vertexCount);
    }
 
    void add_edge(long vertex1, long vertex2, long weight){
        adjList[vertex1].push_back(make_pair(vertex2, weight));
        adjList[vertex2].push_back(make_pair(vertex1, weight));
        edgeCount++;
    }
 
    void dijkstra(vector<long> &result, vector<long> &predecessor, long start){
        vector<bool> visited(vertexCount, false);
        priority_queue <pair<long, long>,
                        vector <pair<long, long>>,
                        greater <pair<long, long>> > pq;
        result = vector<long>(vertexCount, LONG_MAX);
        predecessor = vector<long>(vertexCount, -1); 
       
        pq.push(make_pair(0, start));
        result[start] = 0;
 
 
        while(!pq.empty()){
            auto temp = pq.top();
            pq.pop();
 
 
            long u = temp.second;
            if (visited[u]) continue;
            visited[u] = true;
 
 
            for(auto vertex:adjList[u]){
                long nextVertex = vertex.first;
                long weight = vertex.second;
 
 
                if(!visited[nextVertex] && result[u] + weight < result[nextVertex]){
                    result[nextVertex] = result[u] + weight;
                    pq.push(make_pair(result[nextVertex], nextVertex));
                    predecessor[nextVertex] = u; 
                }
            }
        }
    }
 
    vector<long> trace_path(long start, long end, const vector<long>& predecessor) {
        vector<long> path;
        for (long at = end; at != -1; at = predecessor[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        if (path.front() == start) {

            return path;
        }
        return {}; 
    }
};
 
 
int main(){
    long a, b, start;
    cin >> a >> b;

    graph g;
    g.init(a);

    vector<long> dijkstra_result;
    vector<long> predecessor;

    for (int i = 0; i < b; i++) {
        long vertex1, vertex2, weight;
        cin >> vertex1 >> vertex2 >> weight;
        g.add_edge(vertex1, vertex2, weight);
    }

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> start;

        for (long i = 0; i <= a; i++){
            if (i == start) {
                continue;
            }

            g.dijkstra(dijkstra_result, predecessor, start);

            vector<long> path = g.trace_path(start, i, predecessor);
            cout << "---From " << start << " to " << i << "---" << endl;
            if (!path.empty()) {
                for (auto node : path) {
                    cout << node;
                    if (node != i) {
                        cout << " - ";
                    }
                }
                cout << endl;
            } 
            else { 
                cout << "Invalid starting point" << endl;
            }
        }
    }
    return 0;
}