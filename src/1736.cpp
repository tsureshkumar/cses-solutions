/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/1736

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

struct LazySegmentTree {
    // lazy is always for the child nodes and for propagation
    vl tree, lazy, diff;
    LazySegmentTree (int n) {
        tree.resize (4*n+1, 0);
        lazy.resize (4*n+1, 0);
        diff.resize (4*n+1, 0);
    }
        void pushpoly (int v, int tl, int tr) {
        if (lazy[v] != 0) {
            int n = tr-tl+1;
            int d = diff[v];
            LL sum = (n * (2LL * lazy[v] + (n-1LL) * d)) / 2LL;
            tree[v] += sum;

            if (tl != tr) {
                int mid = (tr - tl) / 2 ;
                int left = lazy[v], right = lazy[v] + (mid+1) * 1LL * d;
                lazy[v*2] += left;
                diff[v*2] += d;
                lazy[v*2+1] += right;
                diff[v*2+1] += d;
            }
            lazy[v] = 0;
            diff[v] = 0;
        }
    }
    void update (int v, int tl, int tr, int l, int r, int add) {
        pushpoly (v, tl, tr);
        if (tr < l || tl > r) return;
        if (l <= tl && tr <= r) {
            lazy[v] += add;
            diff[v] += 1;
            pushpoly (v, tl, tr);
            return;
        }
        int tm = (tl + tr) / 2;
        update (v*2, tl, tm, l, r, add);
        update (v*2+1, tm+1, tr, l, r, add);
        tree[v] = tree[v*2] + tree[v*2+1];
    }
    LL query (int v, int tl, int tr, int l, int r) {
        pushpoly (v, tl, tr);

        if (tr < l || tl > r) return 0;

        if (l <= tl && tr <= r) return tree[v];
        int tm = (tl + tr) / 2;
        return query (v*2, tl, tm, l, r) + query (v*2+1, tm+1, tr, l, r);
    }
    void set (int v, int tl, int tr, int l, int r, int x) {
        update (v, tl, tr, l, r, x);
    }

    void poly_increment (int v, int tl, int tr, int l, int r, int sequence_start) {
        pushpoly (v, tl, tr);
        if (tr < l || tl > r) return;
        if (l == tl && tr == r) {
            lazy[v] += l-sequence_start+1;
            diff[v] += 1;
            pushpoly (v, tl, tr);
            return;
        }
        int tm = (tl + tr) / 2;
        poly_increment (v*2, tl, tm, l, min(r, tm), sequence_start);
        poly_increment (v*2+1, tm+1, tr, max(l, tm+1), r, sequence_start);
        tree[v] = tree[v*2] + tree[v*2+1];
    }
};


int main(int argc, char **argv) {
    cin.tie(0)->sync_with_stdio(false);

    int n, q; see(n, q);
    vi v; seev(v, n);

    LazySegmentTree st(n);
    rep (i, n) st.update (1, 0, n-1, i, i, v[i]);

    rep (_, q) {
        int t; see(t);
        if (t == 1) { // increase by x for the range [a,b] as polynomial
            int a, b; see(a, b);
            st.poly_increment (1, 0, n-1, a-1, b-1, a-1);
        } else { // query the range [a,b]
            int a, b; see(a, b);
            putl (st.query (1, 0, n-1, a-1, b-1));
        }
    }

    return 0;
}
