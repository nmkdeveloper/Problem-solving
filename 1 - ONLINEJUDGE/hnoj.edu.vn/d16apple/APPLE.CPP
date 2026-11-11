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
//    return a[Randint(0, sz(a) - 1)];
//int Randvectorint(const vi& a){
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

const int OFFSET = 1e5 + 5;
int N;
vector<vi> adj;

void Read(){
    cin >> N;
    adj.resize(4 * OFFSET);
    REP(i, N){
        int x, y;
        cin >> x >> y;
        y += OFFSET;
        adj[x].pb(y);
        adj[y].pb(x);
    }
}

vb visited;
ll cntx, cnty;

void DFS(int u){
    visited[u] = true;
    if (u <= OFFSET) cntx ++;
    else cnty ++;
    for (const auto& v : adj[u]){
        if (!visited[v]){
            DFS(v);
        }
    }
}

void Solve(){
    visited.assign(4 * OFFSET, false);
    ll ans = 0;
    FOR(i, 1, OFFSET){
        if (sz(adj[i]) && !visited[i]){
            cntx = 0;
            cnty = 0;
            DFS(i);
            ans += cntx * cnty;
        }
    }
    cout << ans - (1LL * N);
}

signed main(){
    Fast();
    File("APPLE");
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
