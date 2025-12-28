#include <bits/stdc++.h>
using namespace std;


const int N = 100005;

// DSU
vector<int> ran(N+1, 1);
vector<int> par(N+1);

int find(int n) {
    if (par[n] == n) return n;
    par[n] = find(par[n]);
    return par[n];
}



void merge(int n1, int n2) {
    int p1 = find(n1), p2 = find(n2);

    if (p1 == p2) return;
    if (ran[p1] > ran[p2]) {
        par[p2] = p1;
        ran[p1] += ran[p2];
    }
    else {
        par[p1] = p2;
        ran[p2] += ran[p1];
    }

}

void dfs1(int node, vector<vector<int>> &adj, vector<bool> &seen, vector<vector<int>> &children) {
    seen[node] = true;
    for (auto &i : adj[node]) {
        if (!seen[i]) {
            children[node].push_back(i);
            dfs1(i, adj, seen, children);
        }
    }
}

bool dfs2(int node, vector<vector<int>> &children, vector<int> &parity, vector<vector<int>> &new_children) {
    if (!parity[node] && children[node].size() == 0) {
        return false;
    }
    bool res = (bool)parity[node];
    for (auto &i : children[node]) {
        bool v = dfs2(i, children, parity, new_children);
        if (v) new_children[node].push_back(i);
        res |= v;
    }
    return res;

}

void dfs3(int node, vector<vector<int>> &children, vector<int> &parity, vector<int> &path, bool ret) {
    path.push_back(node);
    parity[node] ^= 1;
    if (ret) return;
    if (children[node].size() == 0) return;
    for (auto &i : children[node]) {
        dfs3(i, children, parity, path, false);
        path.push_back(node);
        parity[node] ^= 1;
        if (parity[i]) {
            dfs3(i, children, parity, path, true);
            path.push_back(node);
            parity[node] ^= 1;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    vector<vector<int>> adj(n+1);
    vector<int> parity(n+1);

    for (int i = 0; i < m; i++) {
        int t, f;
        cin >> t >> f;
        edges[i] = {t, f};
        adj[t].push_back(f);
        adj[f].push_back(t);
    }
    for (int i = 1; i < n+1; i++) {
        cin >> parity[i];
    }
    for (int i = 1; i < n+1; i++) {
        par[i] = i;
    }
    for (auto &[t, f] : edges) {
        merge(t, f);
    }
    int target = -1;

    vector<int> target_nodes;
    for (int i=1; i < n+1; i++) {
        if (parity[i]) {
            int p = find(i);
            if (target != -1 && p != target) {
                cout << -1 << endl;
                return 0;
            }
            target = p;
            target_nodes.push_back(i);
        }
    }

    if (target == -1) {
        cout << 0 << endl;
        return 0;
    }

    vector<vector<int>> children(n+1);
    vector<bool> seen(n+1);
    vector<int> path;
    dfs1(target_nodes[0], adj, seen, children);
    vector<vector<int>> new_children(n+1);
    dfs2(target_nodes[0], children, parity, new_children);
    dfs3(target_nodes[0], new_children, parity, path, false);

    int offset = 0;

    if (parity[target_nodes[0]]) {
        offset = 1;
    }
    cout << (int)(path.size() - offset) << endl;
    for (int i=offset; i < path.size(); i++) {
        cout << path[i] << " ";
    }
    cout << endl;    
    return 0;
}