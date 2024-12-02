/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/1737

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
 
 
struct node {
    LL sum;
    int version;
    node *left, *right;
    node() : sum(0), version(1), left(nullptr), right(nullptr) {}
};

/*
* This problem is a classic example of the persistence property of the segment tree.
* We can copy the previous version of the tree and update it to create a new version.
* This way we can query any version of the tree at any time.
*/
 
class SegmentTree {
    int n;
    vector<node*> roots;
public:
    SegmentTree(int m) : n(1<<(32 - __builtin_clz(m))) {
        roots.pb(nullptr);
    }
    node* build(const vector<int>& arr, int tl, int tr);
    void build(const vector<int>& arr);
    void update(int i, int k, int x);
    node* update(node * p, int tl, int tr, int i, int k, int x);
    LL query(int l, int r, int k);
    LL query(node * p, int tl, int tr, int l, int r);
    void copy(int k);
};

void SegmentTree::build(const vector<int>& arr) {
    roots.pb(build(arr, 0, n-1));
}

node* SegmentTree::build(const vector<int>& arr, int tl, int tr) {
    if(tl == tr) {
        node * p = new node();
        p->sum = tl >= (int) arr.size() ? 0 : arr[tl];
        return p;
    }
    int tm = (tl + tr) / 2;
    node * left = build(arr, tl, tm);
    node * right = build(arr, tm+1, tr);
    node * p = new node();
    p->left = left;
    p->right = right;
    p->sum = left->sum + right->sum;
    return p;
}

void SegmentTree::update(int i, int k, int x) {
    roots[k] = update(roots[k], 0, n-1, i, k, x);
}

node* SegmentTree::update(node *prev, int tl, int tr, int i, int k, int x) {
    node * q = new node();
    if(tl == tr) {
        q->sum = x;
        q->version = k;
        return q;
    }
    int tm = (tl + tr) / 2;
    if(i <= tm) {
        q->left = update(prev->left, tl, tm, i, k, x);
        q->right = prev->right; 
    } else {
        q->left = prev->left;
        q->right = update(prev->right, tm+1, tr, i, k, x);
    }
    q->sum = q->left->sum + q->right->sum;
    return q;
}

LL SegmentTree::query(int l, int r, int k) {
    LL res = query(roots[k], 0, n-1, l, r);
    return res;
}

LL SegmentTree::query(node * p, int tl, int tr, int l, int r) {
    if(l > r) return 0;
    if(tl > r || tr < l) return 0;
    if(l <= tl && tr <= r) return p->sum;
    int tm = (tl + tr) / 2;
    return query(p->left, tl, tm, l, r) + query(p->right, tm+1, tr, l, r);
}

void SegmentTree::copy(int k) {
    roots.pb(roots[k]);
}
 
 
int main(int argc, char **argv) {
    cin.tie(0)->sync_with_stdio(false);
    int n, q; see(n, q);
    SegmentTree st(n);
    vi arr; 
    rep(i, n) {
        int x; see(x);
        arr.pb(x);
    }
    st.build(arr);
    rep(i, q) {
        int c; see(c);
        if(c == 1) { // update
            int k, a, x; see(k, a, x);
            st.update(a-1, k, x);
        } else if (c == 2) { // query
            int k, a, b; see(k, a, b);
            // debug("query", k, a, b);
            putl(st.query(a-1, b-1, k));
        } else { // copy
            int k; see(k);
            st.copy(k);
        }
    }
    return 0;
}
