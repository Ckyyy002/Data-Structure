#include <bits/stdc++.h>
using namespace std;

struct graph{
    long vertexCount, edgeCount;
    vector<vector<pair<long, long>>> adjList;
    
    void init(long v){
        vertexCount = v;
        edgeCount = 0;

        for(int i=0; i<vertexCount; i++){
            adjList.push_back({});
        }
    }

    void add_edge(long vertex1, long vertex2, long weight){
        adjList[vertex1].push_back(make_pair(vertex2, weight));
        edgeCount++;
    }

    void dfs(vector<long> &result, long start){
        vector<bool> visited(vertexCount, false);
        stack<long> st;

        st.push(start);
        visited[start] = true;
        result.push_back(start);

        while(!st.empty()){
            long temp = st.top();
            st.pop();

            if(!visited[temp]){
                result.push_back(temp);
                visited[temp] = true;
            }

            for(auto vertex:adjList[temp]){
                if (!visited[vertex.first]) {
                    st.push(vertex.first);
                }
            }
        }
    }
};

void find_path(graph &g, int start, int end){
    vector<long> result;
    g.dfs(result, start);

    int found = 0;
    long total = 0;
    for(int i = 0; i < result.size(); i++){
        if(result[i] == end) {
            for(int j = 0; j < i; j++){
                for(auto &p : g.adjList[result[j]]) {
                    if(p.first == result[j+1]) {
                        total += p.second;
                        break;
                    }
                }
            }

            cout << "Path found with cost " << total << ": ";
            for(long j = 0; j <= i; j++){
                cout << result[j] << " ";
            }
            cout << endl;
            found = 1;
            break;
        }
    }

    if(!found) {
        cout << "Impossible to find the path" << endl;
    }
}

int main(){
    graph g;
    
    int v, n;
    cin >> v >> n;

    g.init(v);
    for(int i = 0; i < n; i++){
        long vertex1, vertex2, weight;
        cin >> vertex1 >> vertex2 >> weight;
        g.add_edge(vertex1, vertex2, weight);
    }

    int s, e;
    cin >> s >> e;

    find_path(g, s, e);

    return 0;
}