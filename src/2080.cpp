/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/2080
 
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
 
    int n, k; see(n, k);
 
    vector<set<int>> adj(n);
    rep(i, n-1) {
        int u, v; see(u, v);
        u--; v--;
        adj[u].insert(v);
        adj[v].insert(u);
    }
 
    if (n == k) { // can't have any paths of length n in a tree
        putl(0);
        return 0;
    }
 
    // centroid decomposition
    vi subsize(n);
    vi processed(n, 0);
    function<int(int, int)> subtree_size = [&](int u, int p) {
        int ans = 1;
        for (int v : adj[u]) if (v != p && !processed[v]) ans += subtree_size(v, u);
        subsize[u] = ans;
        return ans;
    };
    subtree_size(0, -1);
 
    function<int(int, int, int)> find_centroid = [&](int wanted, int u, int p) {
        for (int v : adj[u]) if (v != p && !processed[v] && subsize[v] > wanted) return find_centroid(wanted, v, u);
        return u;
    };
 
    LL ans = 0;
    function<void(int, int, int, vl&, vl&)> count_paths = [&](int u, int p, int d, vl &prev, vl &cur) {
        if (d > k) return;
        ans += prev[k-d];
        cur[d]++;
        for (int v : adj[u]) if (v != p && !processed[v]) count_paths(v, u, d+1, prev, cur);
    };
 
    function<void(int, int)> decompose = [&](int u, int p) {
        subtree_size(u, p);
        if (subsize[u] < k) return;
        int centroid = find_centroid(subsize[u]>>1, u, p);
        debug(u+1, p+1, centroid+1);
        processed[centroid] = 1;
 
        // process. count paths of exact length k
        vl paths(k+1, 0), cur(k+1, 0);
        paths[0] = 1; // centroid itself
        for (int v : adj[centroid]) {
            if (processed[v]) continue;
            count_paths(v, centroid, 1, paths, cur);
            repr(i,1, k+1) paths[i] = cur[i];
        }
 
        for (int v : adj[centroid]) if (!processed[v]) decompose(v, centroid);
    };
    decompose(0, -1);
 
    putl(ans);
    return 0;
}
