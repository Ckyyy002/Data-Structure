#include <bits/stdc++.h>
using namespace std;

const int MAX = 100;

int h, w;
char grid[MAX][MAX];
int visited[MAX][MAX];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
 
struct titik {
    int x, y;
};

bool valid(int x, int y) {
    return x >= 0 && x < h && y >= 0 && y < w && !visited[x][y] && grid[x][y] == '+';
}

int dfs(int x, int y) {
    stack<titik> s;
    s.push({x, y});
    visited[x][y] = 1;
    int area = 0;
    
    while (!s.empty()) {
        titik current = s.top();
        s.pop();
        area++;
        
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            
            if (valid(nx, ny)) {
                visited[nx][ny] = 1;
                s.push({nx, ny});
            }
        }
    }
    
    return area;
}

int main() {
    cin >> h >> w;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> grid[i][j];
            visited[i][j] = 0;
        }
    }

    int total = 0, max_area = 0;
    int area[MAX * MAX] = {0};

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == '+' && !visited[i][j]) {
                int current_area = dfs(i, j);
                total++;
                if (current_area > max_area) {
                    max_area = current_area;
                }
                area[current_area]++;
            }
        }
    }

    int even_count = 0;
    for (int i = 1; i <= max_area; i++) {
        if (area[i] > 0 && i % 2 == 0) {
            even_count += area[i];
        }
    }
    cout << total << " " << max_area << " " << even_count << endl;

    return 0;
}