/**
 * G. A New Beginning
 * Solution using Slope Trick and Coordinate Transformation
 * * Transformation:
 * S = x + y
 * v = x - y
 * Cost becomes 1/2 * |v_path - v_potato|
 * Path constraint: |v_next - v_prev| <= S_next - S_prev
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;

struct Potato {
    ll S, v;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if (!(cin >> n)) return 0;
    vector<Potato> pots(n);
    for (int i = 0; i < n; ++i) {
        ll x, y;
        cin >> x >> y;
        pots[i].S = x + y;
        pots[i].v = x - y;
    }
    sort(pots.begin(), pots.end(), [](const Potato& a, const Potato& b) {
        return a.S < b.S;
    });
    priority_queue<ll> L; 
    priority_queue<ll, vector<ll>, greater<ll>> R;
    L.push(0);
    R.push(0);

    ll lazy_L = 0;
    ll lazy_R = 0;
    ll min_cost = 0;
    ll prev_S = 0;

    for (int i = 0; i < n; ) {
        ll curr_S = pots[i].S;
        ll diff = curr_S - prev_S;
        lazy_L -= diff;
        lazy_R += diff;
        while (i < n && pots[i].S == curr_S) {
            ll v = pots[i].v;
            L.push(v - lazy_L);
            R.push(v - lazy_R);
            ll l_top = L.top() + lazy_L;
            ll r_top = R.top() + lazy_R;
            if (l_top > r_top) {
                min_cost += (l_top - r_top);
                L.pop();
                R.pop();
                L.push(r_top - lazy_L);
                R.push(l_top - lazy_R);
            }
            
            i++;
        }
        prev_S = curr_S;
    }
    cout << min_cost / 2 << endl;

    return 0;
}