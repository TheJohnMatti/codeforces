#include <bits/stdc++.h>
using namespace std;


void handle() {
    int n; cin >> n;

    vector<string> g(n);
    for (auto &row : g) cin >> row;

    if (n <= 2) {
        cout << "YES\n";
        return;
    }

    int cnt = 0;

    for (auto i : g) {
        for (auto j : i) {
            if (j == '#') cnt++;
        }
    }
    if (cnt <= 4) {
        for (int i=0; i < g.size()-1; i++) {
            for (int j=0; j < g[i].size()-1; j++) {
                int t_cnt = 0;
                if (g[i][j] == '#') t_cnt++;
                if (g[i+1][j] == '#') t_cnt++;
                if (g[i][j+1] == '#') t_cnt++;
                if (g[i+1][j+1] == '#') t_cnt++;
                if (t_cnt == cnt) {
                    cout << "YES\n";
                    return;
                }
            }
        }
    } 
    vector<vector<int>> coord_set;

    for (int i=0; i < g.size(); i++) {
        for (int j=0; j < g[i].size(); j++) {
            if (g[i][j] == '#') coord_set.push_back({i, j}); 
        }
    }

    int s1 = -2000, s2 = -2000;
    bool fail = false;
    for (auto &c: coord_set) {
        if (s1 == -2000 || c[0] - c[1] == s1) {
            s1 = c[0] - c[1];
        }
        else if (s2 == -2000 || c[0] - c[1] == s2) {
            s2 = c[0] - c[1];
        }
        else {
            fail = true;
            break;
        }
    }
    if (!fail && (abs(s1 - s2) == 1 || s2 == -2000)) {
        cout << "YES\n";
        return;
    }

    s1 = -2000, s2 = -2000;
    fail = false;
    for (auto &c: coord_set) {
        if (s1 == -2000 || c[0] + c[1] == s1) {
            s1 = c[0] + c[1];
        }
        else if (s2 == -2000 || c[0] + c[1] == s2) {
            s2 = c[0] + c[1];
        }
        else {
            fail = true;
            break;
        }
    }
    if (!fail && (abs(s1 - s2) == 1 || s2 == -2000)) {
        cout << "YES\n";
        return;
    }
    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        handle();
    }
    return 0;
}
