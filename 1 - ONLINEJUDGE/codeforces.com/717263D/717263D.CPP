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

#define debug(x) clog << #x << " = " << (x) << endl

const int MAXARR = 1e7 + 15;
const int INF = 1e9 + 7;
const ll INF64 = 2e18 + 7;
const int MOD = 998244353;

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

int n, k, N;
vector<vi> adj;

void Read()
{
    cin >> n >> k;
    adj.assign(n + 1, vi());
    REP(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
}

vi siz, parent;
vb removed;
vi ord_dist;
vi fact, invfact;

int modpow(int a, int e)
{
    int res = 1;
    while (e)
    {
        if (e & 1)
            res = (ll)res * a % MOD;
        a = (ll)a * a % MOD;
        e >>= 1;
    }
    return res;
}

void ntt(vi &a, bool invert)
{
    int n_ = sz(a);
    for (int i = 1, j = 0; i < n_; i++)
    {
        int bit = n_ >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    for (int len = 2; len <= n_; len <<= 1)
    {
        int wlen = modpow(3, (MOD - 1) / len);
        if (invert)
            wlen = modpow(wlen, MOD - 2);
        for (int i = 0; i < n_; i += len)
        {
            ll w = 1;
            for (int j = 0; j < len / 2; j++)
            {
                int u = a[i + j];
                int v = (int)(a[i + j + len / 2] * w % MOD);
                int x = u + v;
                if (x >= MOD)
                    x -= MOD;
                int y = u - v;
                if (y < 0)
                    y += MOD;
                a[i + j] = x;
                a[i + j + len / 2] = y;
                w = w * wlen % MOD;
            }
        }
    }
    if (invert)
    {
        int inv_n = modpow(n_, MOD - 2);
        for (int &x : a)
            x = (ll)x * inv_n % MOD;
    }
}

void square(vi &a)
{
    int n_ = sz(a);
    if (n_ <= 64)
    {
        vi res(n_, 0);
        REP(i, n_)
        {
            if (a[i] == 0)
                continue;
            for (int j = 0; i + j < n_; j++)
            {
                if (a[j] == 0)
                    continue;
                res[i + j] = (res[i + j] + (ll)a[i] * a[j]) % MOD;
            }
        }
        a.swap(res);
        return;
    }
    ntt(a, false);
    REP(i, n_)
        a[i] = (ll)a[i] * a[i] % MOD;
    ntt(a, true);
}

void calc_size(int s, vi &order)
{
    stack<int> st;
    st.push(s);
    parent[s] = 0;
    while (sz(st))
    {
        int u = st.top();
        st.pop();
        order.pb(u);
        for (int v : adj[u])
        {
            if (v == parent[u] || removed[v])
                continue;
            parent[v] = u;
            st.push(v);
        }
    }
    FORD(i, sz(order) - 1, 0)
    {
        int u = order[i];
        siz[u] = 1;
        for (int v : adj[u])
        {
            if (v == parent[u] || removed[v])
                continue;
            siz[u] += siz[v];
        }
    }
}

int findCentroid(int s)
{
    vi order;
    calc_size(s, order);
    int total = siz[s];
    for (int u : order)
    {
        int mx = total - siz[u];
        for (int v : adj[u])
        {
            if (v == parent[u] || removed[v])
                continue;
            mx = max(mx, siz[v]);
        }
        if (mx <= total / 2)
            return u;
    }
    return s;
}

void Decompose(int s)
{
    int c = findCentroid(s);
    vector<vi> subtrees;
    vi all;
    all.pb(0);
    for (int v : adj[c])
    {
        if (removed[v])
            continue;
        vi vec;
        stack<tuple<int, int, int>> st;
        st.push({v, c, 1});
        while (sz(st))
        {
            auto [u, p, d] = st.top();
            st.pop();
            vec.pb(d);
            for (int to : adj[u])
            {
                if (to == p || removed[to])
                    continue;
                st.push({to, u, d + 1});
            }
        }
        subtrees.pb(vec);
        for (int d : vec)
            all.pb(d);
    }
    int maxd = 0;
    for (int d : all)
        maxd = max(maxd, d);
    int len = 1;
    while (len <= 2 * maxd)
        len <<= 1;
    vi F(len, 0);
    for (int d : all)
        F[d]++;

    square(F);
    for (auto &vec : subtrees)
    {
        int m = 0;
        for (int d : vec)
            m = max(m, d);
        int len2 = 1;
        while (len2 <= 2 * m)
            len2 <<= 1;
        vi G(len2, 0);
        for (int d : vec)
            G[d]++;
        square(G);
        for (int i = 1; i <= 2 * m; i++)
        {
            F[i] -= G[i];
            if (F[i] < 0)
                F[i] += MOD;
        }
    }
    for (int d = 1; d < len && d <= N; d++)
    {
        ord_dist[d] += F[d];
        if (ord_dist[d] >= MOD)
            ord_dist[d] -= MOD;
    }

    removed[c] = true;
    for (int v : adj[c])
    {
        if (!removed[v])
            Decompose(v);
    }
}

int C(int n_, int k_)
{
    if (k_ < 0 || k_ > n_)
        return 0;
    return (ll)fact[n_] * invfact[k_] % MOD * invfact[n_ - k_] % MOD;
}

void Solve()
{
    N = n - 1;

    siz.assign(n + 1, 0);
    parent.assign(n + 1, 0);
    removed.assign(n + 1, false);
    ord_dist.assign(n + 1, 0);

    fact.resize(n + 1);
    invfact.resize(n + 1);
    fact[0] = 1;
    FOR(i, 1, n)
        fact[i] = (ll)fact[i - 1] * i % MOD;
    invfact[n] = modpow(fact[n], MOD - 2);
    FORD(i, n - 1, 0)
        invfact[i] = (ll)invfact[i + 1] * (i + 1) % MOD;

    Decompose(1);

    ll ans = (ll)n * C(N, k) % MOD;
    FOR(d, 1, N)
    {
        ans = (ans + (ll)ord_dist[d] * C(N - d, k)) % MOD;
    }
    cout << ans;
}

int main()
{
    fixIO();
    File("717263D");
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
