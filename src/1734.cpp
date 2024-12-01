/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/1734

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

int main(int argc, char **argv) {
    cin.tie(0)->sync_with_stdio(false);

    int n, q; see(n, q);
    vi a(n); seea(a, 0, n);

    vii queries(q);
    for(auto &[x, y] : queries) {
        see(x, y);
        x--; y--;
    }

    // do dimentionality reduction by compressing the array
    vi b = a;
    sort(all(b));
    b.erase(unique(all(b)), b.end());
    for(auto &x : a) x = INDEX(b, x);

    // model distinct values as a range query
    // fw stores the active last seen 1 for each distinct value.
    // at any time, there will be only one active 1 for each distinct value.
    // when seen a new distinct value, reset the last seen 1 of that value by subtracting 1.
    // then add a new 1 at the current index.
    int M = n;
    vi fw(M+1);
    function<void(int, int)> add = [&](int i, int x) {
        i++; // 1-indexed
        for(; i <= M; i += BitLSOne(i)) fw[i] += x;
    };
    function<int(int)> sum = [&](int i) {
        i++; // 1-indexed
        int res = 0;
        for(; i > 0; i -= BitLSOne(i)) res += fw[i];
        return res;
    };

    // events makes it a sweep line problem
    vector<array<int, 3>> events;
    rep(i, q) {
        auto [l, r] = queries[i];
        events.pb({l, -1, i});
        events.pb({r, 1, i});
    }
    sort(all(events));

    auto print_fw = [&]() {
        #if DEBUG == 1
        rep(i, M+1) cout << sum(i) - sum(i-1) << " ";
        cout << "\n";
        #endif
    };

    vi ans(q);
    vi last(M+1, -1);
    int cur = -1;

    print_fw();

    rep(i, events.size()) {
        auto [pos, type, idx] = events[i];
        debug(pos, type, idx, cur);
        while(cur < pos) {
            cur++;
            debug(a[cur], last[a[cur]], cur);
            if(last[a[cur]] != -1) add(last[a[cur]], -1);
            last[a[cur]] = cur;
            add(cur, 1);
        }
        print_fw();
        if(type == 1) ans[idx] = sum(pos) - sum(queries[idx].fi-1);
        debug(idx, queries[idx].fi, queries[idx].se, ans[idx]);
    }

    for(auto x : ans) putl(x);

    return 0;
}
