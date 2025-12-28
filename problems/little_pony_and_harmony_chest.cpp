#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int &x: a) cin >> x;

    vector<int> primes = {2,3,5,7,11,13,17,19,23,29};
    vector<int> numMask(59,0);
    for(int x=1; x<=58; x++){
        int mask = 0;
        for(int i=0; i<primes.size(); i++){
            if(x % primes[i] == 0) mask |= (1<<i);
        }
        numMask[x] = mask;
    }

    const int INF = 1e9;
    int maxMask = 1<<primes.size();
    vector<vector<int>> dp(n+1, vector<int>(maxMask, INF));
    vector<vector<int>> par(n+1, vector<int>(maxMask,-1));

    dp[0][0] = 0;

    for(int i=0; i<n; i++){
        for(int mask=0; mask<maxMask; mask++){
            if(dp[i][mask]==INF) continue;
            for(int b=1; b<=58; b++){
                int m = numMask[b];
                if(mask & m) continue; // conflict in primes
                int newMask = mask | m;
                int cost = dp[i][mask] + abs(a[i]-b);
                if(cost < dp[i+1][newMask]){
                    dp[i+1][newMask] = cost;
                    par[i+1][newMask] = b;
                }
            }
        }
    }

    // find minimal sum
    int bestMask = 0;
    for(int mask=0; mask<maxMask; mask++){
        if(dp[n][mask] < dp[n][bestMask]) bestMask = mask;
    }

    // reconstruct
    vector<int> res(n);
    int mask = bestMask;
    for(int i=n; i>=1; i--){
        res[i-1] = par[i][mask];
        mask ^= numMask[res[i-1]]; // remove primes of chosen number
    }

    for(int i=0;i<n;i++){
        cout << res[i] << " \n"[i==n-1];
    }
}
