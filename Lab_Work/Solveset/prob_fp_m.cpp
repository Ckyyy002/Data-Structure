#include <bits/stdc++.h>
using namespace std;

int main() {
    map<string, int> m;
    
    int n;
    cin >> n;

    for(int i = 0; i < n; i++) {
        string cmd, frt;
        int x;
        cin >> cmd >> frt >> x;

        if(cmd == "ADD") {
            m[frt] += x;
        }
        else {
            if(m.count(frt)) {
                if(m[frt] >= x) {
                    m[frt] -= x;
                    cout << "SUCCESS" << endl;
                }
                else {
                    cout << "not enough stock" << endl;
                }
            }
            else {
                cout << "item not found" << endl;
            }
        }
    }
}