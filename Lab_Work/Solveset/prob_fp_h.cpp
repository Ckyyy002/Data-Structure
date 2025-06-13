#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    vector<int> count(128, 0); 

    cin >> s;
    for(char c : s) {
        count[c]++;
    }

    bool found = false;
    for(int i = 0; i < s.size(); i++) {
        if(count[s[i]] == 1) {
            cout << i << endl;
            found = true;
            break;
        }
    }

    if(!found) {
        cout << -1 << endl;
    }
    
    return 0;
}