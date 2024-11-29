/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/1711

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

    int n, m; see(n, m);
    int S = 0, T = n-1;
    vvii adj(n);
    vvi res(n);
    vvl cap(n, vl(n, 0));
    int edge_id = 0;
    rep(i, m) {
        int u, v; see(u, v);
        u--; v--;
        adj[u].pb({v, edge_id++});
        res[u].pb(v);
        res[v].pb(u);
        cap[u][v] = 1;
        //cap[v][u] = 1;
    }

    vi par(n, -1);
    function<LL(int, int)> augment = [&](int S, int T) {
        fill(all(par), -1);

        // BFS to find augmenting path
        queue<int> q;
        q.push(S);
        while(!q.empty() && par[T] == -1) {
            int u = q.front(); q.pop();
            for(auto v: res[u]) {
                if(par[v] != -1 || cap[u][v] <= 0) continue;
                par[v] = u;
                q.push(v);
            }
        }

        if(par[T] == -1) return 0LL;

        // find bottleneck in the path
        int cur = T;
        LL bottleneck = INF;
        while(cur != S) {
            bottleneck = min(bottleneck, cap[par[cur]][cur]);
            cur = par[cur];
        }

        // send flow through the path
        LL flow = bottleneck == INF ? 0 : bottleneck;
        cur = T;
        while(cur != S) {
            cap[par[cur]][cur] -= flow;
            cap[cur][par[cur]] += flow;
            cur = par[cur];
        }

        return flow;

    };

    int last, flow = 0, days=0;
    while((last = augment(S, T)) != 0) {
       flow += last;
       days++;
    }

    vvi paths;
    // send flows such that each edge is used at most once and longest path is found
    // this only the AC in cses
    vi vis(edge_id+2, 0);
    function<void(int, int)> dfs = [&](int u, int p) {
        debug(u, p);
        if(u == S) paths.pb(vi());
        paths.back().pb(u);
        if(u == T) return;

        for(auto [v, id]: adj[u]) {
            if(v == p || vis[id] || cap[u][v] != 0) continue;
            dfs(v, u);
            vis[id] = 1;
            return;
        }
    };

    rep(i, flow) dfs(S, -1);


    putl(paths.size());
    for(auto &v: paths) {
        putl(v.size());
        for(auto x: v) put(x+1);
        putl();
    }

    return 0;
}
