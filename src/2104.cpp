/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/2104

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

struct SegTree {
    int n;
    vi t;
    SegTree(int m) : n(1<<(32-__builtin_clz(m))), t(2*n, 0) {}
    void update(int p, int value) {
        for(t[p += n] = value; p > 1; p >>= 1) t[p>>1] = min(t[p], t[p^1]);
    }
    int query(int l, int r) {
        int res = INF;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if(l&1) res = min(res, t[l++]);
            if(r&1) res = min(res, t[--r]);
        }
        return res;
    }
};

int main(int argc, char **argv) {
    cin.tie(0)->sync_with_stdio(false);

    string s;
    see(s);

    string t = s + "$";
    int n = t.size();

    vi sa(n), ra(n);
    rep(i,n) sa[i] = i, ra[i] = t[i];

    for(int k=1; k<n; k*=2) {
        vii pairs;
        rep(i,n) pairs.pb({ra[i], i + k < n ? ra[i+k] : 0});
        sort(all(sa), [&](int a, int b) {
            return pairs[a] < pairs[b];
        }); 
        ra[sa[0]] = 0;
        repr(i,1,n) ra[sa[i]] = pairs[sa[i]] == pairs[sa[i-1]] ? ra[sa[i-1]] : i;
    }

    #if DEBUG == 1
    rep(i,n) putl(sa[i], ra[i], t.substr(sa[i]));
    #endif

    SegTree st(n);
    rep(i,n) st.update(i, sa[i]);

    int q;
    see(q);

    while(q--) {
        string pat;
        see(pat);

        int m = pat.size();
        int l = 0, r = n-1;
        while(l < r) {
            int mid = (l + r) / 2;
            if(t.substr(sa[mid], m) < pat) l = mid + 1;
            else r = mid;
        }
        if (t.substr(sa[l], m) != pat) {
            putl(-1);
            continue;
        }
        int low = l;

        l = 0, r = n;
        while(l < r) {
            int mid = (l + r) / 2;
            if(mid == n || t.substr(sa[mid], m) > pat) r = mid;
            else l = mid + 1;
        }
        int high = l;

        debug(low, high, sa[low], sa[high-1], t.substr(sa[low], m), t.substr(sa[high-1], m));
        int res = st.query(low, high);
        putl(res+1);
    }


    return 0;
}
