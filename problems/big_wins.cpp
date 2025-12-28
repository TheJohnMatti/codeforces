#include <bits/stdc++.h>

using namespace std;
typedef array<int, 3> T;

class SegmentTree {
private:
    int n;
    vector<T> tree;
    vector<T> arr; 
    T merge(T a, T b) {
        int max_pref=max(a[0], a[2]+b[0]);
        int max_suf=max(b[1], b[2]+a[1]);
        int sm = a[2]+b[2];
        return {max_pref, max_suf, sm};
    }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(2 * node, start, mid);
            build(2 * node + 1, mid + 1, end);
            tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
        }
    }

    void update(int node, int start, int end, int idx, T val) {
        if (start == end) {
            arr[idx] = val;
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(2 * node, start, mid, idx, val);
            } else {
                update(2 * node + 1, mid + 1, end, idx, val);
            }
            tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
        }
    }

    T query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return T();
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        T p1 = query(2 * node, start, mid, l, r);
        T p2 = query(2 * node + 1, mid + 1, end, l, r);
        return merge(p1, p2);
    }
    public:
    SegmentTree(const std::vector<T>& input_arr) {
        n = input_arr.size();
        arr = input_arr;
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    void update_value(int idx, T val) {
        update(1, 0, n - 1, idx, val);
    }

    T query_range(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};


void solve() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (auto &i : nums) cin >> i;
    vector<int> next_smaller(n, n);
    vector<int> prev_smaller(n, -1);
    vector<vector<int>> where(n+1);
    vector<int> stack;
    for (int i=0; i<n; i++) {
        where[nums[i]].push_back(i);
        while (!stack.empty() && nums[i] < nums[stack.back()]) {
            int idx = stack.back(); stack.pop_back();
            next_smaller[idx] = i;
        }
        stack.push_back(i);
    }
    stack.clear();
    for (int i=n-1; i>-1; i--) {
        while (!stack.empty() && nums[i] < nums[stack.back()]) {
            int idx = stack.back(); stack.pop_back();
            prev_smaller[idx] = i;
        }
        stack.push_back(i);
    }
    vector<T> tree(n, {1, 1, 1});
    SegmentTree t(tree);
    int res=0, med=1;
    for (int mn=1; mn<=n; mn++) {
        bool working=true;
        while (working && med<=n) {
            working=false;
            if (med<=mn) {
                for (auto &j : where[med]) t.update_value(j, {0, 0, -1});
                med++;
                working=true;
                continue;
            }
            if (where[med].empty()) {med++; working=true; continue;}
            for (int j=0; j<where[mn].size(); j++) {
                int &idx = where[mn][j];
                int best_left=idx-1==prev_smaller[idx]?0:t.query_range(prev_smaller[idx]+1, idx-1)[1];
                int best_right=idx+1==next_smaller[idx]?0:t.query_range(idx+1, next_smaller[idx]-1)[0];
                if (best_left+best_right-1 >= 0) {
                    working=true;
                    res = max(res, med-mn);
                    for (auto &j : where[med]) t.update_value(j, {0, 0, -1});
                    med++;
                    break;
                }  else {
                    idx=where[mn].back();
                    where[mn].pop_back();
                    j--;
                }
            }
        }
    }
    cout << res << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int t; 
    cin >> t;
    while (t--) solve();



    return 0;
}