/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/2134

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

class SegmentTree {
    int n;
    vi tree;
public:
    SegmentTree(int m) : n(1<<(32-__builtin_clz(m))), tree(2*n, -INF) {}
    void update(int i, int v) {
        i += n;
        tree[i] = v;
        for (i /= 2; i > 0; i /= 2) {
            tree[i] = max(tree[i*2], tree[i*2+1]);
        }
    }
    int query(int l, int r) {
        int res = -INF;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l&1) res = max(res, tree[l++]);
            if (r&1) res = max(res, tree[--r]);
        }
        return res;
    }
};

int main(int argc, char **argv) {
    cin.tie(0)->sync_with_stdio(false);

    int n, q;
    see(n, q);
    
    vi a(n);
    seea(a, 0, n);

    vvi adj(n);
    rep(i, n-1) {
        int u, v;
        see(u, v);
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }


    // heavy light decomposition
    vi size(n), depth(n), parent(n), heavy(n, -1);
    function<int(int, int)> dfs = [&](int u, int p) {
        size[u] = 1;
        for (int v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            parent[v] = u;
            size[u] += dfs(v, u);
            if (heavy[u] == -1 || size[v] > size[heavy[u]]) {
                heavy[u] = v;
            }
        }
        return size[u];
    };
    dfs(0, -1);

    vi head(n), pos(n);
    int cur_pos = 0;
    SegmentTree st(n);
    function<void(int, int)> decompose = [&](int u, int h) {
        head[u] = h;
        pos[u] = cur_pos++;
        st.update(pos[u], a[u]);
        if (heavy[u] != -1) {
            decompose(heavy[u], h);
        }
        for (int v : adj[u]) {
            if (v == parent[u] || v == heavy[u]) continue;
            decompose(v, v);
        }
    };
    decompose(0, 0);

    auto query = [&](int u, int v) {
        int mx = -INF;
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            mx = max(mx, st.query(pos[head[u]], pos[u]+1));
            u = parent[head[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        return max(mx, st.query(pos[u], pos[v]+1));
    };

    rep(i, q) {
        int t;
        see(t);
        if (t == 1) {
            int u, x;
            see(u, x);
            u--;
            st.update(pos[u], x);
        } else {
            int u, v;
            see(u, v);
            u--; v--;
            put(query(u, v));
        }
    }
    cout << "\n";

    return 0;
}
