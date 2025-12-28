#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (int i=0; i<m; i++) {
        cin >> edges[i].first >> edges[i].second;
        edges[i].first--; edges[i].second--;
    }

    vector<int> g(m);
    vector<int> f(m);


    cout << f[0] << endl;

    return 0;
}
