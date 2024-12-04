/*
 * Author: Sureshkumar T <tsureshkumar2000@gmail.com>
 * Copyright (C) 2024 Sureshkumar T. All rights reserved.
 */


// https://cses.fi/problemset/task/1112

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

LL modpow(LL b, LL e) {
    LL ans = 1;
    while(e) {
        if(e&1) ans = ans * b % MD;
        b = b * b % MD;
        e >>= 1;
    }
    return ans;
}

LL bf(string &s, int n) {
    set<string> st;

    function<void(int, int, string&)> gen = [&](int i, int x, string &t) {
        //if(x==1) debug(i, x, t);
        if(i == n) {
            st.insert(t);
            return;
        }
        if(i==x) {
            if(i+(int)s.size() >n) return;
            string old = t;
            t += s;
            gen(i+(int)s.size(), x, t);
            t = old;
        } else {
            repr(j,'A','Z'+1) {
                t.push_back(j);
                gen(i+1, x, t);
                t.pop_back();
            }
        }
    };

    rep(i,n) {
        string tmp = "";
        gen(0, i, tmp);
    }

    // repi(x,st) {
    //     debug(*x);
    // }

    return st.size();
}

LL solve2(string &s, int n) {
     // calculate kmp distances
    auto kmp_preprocess = [&](string &s, vi &kmp) {
        int n = s.sz;
        if(n==0) return;
        kmp.assign(n+5, 0);
        kmp[0] = -1;
        int k = 0;
        repr(i,1,n) {
            while(k >= 0 && s[i] != s[k]) k=kmp[k];
            k++;
            kmp[i+1] = k;
        }
    };
 
    vi kmp;
    kmp_preprocess(s, kmp);
 
#if DEBUG==1
    const int w = 9;
    setw(w); put("i"); rep(i,n) {setw(w); put(i);} putl();
    setw(w); put("s"); rep(i,n) {setw(w); put(s[i]);} putl();
    setw(w); put("kmp"); rep(i,n) {setw(w); put(kmp[i]);} putl();
#endif // DEBUG
 
    // dp[i][j] - holds number of strings of length i which holds a substring of line
    //            of j-1 length
    //                
    int m = s.sz;
    vvi dp(n+2, vi(m+2, 0));
    dp[0][0] = 1; // strings of length 0 with empty prefix of line
 
    repr(i,1,n+1) {
        // strings of len i, with complete string line as substring one or more time
        // since already it is contained in i-1 length, we can add any char for i'th pos
        dp[i][m] = ((LL)26 * dp[i-1][m])%MD;
        repr(j,0,m) {
            // try to fill with length of j of line is contained in strings of length i
            repr(k,'A','Z'+1) {
                // ith char is k
                // identify which longest prefix of line[j] is ending with k
                int prefix_ends_with_k = -1;
                for(int t=j; t >= 0; t = kmp[t]) {
                    if(s[t] == k) {
                        prefix_ends_with_k = t;
                        break;
                    }
                }
                (dp[i][prefix_ends_with_k+1] += dp[i-1][j])%=MD;
                // if no prefix ends with k, still add it above as empty prefix
            }
        }
    }
 
#if DEBUG==1
    putl("dp solution2:");
    rep(i,n+1) {
        rep(j, m+1) {
            setw(w); put(dp[i][j]);
        }
        putl();
    }
#endif // DEBUG
 
    LL res = 0;
    (res += dp[n][m])%=MD;
    return res;
}   

int main(int argc, char **argv) {
    cin.tie(0)->sync_with_stdio(false);

    int n; see(n);
    string s; see(s);
    int m = s.size();

    vi kmp(m+1, 0);
    int k = 0;
    repr(i,1,m) {
        while(k > 0 && s[i] != s[k]) k = kmp[k-1];
        if(s[i] == s[k]) k++;
        else k = 0;
        kmp[i] = k;
    }

    // dp[i][j] = number of strings of length i where j characters match s
    vvl dp(n+1, vl(m+1, 0));
    dp[0][0] = 1; // base case: empty string
    repr(i,0,n) {
        rep(j,m+1) {
            for(int k='A'; k<='Z'; k++) { // next input char
                int next_j = j;
                while(next_j >= 0 && s[next_j] != k) next_j = next_j-1>=0?kmp[next_j-1]:-1;
                
                if(next_j == -1) {
                    next_j++;
                    if(k == s[next_j]) next_j++;
                    (dp[i+1][next_j] += dp[i][j]) %= MD;
                } else if(next_j+1 < m) {
                    next_j++;
                    (dp[i+1][next_j] += dp[i][j]) %= MD;
                } else {
                    debug(i, j, (char) k, next_j, dp[i][j]);
                }

            }
        }
    }

    #if DEBUG==1
    putl("dp:");
    const int w = 9;
    setw(w); put("*"); rep(i,n+1) {setw(w), put(i);} putl("");
    setw(w); put("s"); rep(i,m+1) {setw(w), put(s[i]);} putl("");
    setw(w); put("kmp"); rep(i,m+1) {setw(w), put(kmp[i]);} putl("");
    setw(w); put("res"); rep(i,n+1) {
        LL ans = 0;
        repr(j,0,m) (ans += dp[i][j]) %= MD;
        setw(w), put((modpow(26, i) - ans + MD)%MD);
    } putl("");
    // setw(w); put("bf"); rep(i,n+1) {setw(w), put(bf(s, i));} putl("");
    rep(i,m+1) {
        setw(w); put(i);
        rep(j,n+1) {
            setw(w), put(dp[j][i]);
        }
        putl("");
    }
    #endif

    // LL ans2 = solve2(s, n);
    // putl(ans2);

    LL ans = modpow(26, n);
    LL rem = 0;
    repr(j,0,m+1) (rem += dp[n][j]) %= MD;
    ans = (ans - rem + MD) % MD;
    putl(ans);

    return 0;
}
