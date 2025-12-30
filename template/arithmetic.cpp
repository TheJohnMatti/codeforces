#include <bits/stdc++.h>
using namespace std;

long long modpow(long long a, long long e, long long mod) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % mod;
        a = a * a % mod;
        e >>= 1;
    }
    return r;
}

long long inverse(long long a, long long mod) {
    return modpow(a, mod - 2, mod);
}

// Modular inverse using Extended Euclid (works for any mod where gcd(a,mod)=1)
long long modinv(long long a, long long mod) {
    long long b = mod, u = 1, v = 0;
    while (b) {
        long long t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= mod;
    if (u < 0) u += mod;
    return u;
}