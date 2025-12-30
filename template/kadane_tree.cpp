#include <bits/stdc++.h>
using namespace std;

struct Kadanetree {
    using ll = long long;
    int n;
    vector<ll> pref, suf, best, sum;

    Kadanetree(int _n) : n(_n) {
        pref.assign(4*n, 0);
        suf.assign(4*n, 0);
        best.assign(4*n, 0);
        sum.assign(4*n, 0);
    }

    inline void pull(int v) {
        sum[v]  = sum[v<<1] + sum[v<<1|1];
        pref[v] = max(pref[v<<1], sum[v<<1] + pref[v<<1|1]);
        suf[v]  = max(suf[v<<1|1], sum[v<<1|1] + suf[v<<1]);
        best[v] = max({best[v<<1], best[v<<1|1], suf[v<<1] + pref[v<<1|1]});
    }

    void build(const vector<ll>& a, int v, int l, int r) {
        if (l == r) {
            sum[v] = pref[v] = suf[v] = best[v] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(a, v<<1, l, m);
        build(a, v<<1|1, m+1, r);
        pull(v);
    }

    void update(int idx, ll val, int v, int l, int r) {
        if (l == r) {
            sum[v] = pref[v] = suf[v] = best[v] = val;
            return;
        }
        int m = (l + r) >> 1;
        if (idx <= m) update(idx, val, v<<1, l, m);
        else update(idx, val, v<<1|1, m+1, r);
        pull(v);
    }

    ll q_pref, q_suf, q_best, q_sum;

    void query(int ql, int qr, int v, int l, int r) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            if (q_sum == (ll)4e18) {
                q_sum  = sum[v];
                q_pref = pref[v];
                q_suf  = suf[v];
                q_best = best[v];
            } else {
                q_best = max({q_best, best[v], q_suf + pref[v]});
                q_pref = max(q_pref, q_sum + pref[v]);
                q_suf  = max(suf[v], sum[v] + q_suf);
                q_sum += sum[v];
            }
            return;
        }
        int m = (l + r) >> 1;
        query(ql, qr, v<<1, l, m);
        query(ql, qr, v<<1|1, m+1, r);
    }

    ll query(int l, int r) {
        q_sum = (ll)4e18;
        query(l, r, 1, 0, n-1);
        return q_best;
    }

    void build(const vector<ll>& a) { build(a, 1, 0, n-1); }
    void update(int idx, ll val) { update(idx, val, 1, 0, n-1); }
};
