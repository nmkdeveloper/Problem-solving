#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ull = unsigned long long;
using vi  = vector<int>;
using vll = vector<long long>;
using vb  = vector<bool>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define FOR(a, b, c) for (auto a = (b); a <= (c); a++)
#define FORD(a, b, c) for (auto a = (b); a >= (c); a--)
#define REP(i, n) for (auto i = 0; i < (n); i++)
#define REPD(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()

const char el = '\n';

//mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
//
//int Randint(int minium, int maxium){
//    return uniform_int_distribution<int>(minium, maxium)(rng);
//}
//
//ll Randll(ll minium, ll maxium){
//    return uniform_int_distribution<ll>(minium, maxium)(rng);
//}
//
//int Randvectorint(const vi& a){
//    return a[Randint(0, sz(a) - 1)];
//}
//
//ll Randvectorll(const vll& a){
//    return a[Randint(0, sz(a) - 1)];
//}

void Fast(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}

void File(const string& filename = ""){
    if(fopen((filename +".INP").c_str(), "r")){
        freopen((filename + ".INP").c_str(), "r", stdin);
        freopen((filename + ".OUT").c_str(), "w", stdout);
    }
}


struct Pathinfo
{
    int u;
    int v;
    ll w;
    ll passed;
};

int N, M;
vector<vi> adj;
vector<Pathinfo> path;

bool Findpath(int u, int p, int tar, ll& passed){
    passed |= (1LL << u);
    if (u == tar){
        return true;
    }
    for (auto v : adj[u]){
        if (v != p){
            if (Findpath(v, u, tar, passed)) return true;
        }
    }
    passed &= ~(1LL << u);
    return false;
}

void Read(){
    cin >> N >> M;
    adj.resize(N + 1);
    REP(i, N - 1){
        int u, v;
        cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }
    REP(i, M){
        int u, v;
        ll w;
        cin >> u >> v >> w;
        path.pb({u, v, w, 0});
        Findpath(u, 0, v, path[i].passed);
    }
}

void Solve(){
    const int sz = 1 << (N + 1);
    vll dp(sz, 0);
    int maxmask = (1 << (N + 1)) - 1;
    for (const auto& p : path){
        ll maskp = p.passed;
        ll w = p.w;
        FORD(mask, 1LL * maxmask, 0LL){
            if ((mask & maskp) == 0){
                dp[mask | maskp] = max(dp[mask | maskp], dp[mask] + w);
            }
        }
    }
    ll ans = 0;
    FOR(mask, 0LL, 1LL * maxmask){
        ans = max(ans, dp[mask]);
    }
    cout << ans;
}

signed main(){
    Fast();
    File("DUAGHE");
    Read();
    Solve();
    return 0;
}

/*
    ---------------------------------------------------
               Code By github/toiyeuyuriiiii
                   I Love You My Girl <3
    ---------------------------------------------------
*/
