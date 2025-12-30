#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
 
inline int readInt() {
    int x = 0;
    bool neg = false;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') neg = true;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return neg ? -x : x;
}
 
struct pt {
    long long x, y;
    pt() : x{0}, y{0} {};
    pt(long long x, long long y) : x{x}, y{y} {}
    bool operator == (pt const& t) const {
        return x == t.x && y == t.y;
    }
};
 
long long orientation(pt a, pt b, pt c) {
    long long v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < 0) return -1; 
    if (v > 0) return +1; 
    return 0;
}
 
bool cw(pt a, pt b, pt c) {
    long long o = orientation(a, b, c);
    return o < 0;
}
 
double segment_area(double r, double h) {
    return r*r*acos((r-h)/r)-(r-h)*sqrt(2*r*h-h*h);
}
 
void solve() {
    int n = readInt();
    int r = readInt();
    vector<pt> points(n);
    long long min_y = 4e18, min_x = 4e18;
    int tgt_idx = -1;
    for (int i=0; i<n; i++) {
        points[i].x = readInt();
        points[i].y = readInt();
        if (points[i].y < min_y || (points[i].y == min_y && points[i].x < min_x)) {
            min_y = points[i].y;
            min_x = points[i].x;
            tgt_idx = i;
        }
    }
    points.push_back(pt(0, 0));
    if (min_y > 0 || (min_y == 0 && min_x > 0)) {min_y = 0; min_x = 0;}
 
    pt p0 = pt(min_x, min_y);
 
    sort(points.begin(), points.end(), [&] (const pt &a, const pt &b) {
        long long o = orientation(p0, a, b);
        if (o == 0)
            return (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y)
                < (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
        return o < 0;
    });
    vector<pt> st;
    st.reserve(n+1);
    for (int i=0; i < (int)points.size(); i++) {
        while (st.size() > 1 && !cw(st[st.size()-2], st.back(), points[i])) st.pop_back();
        st.push_back(points[i]);
    }
    for (auto &p : st) if (p.x == 0 && p.y == 0) {
        cout << M_PI * r * r / 2 << "\n";
        return;
    }
    int sz = st.size();
    double min_dist = 1e9;
    auto handle = [&](pt &p1, pt &p2) -> void {
        double cross = abs(p1.x * p2.y - p2.x * p1.y);
        double dx = p1.x - p2.x;
        double dy = p1.y - p2.y;
        double base = sqrt(dx*dx + dy*dy);
        double h = cross / base;
        if (h < min_dist) min_dist = h;
    };
    for (int i=0; i<sz; i++) {
        handle(st[i], st[(i+1)%sz]);
    }
    cout << segment_area(r, r-min_dist) << "\n";
}
 
int main() { 
    cout << fixed << setprecision(10);
    solve();
    return 0;
}