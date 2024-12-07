/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/2195

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <bitset>
#include <unordered_set>
#include <random>
#include <functional>
#include <iterator>

using namespace std;

//----------TEMPLATES----------
template<typename... T>
void see(T&... args) { ((cin >> args), ...);}
template<typename... T>
void put(T&&... args) { ((cout << args << " "), ...);}
template<typename... T>
void putl(T&&... args) { ((cout << args << " "), ...); cout<<"\n";}
#define error(...) { string _s = #__VA_ARGS__; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s);istream_iterator<string> _it(_ss); err(_it, __VA_ARGS__); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {cerr << *it << "=" << a << ", "; err(++it, args...);}

//----------MACROS----------
#define LL                  long long
#define INF                 ((1e9))
#define EPS                 (0.0000001)
#define PI                  (acos(-1.0))
#define MD                  (1000000007)
#define ii                  pair<int,int>
#define ll                  pair<LL,LL>
#define vii                 vector<pair<int,int> >
#define vi                  vector<int>
#define vvi                 vector<vector<int> >
#define vvii                vector<vector<ii> >
#define vl                  vector<long long>
#define vvl                 vector<vector<long long> >
#define rep(i,n)            for(int i=0, _##i=(n); i<_##i; ++i)
#define dwn(i,n)            for(int i=(n); --i>=0; )
#define ntimes(n)           while(n-- >0)
#define repr(i,l,r)         for(int i=(l), _##i=(r); i<_##i; ++i)
#define dwnr(i,l,r)         for(int i=(r), _##i=(l); --i>=_##i; )
#define repi(i,a)           for(__typeof((a).begin()) i=(a).begin(), _##i=(a).end(); i!=_##i; ++i)
#define dwni(i,a)           for(__typeof((a).rbegin()) i=(a).rbegin(), _##i=(a).rend(); i!=_##i; ++i)
#define BitLSOne(x)         ((x)&(-x))
#define BitLSOneRst(x)      ((x)&(x-1))
#define inbound(x,l,r)      (l < x && x < r)
#define inboundi(x,l,r)     (l <= x && x <= r)
#define overlaps(x,y,a,b)   ((min(y,b)-max(x,a)) > 0)
#define overlapwin(x,y,a,b) ((min(y,b)-max(x,a)))
#define all(a)              (a).begin(), (a).end()
#define bitcount            __builtin_popcount
#define gcd                 __gcd
#define INDEX(arr,ind)      (lower_bound(all(arr),ind)-arr.begin())
#define sz                  size()
#define seea(a,x,y)         for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n)           for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
#define putv(v,n,k)         { for(int i=0;i<n;i++){ setw(k); cout << v[i]; } cout << ""; }
#define sees(s,n)           for(int i=0;i<n;i++){int x; cin>>x; s.insert(x);}
#define pb                  push_back
#define fi                  first
#define se                  second
#define setpr(x)            cout<<setprecision(x)<<fixed
#define setw(x)             cout<<setw(x)<<fixed

/*debug functions*/
#if DEBUG == 1
#define HIGHLIGHT "\u001b[33m"
#define RESETHIGH "\u001b[00m"
struct debugger{template<typename T> debugger& operator ,(const T& v){std::cout<<v<<" ";return *this;}}dbg;
#define debug(...) {cout << HIGHLIGHT << #__VA_ARGS__ << ": "; dbg,__VA_ARGS__;std::cout<< RESETHIGH << std::endl;}
#define debugv(v) {cout << HIGHLIGHT; for(__typeof(v[0]) &x:v) { std::cout << x << " "; } cout << std::endl; cout << RESETHIGH;}
#else
#define debug(...) // Just strip off all debug tokens
#define debugv(...) // Just strip off all debug tokens
#define DEBUG 0
#endif

#include <complex>
typedef long long LD;
struct P { // point
    LD x, y;
    P(LL x, LL y) : x((LD)x), y((LD)y) {}
    P() : x(0), y(0) {}
    bool operator<(const P &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
    bool operator==(const P &p) const {
        return x == p.x && y == p.y;
    }
    P operator-(const P &p) const {
        return P(x-p.x, y-p.y);
    }
    LD dist2(const P &p) const {
        return (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y);
    }
    LD cross(const P &p) const {
        return x*p.y - y*p.x;
    }
    LD dot(const P &p) const {
        return x*p.x + y*p.y;
    }
    LD norm() const {
        return x*x + y*y;
    }
    LD slope() const {
        if(x == 0) return INF;
        return y / x;
    }
    static int comp(LD a, LD b) {
        return fabs(a-b) < EPS ? 0 : (a < b ? -1 : 1);
    }
    friend ostream& operator<<(ostream& os, const P& p) {
        os << (LL)p.x << " " << (LL)p.y;
        return os;
    }
};

vector<P> solve(vector<P> &points) {
    int n = points.size();
    sort(all(points));

    auto orientation = [](P o, P a, P b) -> int {
        LD res = (a-o).cross(b-o);
        // debug(o,a,b,res);
        return res ? (res > 0 ? 1 : -1) : 0;
    };

    vector<int> lower_hull;
    // build top half
    rep(i,n) {
        P p = points[i];
        int hsz = lower_hull.size();

        // turns left?
        while(hsz >= 2 && orientation(points[lower_hull[hsz-2]], points[lower_hull[hsz-1]], p) < 0) {
            // debug(i, "popping back", points[lower_hull[hsz-1]]);
            lower_hull.pop_back();
            hsz--;
        }
        lower_hull.pb(i);
    }

    vector<int> upper_hull;
    dwn(i, n) {
        P p = points[i];
        int hsz = upper_hull.size();
        while(hsz >= 2 && orientation(points[upper_hull[hsz-2]], points[upper_hull[hsz-1]], p) < 0) {
            // debug(i, "popping back", points[upper_hull[hsz-1]]);
            upper_hull.pop_back();
            hsz--;
        }
        upper_hull.pb(i);
    }

    lower_hull.pop_back();
    upper_hull.pop_back();
    vector<P> hull;    
    rep(i, lower_hull.size()) hull.pb(points[lower_hull[i]]);
    rep(i, upper_hull.size()) hull.pb(points[upper_hull[i]]);

    return hull;
}



int main(int argc, char **argv) {
    cin.tie(0)->sync_with_stdio(false);

    int n; see(n);
    vector<P> points;
    rep(i, n) {
        int x, y; see(x, y);
        points.pb(P(x, y));
    }

    vector<P> hull = solve(points);
    putl(hull.size());
    repi(p, hull) putl(p->x, p->y);

    return 0;
}
