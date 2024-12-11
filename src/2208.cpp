/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/2208

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
#define forx(x,a)           for(auto x:a)
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

#include <cassert>

int grundy(vi &a, bool tdbg=false) {
    bool at_least_one_odd = false;
    forx(x, a) {
        if(x&1) at_least_one_odd = true;
    }
    return at_least_one_odd;
}

int mex(set<int> &s) {
    int i = 0;
    while(s.count(i)) i++;
    return i;
}

unordered_map<int,int> memo;
vi sub = {1,10,100,1000,11,110,1100,101,1010,1001,111,1110,1011,1101,1111};
int mkgrundy(int n) {
    if(n == 0) return 0;
    if(memo.count(n)) return memo[n];
    set<int> s;
    for(int i=0;i < (int)sub.size();i++) {
        if(n-sub[i] >= 0) {
            int ng = mkgrundy(n-sub[i]);
            if(n == 9999) debug(n, n-sub[i], ng);
            s.insert(ng);
        }
    }
    memo[n] = mex(s);
    return memo[n];
}

// test to analyze the states and and grundy values
// it is observed that the grundy values are 0 for all states with at least one odd number
// and >1 for all other states. 
// another key insight:
//  taking one makes any odd number even, and any even number odd.
//  in the last final state, if there is atleast one pile with 1, you can always make a move.
//  so the strategy is to make all the piles even. This forces the opponent to make a move with atleast one odd pile.
//  then you can take the odd pile and make it even again.
//  this way you can always force the opponent to make a move.
//  so the game is always a win for the first player.
void test_grundy() {
    set<int> dd;
    int last_seen_zero = -1;
    for(int i=0;i<=9999;i++) {
        int g = mkgrundy(i);

        vi a(4);
        string s = to_string(i);
        s = string(4-s.size(), '0') + s;
        for(int j=0;j<4;j++) {
            a[j] = (int) s[j]-'0';
        }


        int g2 = grundy(a, false);
        if(g == 0) last_seen_zero = i;
        debug(i, s, g, g2);
        if(i%10 == 0) {
            stringstream ss;
            forx(x, dd) {
                ss << x << " ";
            }
            putl(i, ss.str());
            dd.clear();
        }
        dd.insert(g);
        if( (g >0 && !(g2>0)) || (g==0 && g2!=0)) {
            putl("========");
        }
        assert(g>0? g2>0 : true);
        assert(g==0? g2==0 : true);
    }
    debug(last_seen_zero);
}

int main(int argc, char **argv) {
    cin.tie(0)->sync_with_stdio(false);

    int t; see(t);

    // test_grundy();

    while(t--) {
        int n; see(n);
        vi a(n); seea(a, 0, n);

        putl(grundy(a) ? "first" : "second");
    }

    return 0;
}
