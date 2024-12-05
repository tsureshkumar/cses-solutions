/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/2108

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

    string s; see(s);

    string t = s + "$";
    int n = t.size();

    vi sa(n), ra(n);

    auto radix_sort = [&](vi &sa, vi &ra, int k) {
        int maxi = max(300, n);
        vi cnt(maxi+1);
        rep(i,n) cnt[i+k < n ? ra[i+k] : 0]++;
        repr(i,1,maxi+1) cnt[i] += cnt[i-1];

        vi tmp_sa(n);
        dwn(i,n) tmp_sa[--cnt[sa[i]+k < n ? ra[sa[i]+k] : 0]] = sa[i];
        sa = tmp_sa;
    };

    rep(i,n) sa[i] = i, ra[i] = t[i];
    for(int k=1; k<n; k<<=1) {
        radix_sort(sa, ra, k);
        radix_sort(sa, ra, 0);

        vi tmp_ra(n);
        int r = 0;
        rep(i,n) {
            if(i == 0) tmp_ra[sa[i]] = r;
            else if(ii(ra[sa[i]], sa[i]+k < n ? ra[sa[i]+k] : 0) == ii(ra[sa[i-1]], sa[i-1]+k < n ? ra[sa[i-1]+k] : 0)) tmp_ra[sa[i]] = r;
            else tmp_ra[sa[i]] = ++r;
        }
        ra = tmp_ra;

    }

    vi lcp(n), plcp(n), prev_sa(n);
    prev_sa[sa[0]] = -1;
    repr(i,1,n) prev_sa[sa[i]] = sa[i-1];
    int l = 0;
    rep(i,n) { // traverse as per string order
        if(prev_sa[i] == -1) {
            plcp[i] = 0;
            continue;
        }
        int j = prev_sa[i];
        while(t[i+l] == t[j+l]) l++;
        plcp[i] = l;
        l = max(l-1, 0);
    }
    rep(i,n) lcp[i] = plcp[sa[i]];

    #if DEBUG == 1
    //rep(i,n) putl(sa[i], ra[sa[i]], prev_sa[sa[i]], plcp[sa[i]], lcp[i], t.substr(sa[i]));
    #endif

    LL k = 0;
    see(k);
    LL c = 0;
    repr(i,1,n) {
        LL nxt = (n-1) - sa[i] - lcp[i];
        if(c <= k && k <= c + nxt) {
            putl(s.substr(sa[i], lcp[i] + k - c));
            return 0;
        }
        c += nxt;
    }


    return 0;
}
