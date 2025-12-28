#include <bits/stdc++.h>

using namespace std;

int dfs(int n, vector<vector<int>> &children, vector<int> &dp) {
    int o1 = children[n].size();
    if (o1==0) return 0;
    vector<int> options;
    for (int &i : children[n]) {
        options.push_back(dfs(i, children, dp));
    }
    dp[n] = max({o1, *max_element(options.begin(), options.end()) + o1 - 1});
    return dp[n];
}
int main() {
    int n; 
    cin >> n;
    vector<vector<int>> children(n);
    vector<bool> is_child(n, false);
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        if (is_child[a]) {children[a].push_back(b); is_child[b] = true;}
        else if (is_child[b]) {children[b].push_back(a); is_child[a] = true;}
        else {children[min(a,b)].push_back(max(a,b)); is_child[max(a,b)] = true;}
    }
    vector<int> dp(n, 0);

    int res = dfs(0, children, dp);

    for (int i=0; i < n; i++) {
        cout << i << " " << dp[i] << endl;
    }


    cout << res << endl;
    return 0;
}