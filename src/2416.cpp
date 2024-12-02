/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/2416

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

// segtree that returns the index of the maximum element    
class SegTree
{
  vii st;
  int n;
  public:
  SegTree (int m)
  {
    n = 1 << (int)ceil (log2 (m));  
    st.resize (2 * n);
  }
  ii combine (ii a, ii b)
  {
    if (a.fi == b.fi)
      return {a.fi, max (a.se, b.se)};
    return a.fi > b.fi ? a : b;
  }
  void update (int i, int x)
  {
    for (st[i += n] = {x, i}; i > 1; i >>= 1)
      st[i >> 1] = combine (st[i], st[i ^ 1]);
  }
  ii query (int l, int r)
  {
    ii res = {0, 0};
    for (l += n, r += n; l < r; l >>= 1, r >>= 1)
      {
        if (l & 1)
          res = combine (res, st[l++]);
        if (~r & 1)
          res = combine (res, st[r--]);
      }
    if (l == r)
      res = combine (res, st[l]);
    return res;
  }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, q;
    see(n, q);
    vi a(n);
    seea(a, 0, n);

    // Initialize segment tree for range maximum queries
    SegTree st(n);
    rep(i, n) st.update(i, a[i]);

    // Precompute prefix sums for O(1) range sum queries
    vl cumsum(n + 1, 0);
    dwn(i, n) cumsum[i] = cumsum[i + 1] + a[i];

    // Find next greater element for each position using monotonic stack
    // next_greater[i] = index of first element > a[i] to the right
    vi next_greater(n, n);
    stack<int> stk;
    dwn(i, n) {
        // Remove elements smaller than current (they can't be "next greater")
        while (!stk.empty() && a[stk.top()] < a[i]) 
            stk.pop();
        // Current next greater element is top of stack (or n if none exists)
        next_greater[i] = stk.empty() ? n : stk.top();
        stk.push(i);
    }

    // Precompute minimum cost to make suffix increasing starting at each position
    // cost[i] = minimum cost to make a[i:] increasing
    vl cost(n + 1, 0);
    dwn(i, n) {
        int next_big = next_greater[i];
        // Calculate sum of elements between i and next greater element
        LL sum = cumsum[i] - cumsum[next_big];
        // Cost to increase all elements between i and next_big to a[i]
        LL t = (LL)(next_big - i) * a[i] - sum;
        // Total cost = cost of current segment + cost of remaining suffix
        cost[i] = t + cost[next_big];
    }

    // Query function to find minimum cost for range [l,r]
    auto query = [&](int l, int r) {
        // Find maximum element and its position in range [l,r]
        auto [mxv, mx] = st.query(l, r);
        
        // Cost has two components:
        // 1. Cost from l to maximum element (cost[l] - cost[mx])
        // 2. Cost from maximum element to r:
        //    - All elements need to be increased to mxv
        //    - Cost = (length * mxv) - (sum of elements)
        LL ans = cost[l] - cost[mx];
        ans += (LL)(r - mx + 1) * mxv - (cumsum[mx] - cumsum[r + 1]);
        return ans;
    };

    // Process queries
    rep(i, q) {
        int x, y;
        see(x, y);
        putl(query(x-1, y-1));  // Convert to 0-based indexing
    }

    return 0;
}
