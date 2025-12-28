#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<pair<int,int>> pairs(m);
    for (int i = 0; i < m; i++) {
        cin >> pairs[i].first >> pairs[i].second;
    }

    cout << "YES\n";
    cout << 2 * m << "\n"; // total votes

    for (int i = 0; i < m; i++) {
        int first = pairs[i].first;
        int second = pairs[i].second;

        // --- First vote: ascending order, first two numbers are first, second ---
        bool first_printed = false;
        for (int j = 1; j <= n; j++) {
            if (j == first || j == second) continue;
            if (first_printed) cout << " ";
            cout << j;
            first_printed = true;
        }
        if (first_printed) cout << " ";
        cout << first << " " << second << "\n";

        // --- Second vote: descending order, then first two numbers at end ---
        first_printed = false;
        for (int j = n; j >= 1; j--) {
            if (j == first || j == second) continue;
            if (first_printed) cout << " ";
            cout << j;
            first_printed = true;
        }
        if (first_printed) cout << " ";
        cout << first << " " << second << "\n";
    }

    return 0;
}
