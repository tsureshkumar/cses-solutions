/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/1727

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
#define LD                  long double
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

// default precision is not rounding to even, so we need to implement it
LD round_to_even(LD d) {
   long n = d * 1e6;
    auto half = 1.0l * (10 * n + 5) / 1e7;
 
    const LD eps = numeric_limits<long double>::epsilon();
    if (abs(d - half) <= eps) {
        if (n % 2 == 1)
            ++n;
        d = n / 1e6;
    }
    return d;
}

int main(int argc, char **argv) {
    cin.tie(0)->sync_with_stdio(false);

    int n, k; see(n, k);


    // P(X=x) = 1/k for uniform distribution
    // CDF F(X<=x) = x/k
    // P(max = exactly x) = P(all children receive <= x) - P(all children receive <= x-1)
    // P(max = x) = F(X<=x) - F(X<=x-1) = (x/k)^n - ((x-1)/k)^n
    // E(max) = sum(x * P(max = x)) for x = 1 to k
    // simplyfing by distributing the sum, t=x-1 and changing limits, expanding and cancelling
    // E(max) = k - 1/k^n * sigma i^n for i = 1 to k
    auto solve = [&](int n, int k) {
        LD ans = 0.0;
        rep(i, k) {
            ans += pow(i, n);
        }
        return k - ans / pow(k, n);
    };

    LD ans = solve(n, k);
    printf("%.6Lf\n", round_to_even(ans));

    #if DEBUG == 1
    printf("%.6Lf\n", round_to_even(solve(12, 49))); // 45.710377    printf("%.6Lf\n", round_to_even(solve(2, 64))); // 45.710377
    printf("%.6Lf\n", round_to_even(solve(2, 64))); // 43.164062
    printf("%.6Lf\n", round_to_even(solve(62, 81))); // 80.151085
    printf("%.6Lf\n", round_to_even(solve(7, 10))); // 9.191958
    printf("%.6Lf\n", round_to_even(solve(2, 3))); // 2.444444
    #endif
    
    return 0;
}
