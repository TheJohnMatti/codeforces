/* IDEMPOTENT OPERATIONS ONLY ! */
template<typename T>
struct SparseTable {
    int n, k;
    vector<vector<T>> st;
    function<T(T, T)> merge;

    SparseTable(const vector<T>& a, function<T(T, T)> _merge) : merge(_merge) {
        n = a.size();
        k = __lg(n) + 1;
        st.assign(k, vector<T>(n));
        for (int i = 0; i < n; i++) st[0][i] = a[i];
        for (int j = 1; j < k; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                st[j][i] = merge(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }

    T query(int l, int r) {
        int j = __lg(r - l + 1);
        return merge(st[j][l], st[j][r - (1 << j) + 1]);
    }
};