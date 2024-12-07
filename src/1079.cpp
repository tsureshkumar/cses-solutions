/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/1079

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

#define LIM 1001
int NCR[LIM][LIM];
int fact[1000001];

LL modpow(LL x, LL y, LL mod) {
    LL res = 1;
    while(y > 0) {
        if(y%2 == 1) res = (res*x)%mod;
        x = (x*x)%mod;
        y /= 2;
    }
    return res;
}

int main(int argc, char **argv) {
    cin.tie(0)->sync_with_stdio(false);

    NCR[0][0] = 1;
    repr(i, 1, LIM) NCR[i][0] = 1, NCR[0][i] = 1;
    repr(i, 1, LIM) repr(j, 1, LIM) NCR[i][j] = ((LL)NCR[i-1][j] + NCR[i][j-1])%MD;

    fact[0] = 1;
    repr(i, 1, 1000001) fact[i] = ((LL)fact[i-1]*i)%MD;

    auto ncr = [&](int n, int r) {
        if(r > n) return 0;
        return NCR[n-r][r];
    };

    unordered_map<int, unordered_map<int, int>> memo;
    function<int(int, int)> ncr_rec = [&](int n, int r) -> int {
        if(r > n) return 0;
        if(n < LIM && r < LIM) return ncr(n, r);
        if(r == 0 || r == n) return 1;

        int &ret = memo[n][r];
        if(ret != 0) return ret;

        LL res = 0;
        res += ncr_rec(n-1, r-1);
        res += ncr_rec(n-1, r);
        return ret = res%MD;
    };

    auto inv = [&](int x) {
        return modpow(x, MD-2, MD);
    };

    auto ncr_fact = [&](int n, int r) {
        LL res = fact[n];
        (res *= inv(fact[r])) %= MD;
        (res *= inv(fact[n-r])) %= MD;
        return res;
    };

    int q; see(q);
    while(q--) {
        LL n, r; see(n, r);
        LL res = ncr_fact(n, r);
        putl(res);
    }

    return 0;
}
