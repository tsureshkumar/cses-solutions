/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/2187

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

const int MX = 2*1e6;
vl fact(MX+1, 1);

LL modpow(LL x, LL y) {
    LL res = 1;
    while(y > 0) {
        if(y & 1) res = (res * x) % MD;
        x = (x * x) % MD;
        y >>= 1;
    }
    return res;
}

LL inv(LL x) {
    return modpow(x, MD-2);
}   

LL ncr(LL n, LL r) {
    LL res = fact[n];
    (res *= inv(fact[r])) %= MD;
    (res *= inv(fact[n-r])) %= MD;
    (res += MD) %= MD;
    return res;
}

int main(int argc, char **argv) {
    cin.tie(0)->sync_with_stdio(false);

    repr(i, 1, MX+1) {
        (fact[i] = (fact[i-1] * i)) %= MD;
        (fact[i] += MD) %= MD;
    }

    int n; see(n);
    string s; see(s); // prefix

    int open = 0, close = 0;
    for(auto x: s) {
        if(x == '(') open++;
        else {
            if(++close > open) { // can't fix a close before an open
                putl(0);
                return 0;
            }
        }
    }

    // modified catalan recurrence based on previous term
    // C(n) = C(n-1) * (2*n - 1) (2*n) / (n * (n + 1))
    // the intution is after n-1 valid sequences, we can add a pair of brackets
    // to the end of any sequence in (2*n - 1) * (2) ways, and then divide by
    // (n + 1) to elliminate invalid sequences.
    // 
    // auto solve = [&](LL balance, LL n) -> LL {
    //     LL rem_pairs = (n-balance)/2;
    //     LL ans = 1;
    //     repr(i, 1, rem_pairs+1) {
 
    //         LL a1 = (2 * i + balance - 1)%MD;
    //         LL a2 = (2*i + balance)%MD;
 
    //         LL num = (a1*a2)%MD;
    //         LL den = (i * (i+balance+1))%MD;
 
    //         LL term = (num * inv(den))%MD;
    //         (term *= ans) %= MD;
 
    //         ans = term;
    //         (ans += MD) %= MD;
    //     }
    //     return ans;

    // };

    // Alternative solution using Dyck's formula
    auto solveDyck = [&](LL h, LL n) -> LL {
        if((n + h) & 1) return 0;  // Must be even to reach zero
        
        LL k = (n - h) /2;     // number of up steps needed
        LL m = k + h;          // number of down steps needed

        // Using the formula: C(n,k) - C(n,k-1)
        if(k > n || m > n || k < 0 || m < 0) return 0;
        LL res = ncr(n, k);
        if(k > 0) (res -= ncr(n, k-1) + MD) %= MD;
        (res += MD) %= MD;

        return res;
    };

    // recursive solution
    // equivalent to Dyck paths from height h reaching to 0
    // in n steps
    // If you start at height h, you can either go up or down.
    // you go up by addinga '(' or go down by adding a ')'.
    // function<LL(LL, LL)> solve2 = [&](LL h, LL n) -> LL {
    //     if(h == 0 && n == 0) return 1;
    //     if(h > 0 && n == 0) return 0;
    //     if(h == 0) return solve2(1, n-1);
    //     return solve2(h-1, n-1) + solve2(h+1, n-1);
    // };

    LL balance = open - close;
    LL m = n - s.size();
    LL rem_pairs = (m - balance)/2;

    if ( ((m-balance)&1) || balance < 0 || m < 0 || rem_pairs < 0 || rem_pairs > m/2) {
        putl(0);
        return 0;
    }

    LL ans = 0;
    
    // ans = solve(balance, m);
    // putl(ans);

    ans = solveDyck(balance, m);
    putl(ans);

    // ans = solve2(balance, m);
    // putl(ans);

    return 0;
}
