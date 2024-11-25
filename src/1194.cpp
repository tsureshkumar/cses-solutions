/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/1194

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
#define inboundi(x,l,r)     (l <= x && x < r)
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

vector<vector<char>> mat;

int main(int argc, char **argv) {
    cin.tie(0)->sync_with_stdio(false);

    int n, m; see(n, m);
    mat.resize(n, vector<char>(m));

    ii person; 
    typedef ii state;
    set<state> persons, mons;
    vvi pathPos(n, vi(m, 0));
    rep(i, n) rep(j, m) {
        see(mat[i][j]);
        if(mat[i][j] == 'A') person = ii(i,j);
        if(mat[i][j] == 'M') mons.insert(state(i, j));
    }

    vvi monsDistance(n, vi(m, INF));
    
    // BFS to find the distance of each monster from the nearest person
    queue<state> q;
    for(auto &[r, c] : mons) {
        q.push(state(r, c));
        monsDistance[r][c] = 0;
    }

    vi dr = {0, 1, 0, -1}, dc = {1, 0, -1, 0};
    while(!q.empty()) {
        int len = q.size();
        while(len--) {
            auto [r, c] = q.front(); q.pop();
            rep(i, 4) {
                int nr = r + dr[i], nc = c + dc[i];
                if(inboundi(nr, 0, n) && inboundi(nc, 0, m) && mat[nr][nc] != '#' && monsDistance[nr][nc] == INF) {
                    monsDistance[nr][nc] = monsDistance[r][c] + 1;
                    q.push(state(nr, nc));
                }
            }
        }
    }

    // BFS to find the shortest path from the person to the exit
    vvi personDistance(n, vi(m, INF));
    personDistance[person.fi][person.se] = 0;
    vvii par(n, vii(m, ii(-1, -1)));

    q.push(person);
    while(!q.empty()) {
        int len = q.size();
        while(len--) {
            auto [r, c] = q.front(); q.pop();
            
            // check border
            if(r == 0 || r == n-1 || c == 0 || c == m-1) {
                if(personDistance[r][c] < monsDistance[r][c]) {
                    putl("YES");
                    string path = "";
                    ii p = ii(r, c);
                    while(par[p.fi][p.se].fi != -1) {
                        char pathChar = ' ';
                        ii nxt = par[p.fi][p.se];
                        if(nxt.fi == p.fi) {
                            pathChar = nxt.se == p.se+1 ? 'L' : 'R';
                        } else {
                            pathChar = nxt.fi == p.fi+1 ? 'U' : 'D';
                        }
                        path += pathChar;
                        p = nxt;
                    }
                    reverse(all(path));
                    putl(path.size());
                    putl(path);
                    return 0;
                }
            }

            rep(i, 4) {
                int nr = r + dr[i], nc = c + dc[i];
                if(inboundi(nr, 0, n) && inboundi(nc, 0, m) && mat[nr][nc] != '#' && personDistance[nr][nc] == INF) {
                    personDistance[nr][nc] = personDistance[r][c] + 1;
                    par[nr][nc] = ii(r, c);
                    q.push(state(nr, nc));
                }
            }
        }
    }

    putl("NO");
    return 0;
}
