#include <iostream>
#include <bits/stdc++.h>
using namespace std;


int dp[30001][501];
int gems[30001];

void solve() {
    int n, d;
    cin >> n >> d;
    int max_x = 0;
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        max_x = max(max_x, v);
        gems[v]++;
    }
    for (int i=0; i < 30001; i++) {
        for (int j=1; j < 501; j++) dp[i][j] = -30001;
    }
    dp[d][250] = gems[d];
    int res = gems[d];
    for (int i=d+1 ; i <= max_x; i++) {
        int cnt = gems[i];
        int m_val = -30001;
        for (int j=1; j < 500; j++) {
            int offset = j-250+d;
            if (i-offset < d || offset <= 0) continue;
            int val = cnt + max({(j > 1 ? dp[i-offset][j-1] : -30001), dp[i-offset][j], dp[i-offset][j+1]});
            res = val > res ? val : res;
            m_val = val > m_val ? val : m_val;
            dp[i][j] = val >= 0 ? val : -30001;
        }
    }
    cout << res << endl;
    
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    solve();
    return 0;
}