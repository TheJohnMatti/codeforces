#include <bits/stdc++.h>


using namespace std;
using ll = long long;

int main() {

    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    ll n, k;
    cin >> n >> k;
    if (n * (n-1) / 2 <= k) {
        cout << "no solution" << endl;
        return 0;
    }
    int cn = n;
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            cout << i << " " << j << endl;
            cn--;
            if (!cn) return 0;
        }
    }

    return 0;
}