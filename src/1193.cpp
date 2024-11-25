/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/1193

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

vector<vector<char>> grid;
int n, m;

int pathlen = INF;
string path;

vector<vector<ii>> dist;

bool find_path(int x, int y) {

    typedef tuple<int,int,int> state;
    queue<state> q;
    q.push({x, y, -1});

    //     rep(i, n) {
    //     rep(j, m) {
    //         cout << grid[i][j];
    //     }
    //     cout << "\n";
    // }

    LL steps = 0;
    while(!q.empty()) {
        int s = q.size();
        rep(i, s) {
            auto [x, y, dir] = q.front(); q.pop();
            if(grid[x][y] == '#') continue;
            if(dist[x][y].fi < steps) continue;

            dist[x][y] = {steps, dir};
           
            if(grid[x][y] == 'B') {
                if(dist[x][y].fi < pathlen) {
                    pathlen = dist[x][y].fi;
                    // reconstruct path
                    string p = "";
                    int dir = dist[x][y].se;
                    debug(x,y, dir);
                    int px = x, py = y;
                    while(dir != -1) {
                        switch(dir) {
                            case 0: p += 'R'; py = py-1; break;
                            case 1: p += 'D'; px = px-1; break;
                            case 2: p += 'L'; py = py+1; break;
                            case 3: p += 'U'; px = px+1; break;
                        }
                        dir = dist[px][py].second;
                        debug(px, py, dir);
                    }
                    reverse(all(p));
                    path = p;
                }
                continue;
            }
            grid[x][y] = '#';
            if(x+1 < n && grid[x+1][y] != '#') q.push({x+1, y, 1});
            if(x-1 >= 0 && grid[x-1][y] != '#') q.push({x-1, y, 3});
            if(y+1 < m && grid[x][y+1] != '#') q.push({x, y+1, 0});
            if(y-1 >= 0 && grid[x][y-1] != '#') q.push({x, y-1, 2});
        }
        steps++;
    }

    // auto code = [&](int dir) {
    //     switch(dir) {
    //         case 0: return 'R';
    //         case 1: return 'D';
    //         case 2: return 'L';
    //         case 3: return 'U';
    //     }
    //     return '?';
    // };
    // rep(i, n) {
    //     rep(j, m) {
    //         setw(3);
    //         cout << code(dist[i][j].se) << " ";
    //     }
    //     cout << "\n";
    // }

    debug(pathlen, path);

    return pathlen < 1000000;
}

int main(int argc, char **argv) {
    cin.tie(0)->sync_with_stdio(false);

    see(n, m);
    grid.assign(n, vector<char>(m));
    dist.assign(n, vector<ii>(m, {INF, -1}));
    rep(i, n) rep(j, m) cin >> grid[i][j];

    rep(i, n) rep(j, m) {
        if(grid[i][j] == 'A') {
            dist[i][j] = {0, -1};
            if(find_path(i, j)) {
                putl("YES");
                putl(pathlen);
                putl(path);
                return 0;
            } else {
                putl("NO");
                return 0;
            }
        }
    }   

    return 0;
}
