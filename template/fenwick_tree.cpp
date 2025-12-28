using ll = long long;
class FenwickTree {
    
    vector<ll> arr;
    int n;
    public:
    FenwickTree(int n) {
        this->n = n;
        arr.assign(n+1, 0);
    }

    void add(int i, int v) {
        i++;
        while (i <= n) {
            arr[i] += v;
            i += (i & -i);
        }
    }

    ll query(int i) {
        i++;
        ll res = 0;
        while (i > 0) {
            res += arr[i];
            i -= (i & -i);
        }
        return res;
    }

}