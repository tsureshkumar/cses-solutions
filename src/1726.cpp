/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/1726

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
#define LD                  long double
#define INF                 ((1e9))
#define EPS                 (0.0000001)
#define PI                  (acos(-1.0))
#define MD                  (1000000007)
#define ii                  pair<int,int>
#define ll                  pair<LL,LL>
#define vii                 vector<pair<int,int> >
#define vi                  vector<int>
#define vvld                vector<vector<LD> >
#define vld                 vector<LD>
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

#include <cassert>

#define N 8

vvld transition_matrix;

vvld matmult(vvld a, vvld b) {
    int n = a.size(), m = a[0].size(), p = b[0].size();
    assert(m == (int)b.size());
    vvld c(n, vld(p, 0));
    rep(i,n) rep(j,p) rep(k,m) {
        c[i][j] += a[i][k] * b[k][j];
    }
    return c;
}

vvld matpow(vvld a, int k) {
    int n = a.size();
    vvld res(n, vld(n, 0));
    rep(i,n) res[i][i] = 1;
    while(k) {
        if(k&1) res = matmult(res, a);
        a = matmult(a, a);
        k >>= 1;
    }
    return res;
}

void print_matrix(vvld &a, int w=3, string name = "") {
    cout << name << "\n";
    int m = a.size(), n = a[0].size();
    setw(w); put("*"); rep(i, n) put(i); putl();
    rep(i, m) {
        setw(w); put(i);
        rep(j, n) {
            setw(w); setpr(2); put(a[i][j]);
        }
        putl();
    }
}

LD dp[100][10][10][2];
LD solve_by_dp(int k) {

    auto to_robot = [](int i, int j) { return (i-1)*N + j-1; };
 
    int active = 0, nxt = active^1; // active version of the board
    // fill in the initial state
    repr(i,1,N+1) repr(j,1,N+1) {
        int robot = to_robot(i,j);    
        dp[robot][i][j][active] = 1;
    }
 
    int dx[] = {0,1,0,-1,0};
    // do k iterations
    rep(i,k) {
        // iterate over all robots
        rep(robot,N*N) {
            // iterate over all cells
            repr(i,1,N+1) repr(j,1,N+1) {
                dp[robot][i][j][nxt] = 0;
            }
            repr(i,1,N+1) repr(j,1,N+1) {
                // iterate over all possible moves
                LD cur = dp[robot][i][j][active];
 
                // find valid neighbours
                int denom = 0;
                rep(r,4) {
                    int ni = i+dx[r], nj = j+dx[r+1];
                    if(!(ni < 1 || ni > N || nj < 1 || nj > N)) {
                        denom++;
                    }
                }
                rep(r,4) {
                    int ni = i+dx[r], nj = j+dx[r+1];
                    dp[robot][ni][nj][nxt] += cur / denom;
                }
            }
        }
        swap(active, nxt);
    }
 
    // calculate the answer
    LD prob_empty = 0;
    repr(i,1,N+1) repr(j,1,N+1) {
        LD cell_prob_to_empty = 1;
        rep(robot,N*N) {
            cell_prob_to_empty *= (1-dp[robot][i][j][active]);
        }
        if(i==1 && j==1) debug((i-1)*N + (j-1), cell_prob_to_empty);
        prob_empty += cell_prob_to_empty;
    }
    return prob_empty;
}


int main(int argc, char **argv) {
    cin.tie(0)->sync_with_stdio(false);

    int k; see(k);

    int dx[] = {0,1,0,-1,0};
    int dy[] = {1,0,-1,0,1};

    // build the transition matrix for markov chain
    // each cell T[i][j] is the probability of moving from cell j to cell i
    transition_matrix = vvld(N*N, vld(N*N, 0));
    rep(j, N*N) {
        int x = j/N, y = j%N;
        int denom = (x > 0) + (x < N-1) + (y > 0) + (y < N-1);
        rep(r, 4) {
            int nx = x+dx[r], ny = y+dy[r];
            if(nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            transition_matrix[nx*N+ny][j] = 1.0/denom;
        }
    }

    // compute the k-th power of the transition matrix
    vvld pow = matpow(transition_matrix, k);

    // each robot having their own board initial state
    vvld robots(N*N, vld(N*N, 0));
    rep(i, N*N) robots[i][i] = 1;

    // move the robots to kth state
    vvld res = matmult(pow, robots);
    #if DEBUG==1
    print_matrix(transition_matrix, 3, "transition_matrix");
    print_matrix(res, 3, "res");
    #endif

    // compute the probability of being empty
    // for each cell, probability of being empty
    // is the product of the probability of being empty for each robot
    LD ans = 0;
    rep(cell, N*N) {
        LD empty = 1;
        rep(robot, N*N) empty *= (1.-res[cell][robot]);
        ans += empty;
    }

    printf("%.6Lf\n", ans);

    // LD ans2 = solve_by_dp(k);
    // printf("%.6Lf\n", ans2);

    
    return 0;
}
