/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/1684

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
    const int N = 2*m;
    vvi adj(N+1), radj(N+1);

    auto comp = [&](int a) {
        return a^1; // toggle last bit
    };

    rep(i,n) {
        char ch1, ch2;
        int a,b;

        see(ch1, a, ch2, b);
        a--, b--;

        int x = 2*a + (ch1 == '-');
        int y = 2*b + (ch2 == '-');

        adj[y].pb(comp(x));
        adj[x].pb(comp(y));

        radj[comp(x)].pb(y);
        radj[comp(y)].pb(x);

        debug(i+1, x^1, y);
        debug(i+1, y^1, x);
    }

    // kosaraju SCC
    vi vis(N+1);
    stack<int> st;

    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        for(int v: adj[u]) {
            if(!vis[v]) dfs(v);
        }
        st.push(u);
    };

    rep(i,N) {
        if(!vis[i]) dfs(i);
    }

    vi scc(N, -1);
    function<void(int,int)> dfs2 = [&](int u, int c) {
        vis[u] = 1;
        scc[u] = c;

        for(int v: radj[u]) {
            if(!vis[v]) {
                dfs2(v, c);
            }
        }
    };

    fill(all(vis), 0);
    int scc_count = 0;
    while(!st.empty()) {
        int u = st.top(); st.pop();
        debug(u, vis[u]);
        if(!vis[u]) {
            dfs2(u, ++scc_count);
        }
    }

    vi ans(m);
    rep(i,m) {
        if(scc[2*i] == scc[2*i+1]) {
            putl("IMPOSSIBLE");
            return 0;
        }
        debug(i+1, 2*i, 2*i+1, scc[2*i], scc[2*i+1]);
        ans[i] = scc[2*i] > scc[2*i+1];
    }
    rep(i,m) {
        put(ans[i] ? "-" : "+");
    }
    putl("");

    return 0;
}
