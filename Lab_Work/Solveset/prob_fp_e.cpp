#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> q;

    for (int i = 0; i < n; i++) {
        char str[20];
        cin >> str;

        if(strcmp(str, "depan") == 0) {
            if(!q.empty()) {
                cout << q.front();
                q.erase(q.begin());
            }
            else {
                cout << endl;
            }
            cout << endl;
        }
        else if(strcmp(str, "belakang") == 0) {
            if (!q.empty()) {
                cout << q.back();
                q.pop_back();
            }
            else {
                cout << endl;
            }
            cout << endl;
        }
        else if(strcmp(str, "tambahDepan") == 0) {
            int x;
            cin >> x;
            q.insert(q.begin(), x);
        }
        else if(strcmp(str, "tambahBelakang") == 0) {
            int x;
            cin >> x;
            q.push_back(x);
        }
        else if(strcmp(str, "balik") == 0) {
            reverse(q.begin(), q.end());
        }
    }

    return 0;
}