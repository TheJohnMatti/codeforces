#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MOD = 998244353;
int buckets[8][62][62];
int dp[8][62][62][62];

bool is_palindrome(string s) {
    int p1=0, p2=s.size()-1;
    while (p1 < p2) {if (s[p1]!=s[p2]) return false;p1++;p2--;} 
    return true;
}

int get_idx(char c) {
    if ('a' <= c && c <= 'z') return c-'a';
    if ('A' <= c && c <= 'Z') return 26+c-'A';
    if ('0' <= c && c <= '9') return 52+c-'0';
    return -1;
}

int permutation_factor(int i, int j, int k, int l) {
    if (i == j && j == k && k == l) return 1;
    if (j == k) return (i == j || k == l) ? 4 : 12;
    if (i == j && k == l) return 6;
    if (i == j || k == l) return 12;
    return 24;
}
 
int subproblem(int arr[62][62], int dp[62][62][62]) {
    ll res = 0;
    for (int i=0; i<62; i++) 
        for (int j=0; j<62; j++) 
            for (int k=j; k<62; k++) 
                for (int l=k; l<62; l++) {
                    ll v = (ll)arr[i][j]*arr[i][k] % MOD;
                    v = v * arr[i][l] % MOD;
                    dp[j][k][l] = (dp[j][k][l] + v) % MOD;
                }
    for (int i=0; i<62; i++) 
        for (int j=i; j<62; j++) 
            for (int k=j; k<62; k++) 
                for (int l=k; l<62; l++) {
                    ll v = (ll)dp[i][j][k] * dp[j][k][l] % MOD;
                    v = v * dp[i][k][l] % MOD;
                    v = v * dp[i][j][l] % MOD;
                    v = v * permutation_factor(i, j, k, l) % MOD;
                    res = (res + v) % MOD;
                }
    return res;
}


int main() {
    int n;
    cin >> n;
    vector<string> words(n);
    unordered_set<string> s;
    for (auto &i:words) {
        cin >> i;
        s.insert(i);
    }
    for (auto &i:words) {
        int idx_l = get_idx(i[0]), idx_r = get_idx(i[i.size()-1]);
        buckets[i.size()-3][idx_l][idx_r]++;
        string cpy;
        cpy.resize(i.size());
        reverse_copy(i.begin(), i.end(), cpy.begin());
        if (!is_palindrome(i) && !s.count(cpy)) buckets[i.size()-3][idx_r][idx_l]++;
    }

    ll res=0;
    for (int i=0; i<8; i++) res = (res + subproblem(buckets[i], dp[i])) % MOD;

    cout << res << endl;

    return 0;
}