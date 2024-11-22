/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/2413
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
#include <cassert>

using namespace std;

//----------TEMPLATES----------
template<typename... T>
void see(T&... args) { ((cin >> args), ...);}
template<typename... T>
void put(T&&... args) { ((cout << args << " "), ...);}
template<typename... T>
void putl(T&&... args) { ((cout << args << " "), ...); cout<<'\n';}
#define error(...) { string _s = #__VA_ARGS__; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, __VA_ARGS__); }
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
#define putv(v,n,k)         { for(int i=0;i<n;i++){ setw(k); cout << v[i]; } cout << "\n"; }
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

void otherssolution(int n, vvl & dp) {
    const int mxN = 1e6+6;

    const int md = 1e9+7;
    dp[1][1] = dp[1][2] = 1;
    for (int i = 2; i < mxN; i++) {
        dp[i][1] = (dp[i-1][1]*4%md + dp[i-1][2])%md;
        dp[i][2] = (dp[i-1][1] + dp[i-1][2]*2%md)%md;
    }

}
/*
 *
 *
 *  
 *
 *
 *
 *
 */


LL solve(int t) {

    #define MX (1e6+6)

    vvl dp(MX+2, vl(2, 0)); // 0 is closed, 1 is open

    dp[0][0] = 1;
    dp[0][1] = 1;

    dp[1][0] = 1;
    dp[1][1] = 1;

    repr(i, 2, MX+2) {


        (dp[i][0] += dp[i-1][0])%=MD;        // closed + closed
        (dp[i][0] += dp[i-1][1])%=MD;        // open + closed

        (dp[i][0] += dp[i-1][0])%=MD;        // closed + inverted E = new closed
        (dp[i][0] += dp[i-1][0])%=MD;        // closed + inverted 6 = new closed
        (dp[i][0] += dp[i-1][0])%=MD;        // closed + 9 = new closed

        (dp[i][1] += dp[i-1][1])%=MD;        // open + open
        (dp[i][1] += dp[i-1][0])%=MD;        // closed + open
        (dp[i][1] += dp[i-1][1])%=MD;        // open + inverted C = new open

    }


    // vvl otherdp(MX+2, vl(3, 0));
    // otherssolution(MX+2, otherdp);

    // repr(i,1,996308) {
    //     assert(dp[i][0] + dp[i][1] == otherdp[i][1] + otherdp[i][2]);
    // }


    while(t--) {
        int n; see(n);
        LL res = (dp[n][0] + dp[n][1])%MD;
        putl(res);
    }

    return 0;
}

int main(int argc, char **argv) {
    cin.tie(0)->sync_with_stdio(false);


    int t; see(t);
    solve(t);

    return 0;
}
