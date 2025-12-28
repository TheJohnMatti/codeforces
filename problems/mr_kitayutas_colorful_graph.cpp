#include <bits/stdc++.h>

using namespace std;


class DSU {

    int par[101];
    int rank[101];

    public:
    DSU() {
        for (int i=0; i < 101; i++) {
            rank[i] = 1;
            par[i] = i;
        }
    }

    int find(int n) {
        if (par[n] != n) par[n] = find(par[n]);
        return par[n];
    }

    void merge(int n1, int n2) {
        int p1=find(n1), p2=find(n2);

        if (p1 == p2) return;

        if (rank[p1] > rank[p2]) {
            par[p2] = p1;
            rank[p1] += rank[p2];
        } else {
            par[p1] = p2;
            rank[p2] += rank[p1];
        }
    }
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    unordered_map<int, DSU> mp;

    for (int i=0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        mp[c].merge(a, b);
    }

    int q;
    cin >> q;
    for (int i=0; i < q; i++) {
        int cnt = 0;
        int n1, n2;
        cin >> n1 >> n2;
        for (auto &[k, v] : mp) {
            if (v.find(n1) == v.find(n2)) cnt++; 
        }
        cout << cnt << endl;
    }

    return 0;
}
