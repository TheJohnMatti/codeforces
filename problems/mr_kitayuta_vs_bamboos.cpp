#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// Structure to manage heap elements
struct BambooState {
    ll death_day;
    int index;
    
    // Min-heap: smallest death_day on top
    bool operator>(const BambooState& other) const {
        return death_day > other.death_day;
    }
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n, m, k;
    ll p;
    if (!(cin >> n >> m >> k >> p)) return 0;

    vector<ll> h(n), a(n);
    ll max_h = 0, max_a = 0;
    for(int i=0; i<n; i++){
        cin >> h[i] >> a[i];
        max_h = max(max_h, h[i]);
        max_a = max(max_a, a[i]);
    }

    // Binary Search Range
    // Lower bound 0, Upper bound: max initial height + max possible growth
    ll l = 0, r = max_h + (ll)m * max_a;
    ll ans = r;

    // Buffers for the check function to avoid re-allocation
    // cuts[i] stores how many times we hit bamboo i
    vector<int> cuts(n);
    
    while(l <= r){
        ll mid = (l + r) / 2;
        fill(cuts.begin(), cuts.end(), 0);
        priority_queue<BambooState, vector<BambooState>, greater<BambooState>> pq;
        
        bool possible = true;
        

        if(possible){
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    cout << ans << endl;

    return 0;
}