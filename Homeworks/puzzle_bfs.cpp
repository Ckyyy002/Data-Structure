#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

const string GOAL = "123804765";

const vector<vector<int>> MOVES = {
    {1,3}, {0,2,4}, {1,5},
    {0,4,6}, {1,3,5,7}, {2,4,8},
    {3,7}, {4,6,8}, {5,7}
};

vector<string> getNeighbors(const string &state) {
    vector<string> neighbors;
    int pos = state.find('0');
    for (int move : MOVES[pos]) {
        string next = state;
        swap(next[pos], next[move]);
        neighbors.push_back(next);
    }
    return neighbors;
}

void printSolution(map<string,string> &parent, string state) {
    vector<string> path;
    while (!state.empty()) {
        path.push_back(state);
        state = parent[state];
    }
    reverse(path.begin(), path.end());

    cout << "Solution found in " << path.size()-1 << " moves:\n\n";
    for (auto &p : path) {
        for (int i = 0; i < 9; i++) {
            cout << (p[i] == '0' ? ' ' : p[i]) << " ";
            if (i % 3 == 2) cout << "\n";
        }
        cout << "\n";
    }
}

void solvePuzzle(const string &start) {
    queue<string> q;
    set<string> visited;
    map<string,string> parent;

    q.push(start);
    visited.insert(start);
    parent[start] = "";

    while (!q.empty()) {
        string cur = q.front(); q.pop();

        if (cur == GOAL) {
            printSolution(parent, cur);
            return;
        }

        for (auto &next : getNeighbors(cur)) {
            if (!visited.count(next)) {
                visited.insert(next);
                parent[next] = cur;
                q.push(next);
            }
        }
    }
    cout << "No Solution!\n";
}

int main() {
    string start = "";
    for (int i = 0; i < 9; i++) {
        int x; cin >> x;
        start += to_string(x);
    }

    solvePuzzle(start);
    return 0;
}
