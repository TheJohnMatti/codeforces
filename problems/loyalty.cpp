#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void handle() {
    int n, x;
    cin >> n >> x;
    vector<int> items(n), output;
    for (int i=0; i < n; i++) {
        cin >> items[i];
    }
    sort(items.begin(), items.end());
    int p1 = 0, p2 = n-1;
    ll cnt = 0, bonus = 0;
    while (p1 <= p2) {
        if (cnt + items[p2] >= x) {
            bonus += items[p2];
            cnt = (cnt + items[p2]) % x;
            output.push_back(items[p2]);
            p2--;
        } else {
            cnt = (cnt + items[p1]) % x;
            output.push_back(items[p1]);
            p1++;
        }
    }
    cout << bonus << endl;
    for (int i = 0; i < n; i++) {
        cout << output[i] << " ";
    }
    cout << endl;
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