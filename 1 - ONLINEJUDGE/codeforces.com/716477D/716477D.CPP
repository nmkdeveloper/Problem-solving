#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<bool> vb;
typedef vector<string> vs;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef map<int, int> mii;
typedef map<ll, ll> mll;
typedef set<int> si;
typedef set<ll> sll;
typedef priority_queue<int> max_heap_i;
typedef priority_queue<int, vi, greater<int>> min_heap_i;
typedef priority_queue<ll> max_heap_ll;
typedef priority_queue<ll, vll, greater<ll>> min_heap_ll;

#define FOR(a, b, c) for (int a = (b); a <= (c); a++)
#define FORD(a, b, c) for (int a = (b); a >= (c); a--)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define REPD(i, n) for (int i = (n) - 1; i >= 0; i--)
#define endl '\n'
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()

#define BIT(n) (1 << (n))
#define SET(k, n) ((n) | BIT(k))
#define CLEAR(k, n) ((n) & ~BIT(k))
#define TOGGLE(k, n) ((n) ^ BIT(k))
#define CHECK(k, n) (!!((n) & BIT(k)))
#define MSB(x) ((x) == 0 ? -1 : 63 - __builtin_clzll(x))

const int MAXARR = 1e7 + 15;
const int INF = 1e9 + 7;
const ll INF64 = 2e18 + 7;
const int MOD = 998244353;
const int G = 3;

void fixIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}

void File(const string &fileName = "")
{
    if (fopen((fileName + ".INP").c_str(), "r"))
    {
        freopen((fileName + ".INP").c_str(), "r", stdin);
        freopen((fileName + ".OUT").c_str(), "w", stdout);
    }
}

int n, k;
vector<vi> adj;

