/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/1136

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

    int n, m;
    see(n,m);

    vvi adj(n);
    rep(i,n-1) {
        int u, v; see(u,v);
        --u; --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    vi depth(n);
    vi parent(n);
    function<void(int,int)> dfs = [&](int u, int p) {
        depth[u] = depth[p]+1;
        parent[u] = p;
        for(int v: adj[u]) {
            if(v==p) continue;
            dfs(v,u);
        }
    };
    dfs(0,0);

    // make jump table
    const int LOGN = 20;
    vvi jump(n, vi(LOGN+1));
    rep(i,n) jump[i][0] = parent[i];
    repr(j,1,LOGN+1) {
        rep(i,n) {
            jump[i][j] = jump[jump[i][j-1]][j-1];
        }
    }

    auto lca = [&](int u, int v) {
        if(depth[u] < depth[v]) swap(u,v);

        int k = abs(depth[u]-depth[v]);
        while(k) {
            int j = __builtin_ctz(k);
            u = jump[u][j];
            k &= k-1;
        }

        while(u != v) {
            dwnr(j,0,LOGN) {
                if(jump[u][j] != jump[v][j]) {
                    u = jump[u][j];
                    v = jump[v][j];
                }
            }
            if(u != v) u = jump[u][0], v = jump[v][0];
        }
        return u;
    };

    parent[0] = -1;
    vi path_count(n);
    rep(i,m) {
        int u, v; see(u,v);
        --u; --v;
        if(depth[u] < depth[v]) swap(u,v);
        int w = lca(u,v);
        if(w == v) { // same path
            int par = parent[v];
            if(par != -1) path_count[par]--;
            path_count[u]++;
        } else { // different paths
            int par = parent[w];
            path_count[u]++;
            path_count[v]++;
            path_count[w]--;
            if(par != -1) path_count[par]--;
        }
    }

    function<void(int,int)> dfs2 = [&](int u, int p) {
        for(int v: adj[u]) {
            if(v==p) continue;
            dfs2(v,u);
            path_count[u] += path_count[v];
        }
    };
    dfs2(0,0);

    rep(i,n) {
        put(path_count[i]);
    }
    putl();
    return 0;
}
