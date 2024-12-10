/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/1099

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
#include <cassert>

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

int mex(set<int> s) {
    int i = 0;
    while(s.count(i)) i++;
    return i;
}

unordered_map<int, int> memo;
int mkgrundy(int n) {
    if(n == 9) return 0;
    if(memo.count(n)) return memo[n];
    // debug(n);
    set<int> s;
    for(int i = 1, k=10; i < ceil(log10(n)); i++, k*=10) {
        int d = (n/k)%10;
        if(d == 0) continue;
        int left = n / (k*10);
        int right = n % (k*10);
        repr(j, 1, d+1) {
            int next = (left*(k*10) + (right-9*(k/10)*j));
            int gn = mkgrundy(next);
            // debug(n, i, k, left, right, next, gn);
            s.insert(gn);
        }
    }
    memo[n] = mex(s);
    // debug(n, memo[n]);
    return memo[n];
}

// key insight:
//    Analysing sample patterns, it is observed that
//    you take 1 to a[i] from a stairs. it's equivalent to
//    nim game of removing some from a pile. However, here
//    opponent can counter the move by taking the same in 
//    pile left to it as these move there. The only pile
//    he can't counter is the first one. Or the odd piles, as
//    you can still counter the opponent's move by taking the next
//    odd pile until you reach the 1st.
//    So the game is equivalent to nim game of odd piles.
int grundy(vi &a) {
    int n = a.size();
    int g = 0;
    for(int i = 1; i < n; i+=2) {
        g ^= a[i];
    }
    return g;
}


void test_grundy() {
    rep(i, 9000) {
        vi a;
        for(auto c: to_string(i)) a.pb(c-'0');
        reverse(all(a));

        int digisum = accumulate(all(a), 0);
        if(digisum == 9) {
            int gg = mkgrundy(i);
            int g = grundy(a);
            debug(i, g, gg);
            assert(g == gg);
        }
    }
}

int main(int argc, char **argv) {
    cin.tie(0)->sync_with_stdio(false);

    //test_grundy();

    int q; see(q);
    while(q--) {

        int n; see(n);
        vi a; seev(a, n);

        int g = grundy(a);
        putl(g ? "first" : "second");
    }

    return 0;
}
