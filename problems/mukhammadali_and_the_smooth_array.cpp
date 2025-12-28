#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> nums(n);
    vector<int> nums_s(n);
    vector<int> costs(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        nums_s[i] = nums[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> costs[i];
    }
    if (n == 1) {
        cout << 0 << endl;
        return;
    }
    sort(nums_s.begin(), nums_s.end());
    unordered_map<int, int> key;
    for (int i = 0; i < n; ++i) {
        key[nums_s[i]] = i;
    }

    

    
    int res = *min_element(dp.begin(), dp.end());
    cout << res << endl;
}

int main() {
    // cin.tie(nullptr); cout.tie(nullptr);
    // ios::sync_with_stdio(false);


    int t;
    cin >> t;
    for (int i = 0; i < t; i++) solve();
    return 0;

}