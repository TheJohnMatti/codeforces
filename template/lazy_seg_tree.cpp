template<typename T>
struct SegTree {
    int n;
    vector<T> tree, lazy_add, lazy_set;
    vector<bool> active_set;

    SegTree(int _n) : n(_n) {
        tree.assign(4 * n, 0);
        lazy_add.assign(4 * n, 0);
        lazy_set.assign(4 * n, 0);
        active_set.assign(4 * n, false);
    }

    void push(int node, int l, int r) {
        int mid = (l + r) / 2;
        int left = 2 * node, right = 2 * node + 1;

        if (active_set[node]) {
            lazy_set[left] = lazy_set[node];
            tree[left] = lazy_set[node] * (mid - l + 1);
            active_set[left] = true;
            lazy_add[left] = 0;

            lazy_set[right] = lazy_set[node];
            tree[right] = lazy_set[node] * (r - mid);
            active_set[right] = true;
            lazy_add[right] = 0;

            active_set[node] = false;
        }

        if (lazy_add[node] != 0) {
            if (active_set[left]) lazy_set[left] += lazy_add[node];
            else lazy_add[left] += lazy_add[node];
            tree[left] += lazy_add[node] * (mid - l + 1);

            if (active_set[right]) lazy_set[right] += lazy_add[node];
            else lazy_add[right] += lazy_add[node];
            tree[right] += lazy_add[node] * (r - mid);

            lazy_add[node] = 0;
        }
    }

    void range_set(int ql, int qr, T val, int node, int l, int r) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            tree[node] = val * (r - l + 1);
            lazy_set[node] = val;
            active_set[node] = true;
            lazy_add[node] = 0;
            return;
        }
        push(node, l, r);
        int mid = (l + r) / 2;
        range_set(ql, qr, val, 2 * node, l, mid);
        range_set(ql, qr, val, 2 * node + 1, mid + 1, r);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void range_add(int ql, int qr, T val, int node, int l, int r) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            tree[node] += val * (r - l + 1);
            if (active_set[node]) lazy_set[node] += val;
            else lazy_add[node] += val;
            return;
        }
        push(node, l, r);
        int mid = (l + r) / 2;
        range_add(ql, qr, val, 2 * node, l, mid);
        range_add(ql, qr, val, 2 * node + 1, mid + 1, r);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    T query(int ql, int qr, int node, int l, int r) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return tree[node];
        push(node, l, r);
        int mid = (l + r) / 2;
        return query(ql, qr, 2 * node, l, mid) + query(ql, qr, 2 * node + 1, mid + 1, r);
    }

    void range_set(int l, int r, T val) { range_set(l, r, val, 1, 0, n - 1); }
    void range_add(int l, int r, T val) { range_add(l, r, val, 1, 0, n - 1); }
    T query(int l, int r) { return query(l, r, 1, 0, n - 1); }
};