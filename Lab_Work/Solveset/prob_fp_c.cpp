#include <bits/stdc++.h>
using namespace std;

int energy(vector<int> &kartu) {
    stack<int> s;
    int jumlah = 0;

    for (int i = 0; i < kartu.size(); i++) {
        while (!s.empty() && kartu[i] > kartu[s.top()]) {
            int top_index = s.top();
            s.pop();

            if (s.empty()) {
                break;
            }

            int jarak = i - s.top() - 1;
            int batas = min(kartu[i], kartu[s.top()]) - kartu[top_index];
            jumlah += jarak * batas;
        }
        s.push(i);
    }

    return jumlah;
}

int main() {
    int n;
    cin >> n;

    vector<int> card(n);
    for(int i = 0; i < n; i++) {
        cin >> card[i];
    }

    cout << energy(card) << endl;  
    return 0;
}