void Read()
{
    cin >> n >> k;
    adj.assign(n + 1, vi());
    REP(i, n - 1)
    {
        int u, v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
}

int pw(int a, int b)
{
    int r = 1;
    while (b)
    {
        if (b & 1) r = (ll)r * a % MOD;
        a = (ll)a * a % MOD;
        b >>= 1;
    }
    return r;
}

void ntt(vi &a, bool inv)
{
    int N = sz(a);
    for (int i = 1, j = 0; i < N; i++)
    {
        int bit = N >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= N; len <<= 1)
    {
        int w = pw(G, (MOD - 1) / len);
        if (inv) w = pw(w, MOD - 2);
        int half = len >> 1;
        for (int i = 0; i < N; i += len)
        {
            int wn = 1;
            for (int j = 0; j < half; j++)
            {
                int u = a[i + j];
                int v = (ll)a[i + j + half] * wn % MOD;
                int x = u + v; if (x >= MOD) x -= MOD;
                int y = u - v; if (y < 0) y += MOD;
                a[i + j] = x;
                a[i + j + half] = y;
                wn = (ll)wn * w % MOD;
            }
        }
    }
    if (inv)
    {
        int ni = pw(N, MOD - 2);
        for (int &x : a) x = (ll)x * ni % MOD;
    }
}

vi mul(const vi &a, const vi &b)
{
    if (a.empty() || b.empty()) return {};
    int need = sz(a) + sz(b) - 1;
    if (min(sz(a), sz(b)) <= 60)
    {
        vi c(need, 0);
        for (int i = 0; i < sz(a); i++) if (a[i])
            for (int j = 0; j < sz(b); j++) if (b[j])
                c[i + j] = (c[i + j] + (ll)a[i] * b[j]) % MOD;
        return c;
    }
    int N = 1;
    while (N < need) N <<= 1;
    vi fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(N); fb.resize(N);
    ntt(fa, false); ntt(fb, false);
    for (int i = 0; i < N; i++) fa[i] = (ll)fa[i] * fb[i] % MOD;
    ntt(fa, true);
    fa.resize(need);
    return fa;
}

vi sub, cnt;
vb del;

int calcSz(int root)
{
    vector<pii> stk;
    vi ord, par;
    stk.pb({root, -1});
    while (!stk.empty())
    {
        auto [u, p] = stk.back(); stk.pop_back();
        ord.pb(u);
        par.pb(p);
        sub[u] = 1;
        for (int v : adj[u]) if (v != p && !del[v]) stk.pb({v, u});
    }
    for (int i = sz(ord) - 1; i >= 0; i--)
    {
        int u = ord[i], p = par[i];
        if (p != -1) sub[p] += sub[u];
    }
    return sz(ord);
}

int centroid(int root, int total)
{
    int u = root, p = -1;
    while (true)
    {
        int nxt = -1;
        for (int v : adj[u]) if (v != p && !del[v] && sub[v] * 2 > total)
        {
            nxt = v; break;
        }
        if (nxt == -1) return u;
        p = u; u = nxt;
    }
}

void dfs(int root, int p0, int d0, vi &ds)
{
    vector<tuple<int,int,int>> stk;
    stk.pb({root, p0, d0});
    while (!stk.empty())
    {
        auto [u, p, d] = stk.back(); stk.pop_back();
        ds.pb(d);
        for (int v : adj[u]) if (v != p && !del[v]) stk.pb({v, u, d + 1});
    }
}

void decomp(int entry)
{
    int total = calcSz(entry);
    int c = centroid(entry, total);
    del[c] = true;
    vi all;
    all.pb(0);
    for (int v : adj[c]) if (!del[v])
    {
        vi s;
        dfs(v, c, 1, s);
        int mx = 0;
        for (int d : s) if (d > mx) mx = d;
        vi B(mx + 1, 0);
        for (int d : s) B[d]++;
        for (int d : s) all.pb(d);
        vi sq = mul(B, B);
        int lim = min(sz(sq), sz(cnt));
        for (int i = 0; i < lim; i++)
        {
            cnt[i] -= sq[i];
            if (cnt[i] < 0) cnt[i] += MOD;
        }
    }
    int mx = 0;
    for (int d : all) if (d > mx) mx = d;
    vi A(mx + 1, 0);
    for (int d : all) A[d]++;
    vi sqA = mul(A, A);
    int lim = min(sz(sqA), sz(cnt));
    for (int i = 0; i < lim; i++)
    {
        cnt[i] += sqA[i];
        if (cnt[i] >= MOD) cnt[i] -= MOD;
    }
    for (int v : adj[c]) if (!del[v]) decomp(v);
}

vi fac, ifac;

void pre()
{
    fac.assign(n + 1, 1);
    ifac.assign(n + 1, 1);
    FOR(i, 1, n) fac[i] = (ll)fac[i - 1] * i % MOD;
    ifac[n] = pw(fac[n], MOD - 2);
    FORD(i, n - 1, 0) ifac[i] = (ll)ifac[i + 1] * (i + 1) % MOD;
}

int C(int N, int K)
{
    if (K < 0 || K > N || N < 0) return 0;
    return (ll)fac[N] * ifac[K] % MOD * ifac[N - K] % MOD;
}

void Solve()
{
    pre();
    cnt.assign(n, 0);
    sub.assign(n + 1, 0);
    del.assign(n + 1, false);
    decomp(1);
    ll ans = 0;
    REP(d, n)
    {
        int rem = n - 1 - d;
        if (rem < k) break;
        ans = (ans + (ll)cnt[d] * C(rem, k)) % MOD;
    }
    cout << ans;
}

int main()
{
    fixIO();
    File("717225B");
    Read();
    Solve();
    return 0;
}

/**
 *  "Frieren: Vay theo cau chung ta phai lam gi de nguoi khac nho den chung ta chu?
 *   Himmel:  Cung khong co gi to tac, do la hay thay doi cuoc doi cua ai do
 *            du chi mot chut. Toi thay chi can nhu vay la du roi."
 *
 *                                                   - Sousou no Frieren -
 *  =======================================================================
 *  Template by : Nguyen Minh Khoi (github/nmkdeveloper)
 *  Created     : 2026.09.14
 */
