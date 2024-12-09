/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/1096

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

// when this is multipled with F0, it gives {Fn-4, Fn-3, Fn-2, Fn-1, Fn, Fn+1}
vvl FIB6BASE = {
    {0, 1, 0, 0, 0, 0}, 
    {0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1}
};

void printmat(vvl mat, int setwval=3) {
    int m = mat.size(), n = mat[0].size();
    putl("======");
    setw(setwval), put("*"); rep(i, n) setw(setwval), put(i); putl();
    rep(i, m) {
        setw(setwval), put(i);
        rep(j, n) {
            setw(setwval), put(mat[i][j]);
        }
        putl();
    }
}

vvl matmul(vvl a, vvl b) {
    int m = a.size(), n = a[0].size(), p = b[0].size();
    if(n != (int) b.size()) {
        putl("matmul error: a.size() != b[0].size()");
        return {};
    }
    vvl c(m, vl(p, 0));
    rep(i, m) rep(j, p) rep(k, n) {
        (c[i][j] += (a[i][k] * b[k][j]) % MD) %= MD;
    }
    return c;
}

vvl matpow(vvl a, LL p) {
    int m = a.size(), n = a[0].size();
    vvl res(m, vl(n, 0));
    rep(i, m) res[i][i] = 1;
    while(p > 0) {
        if(p & 1) res = matmul(res, a);
        a = matmul(a, a);
        p >>= 1;
    }
    return res;
}

int main(int argc, char **argv) {
    cin.tie(0)->sync_with_stdio(false);

    LL n; see(n);

    // recurrence relation for this problem is:
    // dp(n) = dp(n-6) + dp(n-5) + dp(n-4) + dp(n-3) + dp(n-2) + dp(n-1)
    // Fn = T * Fn-1 -> in matrix form
    // if linear recurrence relation, then we can use matrix exponentiation to solve it.
    // as Fn = T^(n-1) * F0, where F0 is the initial state of the recurrence relation.
    vvl v = {{1}, {2}, {1+1+2}, {1+4+2+1}, {1+8+4+2+1}, {1+16+8+4+2+1}};
    vvl mat = matmul(matpow(FIB6BASE, n-1), v);

    #if DEBUG == 1
    printmat(mat);
    #endif

    LL ans = mat[0][0];
    putl(ans);

    return 0;
}
