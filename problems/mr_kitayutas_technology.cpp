#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class UF {
    public:

    vector<int> rank;
    vector<int> par;

    UF(int n) {
        rank.resize(n+1);
        par.resize(n+1);
        for (int i = 0; i < n+1; i++) {
            rank[i] = 1;
            par[i] = i;
        }
    }


    int find(int n) {
        while (par[n] != n) {
            par[n] = par[par[n]];
            n = par[n];
        }
        return n;
    }

    pair<int, int> merge(int n1, int n2) {
        int p1 = find(n1), p2 = find(n2);
        if (p1 == p2) {
            return {p1, p1};
        }

        else if (rank[p1] > rank[p2]) {
            rank[p1] += rank[p2];
            par[p2] = p1;
            return {p1, p2};
        } 
        else {
            rank[p2] += rank[p1];
            par[p1] = p2;
            return {p2, p1};
        }

    }
};

unordered_set<int> visiting;
unordered_set<int> visited;
bool fail;

void dfs(int node, vector<vector<int>> &adj) {

    if (fail) return;
    if (visited.count(node)) return;

    if (visiting.count(node)) {
        fail = true;
        return;
    }

    visiting.insert(node);
    for (auto &i : adj[node]) {
        dfs(i, adj);
    }
    visiting.erase(node);
    visited.insert(node);
}

bool top_sort(vector<vector<int>> &edges, vector<vector<int>> &adj) {
    fail = false;
    visiting.clear();
    visited.clear();
    for (auto e : edges) {
        dfs(e[0], adj); dfs(e[1], adj);
    }
    return !fail;
}

int main() {

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n+1);
    vector<vector<vector<int>>> buckets(n+1);

    UF uf(n);

    for (int i = 0; i < m; i++) {
        int to, from;
        cin >> to >> from;
        adj[from].push_back(to);
        pair<int, int> par = uf.merge(to, from);
        if (par.first != par.second) {
            for (int j = 0; j < buckets[par.second].size(); j++) {
                buckets[par.first].push_back(buckets[par.second][j]);
            }
            buckets[par.second].clear();
        }
        buckets[par.first].push_back({to, from});
    }
    int res = 0;
    for (int i = 1; i < n+1; i++) {
        if (buckets[i].size() == 0) continue;
        if (top_sort(buckets[i], adj)) {
            res += uf.rank[i] - 1;
        } else {
            res += uf.rank[i];
        }
    }
    cout << res << endl;
    return 0;
}