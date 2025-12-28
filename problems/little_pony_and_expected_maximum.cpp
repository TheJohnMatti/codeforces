#include <bits/stdc++.h>

using namespace std;


double iterate(double m, double n) {
    if (m == 0) {
        return 0;
    }
    double prob_no_m = pow((m-1) / m, n);

    return (1-prob_no_m) * m + prob_no_m * iterate(m-1, n);
}

int main() {



    int m, n;
    cin >> m >> n;
    if (m == 1) {
        cout << 1 << endl;
        return 0;
    }

    double prev = 1, cur = 1;
    for (double i = 2; i <= m; i++) {
        prev = cur;
        double prob_no_i = pow((i-1)/i, n);
        cur = (1-prob_no_i) * i + prob_no_i * prev;
    }

    cout << cur << endl;


    return 0;
    
}