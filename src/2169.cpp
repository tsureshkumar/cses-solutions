/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/2169

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


struct cmp {
    bool operator() (const ii& a, const ii& b) const {
        if (a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    }
};


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
// Ordered multiset that allows duplicates and supports order statistics
typedef tree<
    ii,                      // Key type
    null_type,                // Mapped type (null since we only need keys)
    cmp,
    rb_tree_tag,              // Red-black tree
    tree_order_statistics_node_update  // Support order statistics
> ordered_multiset;

typedef tree<
    ii,                      // Key type
    null_type,                // Mapped type (null since we only need keys)
    less<ii>,                // Comparison function
    rb_tree_tag,              // Red-black tree
    tree_order_statistics_node_update  // Support order statistics
> ordered_multiset2;




int main(int argc, char **argv) {
    cin.tie(0)->sync_with_stdio(false);

    // Read input
    int n;
    see(n);

    // Store segments as (start, end) pairs
    vii segments;
    vi segids(n); // To maintain original segment indices while sorting
    iota(all(segids), 0);
    vi contains(n), contained_in(n); // Results for each segment

    rep(i,n) {
        int start, end;
        see(start, end);
        segments.pb({start, end});
    }

    auto get_segment = [&](int i) { return segments[segids[i]]; };

    // First pass: Find segments that contain other segments
    {
        // Sort by start point (descending end point for ties)
        sort(all(segids), [&](int i, int j) {
            ii seg1 = segments[i], seg2 = segments[j];
            if(seg1.fi == seg2.fi) {
                return seg1.se >= seg2.se;
            }
            return seg1.fi < seg2.fi;
        });

        ordered_multiset end_points;
        dwn(i, n) {
            ii curr = get_segment(i);
            debug(curr.fi, curr.se);

            // If any previous segment ends before current segment,
            // current segment contains at least one other segment
            int it = end_points.order_of_key({curr.se, -1});
            if(it > 0) {
                contains[segids[i]] = it;
            }

            end_points.insert({curr.se, i});
        }
    }

    // Second pass: Find segments that are contained in other segments
    {
        ordered_multiset2 end_points;
        rep(i, n) {
            ii curr = get_segment(i);
            debug(curr.fi, curr.se);

            // If any previous segment ends after current segment,
            // current segment is contained in at least one other segment
            auto it = end_points.order_of_key({curr.se, -1});
            if(end_points.size() > it ) {
                contained_in[segids[i]] = end_points.size() - it ;
            }
            end_points.insert({curr.se, i});
        }
    }

    // Print results
    for(auto x: contains) put(x); putl();
    for(auto x: contained_in) put(x); putl();

    return 0;
}
