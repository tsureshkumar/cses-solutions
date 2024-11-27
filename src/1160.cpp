/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/1160

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
#include <unistd.h>
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

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    see(n, q);
    vi next(n+1, 0);
    seea(next, 1, n+1);


    vi root(n+1, 0);
    vi pos(n+1, 0);
    vi depth(n+1, 0);
    vi cycleSizes(n+1, 0);

    vi vis(n+1, 0);
    function<void(LL)> dfs = [&](LL v) -> void {
        if (vis[v] == 2) { // VISITING
            root[v] = v;
            int cycleSize = 0;
            pos[v] = ++cycleSize;

            for (int u = next[v]; u != v; u = next[u]) {
                root[u] = root[v];
                pos[u] = ++cycleSize;
            }
            depth[root[v]] = 0;
            cycleSizes[root[v]] = cycleSize;
            vis[v] = 1;
            return ;
        } else if (vis[v] == 1) {
            // FULLY VISITED
            return;
        }
        vis[v] = 2; // VISITED
        dfs(next[v]);

        // depth from cycle start
        if (pos[v] == 0) {
            depth[v] = depth[next[v]] + 1;
            root[v] = root[next[v]];
        }
        vis[v] = 1; // FULLY VISITED
    };

    repr(i, 1, n+1) {
        if (vis[i] == 0) {
            dfs(i);
        }
    }

    // build jump table
    vvi jump(n+1, vi(20, 0));
    repr(i, 1, n+1) {
        jump[i][0] = next[i];
    }
    repr(k, 1, 20) {
        repr(i, 1, n+1) {
            jump[i][k] = jump[jump[i][k-1]][k-1];
        }
    }

    function<int(int, int)> mkjump = [&](int x, int k) -> int {
        dwnr(i, 0, 20) {
            if (k & (1 << i)) {
                x = jump[x][i];
            }
        }
        return x;
    };

    // setw(3); put("*"); rep(i,21) { setw(3); put(i); } putl("");
    // rep(i, n+1) {
    //     setw(3); put(i); 
    //     rep(j, 21) { setw(3); put(jump[i][j]); } 
    //     putl("");
    // }
    // rep(i, n+1) {
    //     setw(3); put(i);
    //     setw(3); put(root[i]);
    //     setw(3); put(depth[i]);
    //     setw(3); put(pos[i]);
    //     setw(3); put(cycleSizes[root[i]]);
    //     putl("");
    // }



    while (q--) {
        int x, y;
        see(x, y);

        if (root[x] != root[y] || depth[x] < depth[y]) {
            putl(-1);
            continue;
        }

        // jump to make depth same
        int ans = depth[x] - depth[y];
        x = mkjump(x, ans);

        if(pos[x] == 0 && x != y) {
            // not in cycle and both are from different trees
            putl(-1);
        } else {
            // in cycle or same tree
            ans += (pos[y] - pos[x] + cycleSizes[root[x]]) % cycleSizes[root[x]];
            putl(ans);
        }
    }

    return 0;
}
