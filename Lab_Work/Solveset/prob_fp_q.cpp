#include <bits/stdc++.h>
using namespace std;

struct graph {
    map<string, vector<string>> adjList;
    map<string, bool> visited;

    void addEdge(string u, string v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        visited[u] = false;
        visited[v] = false;
    }

    int connect() {
        int count = 0;
        for (auto &it: visited) {
            if (!it.second) {
                queue<string> q;
                q.push(it.first);
                visited[it.first] = true;

                while (!q.empty()) {
                    string s = q.front();
                    q.pop();

                    for (string neighbor : adjList[s]) {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
                count++;
            }
        }
        return count;
    }
};

int main(){
    graph g;
    int N, M, energy;
    cin >> N >> M;

    for (int i = 0; i < M; i++){
        string friend1, friend2;
        cin >> friend1 >> friend2;
        g.addEdge(friend1, friend2);
    }

    cin >> energy;
    
    int components = g.connect();
    if (energy > components) {
        cout << "You tied the loose ends and reached her." << endl;
    } 
    else if (energy < components) {
        cout << "You didn't tie the loose ends. She remains out of reach." << endl;
    } 
    else {
        cout << "You tied the loose ends but couldn't reach her." << endl;
    }
    
    return 0;
}