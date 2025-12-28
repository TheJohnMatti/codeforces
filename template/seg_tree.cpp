template<typename T>
struct SegTree {
    int n;
    T ID;
    function<T(T, T)> merge;
    vector<T> tree;

    SegTree(int _n, T _ID, function<T(T, T)> _merge) : n(_n), ID(_ID), merge(_merge) {
        tree.assign(4 * n, ID);
    }

    void build(const vector<T>& a, int node, int l, int r) {
        if (l == r) {
            tree[node] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(a, 2 * node, l, mid);
        build(a, 2 * node + 1, mid + 1, r);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int idx, T val, int node, int l, int r) {
        if (l == r) {
            tree[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) update(idx, val, 2 * node, l, mid);
        else update(idx, val, 2 * node + 1, mid + 1, r);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    T query(int ql, int qr, int node, int l, int r) {
        if (ql > r || qr < l) return ID;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return merge(query(ql, qr, 2 * node, l, mid), query(ql, qr, 2 * node + 1, mid + 1, r));
    }

    void build(const vector<T>& a) { build(a, 1, 0, n - 1); }
    void update(int idx, T val) { update(idx, val, 1, 0, n - 1); }
    T query(int l, int r) { return query(l, r, 1, 0, n - 1); }
};