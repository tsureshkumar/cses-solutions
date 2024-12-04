/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/2420

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

LL modpow(LL a, LL b, LL mod) {
    LL res = 1;
    while(b > 0) {
        if(b&1) res = (res*a) % mod;
        a = (a*a) % mod;
        b >>= 1;
    }
    return res;
}

const int A = 31, B=1e9+7;
LL pows[200005];

struct SegTree {
    int n;

    struct Node {
        LL len, fw_hash, bw_hash;
        Node(int len, int fw_hash, int bw_hash) : len(len), fw_hash(fw_hash), bw_hash(bw_hash) {}
    };

    vector<Node> tree;
    vector<char> a;

    SegTree(string &x) : n(1<<(32-__builtin_clz(x.size()))), tree(2*n, Node(0,0,0)), a(n, 0) {
        int m = x.size();
        rep(i,m) a[i] = x[i];
        build(1, 0, n-1);
    }

    void build(int node, int start, int end) {
        if(start == end) {
            tree[node] = Node(1, a[start], a[start]);
        } else {
            int mid = (start + end) / 2;
            build(2*node, start, mid);
            build(2*node+1, mid+1, end);
            tree[node] = combine(tree[2*node], tree[2*node+1]);
        }
    }

    Node combine(Node a, Node b) {
        Node res = Node(a.len + b.len, 0, 0);
        res.fw_hash = ((LL)a.fw_hash*modpow(A, b.len, B) + b.fw_hash + B) % B;
        res.bw_hash = ((LL)b.bw_hash*modpow(A, a.len, B) + a.bw_hash + B) % B;
        return res;
    }

    void update(int i, int l, int r, int pos, int val) {
        if(l > pos || r < pos) return;
        if(l == r) {
            tree[i] = Node(1, val, val);
            return;
        }
        int mid = (l + r) / 2;
        update(2*i, l, mid, pos, val);
        update(2*i+1, mid+1, r, pos, val);
        tree[i] = combine(tree[2*i], tree[2*i+1]);
    }

    void update(int i, int v) {
        update(1, 0, n-1, i, v);
    }

    Node query(int i, int l, int r, int start, int end) {
        if(l > end || r < start) return Node(0,0,0);
        if(start <= l && r <= end) {
            debug(i, l, r, tree[i].fw_hash, tree[i].bw_hash);
            return tree[i];
        }
        int mid = (l + r) / 2;
        Node left = query(2*i, l, mid, start, end);
        Node right = query(2*i+1, mid+1, r, start, end);
        if(left.len == 0) return right;
        if(right.len == 0) return left;
        Node res = combine(left, right);
        debug(res.len, res.fw_hash, res.bw_hash);
        return res;
    }

    bool is_poly(int l, int r) {
        Node node = query(1, 0, n-1, l, r);
        return node.fw_hash == node.bw_hash;
    }
};


int main(int argc, char **argv) {
    cin.tie(0)->sync_with_stdio(false);

    pows[0] = 1;
    rep(i,200004) pows[i+1] = ((LL)pows[i]*A) % B;

    int n, m;
    see(n, m);

    string s;
    see(s);
    SegTree st(s);


    while(m--) {
        int i;
        see(i);
        if(i == 1) {
            int x;
            char c;
            see(x, c);
            st.update(x-1, c);
        } else {
            int l, r;
            see(l, r);
            putl(st.is_poly(l-1, r-1) ? "YES" : "NO");
        }
    }

    return 0;
}
