#include <iostream>
#include <vector>
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

void printSolution(vector<string> &path) {
    cout << "Solution found in " << path.size()-1 << " moves:\n\n";
    for (auto &p : path) {
        for (int i = 0; i < 9; i++) {
            cout << (p[i] == '0' ? ' ' : p[i]) << " ";
            if (i % 3 == 2) cout << "\n";
        }
        cout << "\n";
    }
}

bool DLS(string state, int depth, int limit, set<string> &visited, vector<string> &path) {
    if (state == GOAL) return true;
    if (depth == limit) return false;

    visited.insert(state);
    for (auto &next : getNeighbors(state)) {
        if (!visited.count(next)) {
            path.push_back(next);
            if (DLS(next, depth+1, limit, visited, path)) return true;
            path.pop_back();
        }
    }
    visited.erase(state); 
    return false;
}

void IDS(string start) {
    for (int limit = 0; ; limit++) {
        set<string> visited;
        vector<string> path = {start};
        if (DLS(start, 0, limit, visited, path)) {
            printSolution(path);
            return;
        }
    }
}

int main() {
    string start = "";
    for (int i = 0; i < 9; i++) {
        int x; cin >> x;
        start += to_string(x);
    }

    IDS(start);
    return 0;
}
