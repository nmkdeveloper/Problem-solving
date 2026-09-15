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

#define BIT(n) (1UL << (n))
#define SET(k, n) ((n) | BIT(k))
#define CLEAR(k, n) ((n) & ~BIT(k))
#define TOGGLE(k, n) ((n) ^ BIT(k))
#define CHECK(k, n) (!!((n) & BIT(k)))
#define MSB(x) ((x) == 0 ? -1 : 63 - __builtin_clzll(x))

#define debug(x) clog << #x << " = " << (x) << endl

const int MAXARR = 1e7 + 15;
const int INF = 1e9 + 7;
const ll INF64 = 2e18 + 7;
const int MOD = 1e9 + 7;

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
vector<vll> c;
vector<vector<pil>> adj;

void Read()
{
    cin >> n >> k;
    c.resize(n, vll(n));
    adj.resize(n);
    REP(i, n)
    {
        REP(j, n)
        {
            cin >> c[i][j];
            if (i != j)
            {
                adj[i].pb({j, c[i][j]});
            }
        }
    }
}

vll Dijikstra(int s)
{
    vll Dist(n, INF64);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    Dist[s] = 0;
    pq.push({0, s});
    while (sz(pq))
    {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > Dist[u])
            continue;
        for (auto [v, w] : adj[u])
        {
            if (Dist[u] + w < Dist[v])
            {
                Dist[v] = Dist[u] + w;
                pq.push({Dist[v], v});
            }
        }
    }
    return Dist;
}

void Solve()
{
    vi ord(k);
    REP(i, k)
    {
        cin >> ord[i];
        ord[i] --;
    }
    vi imp;
    imp.pb(0);
    for (auto x : ord)
    {
        imp.pb(x);
    }
    int m = k + 1;
    vector<vll> d(m, vll(m, INF64));
    REP(i, m)
    {
        vll Dist = Dijikstra(imp[i]);
        REP(j, m)
        {
            d[i][j] = Dist[imp[j]];
        }
    }
    int f = (1 << k) - 1;
    vector<vll> dp(1 << k, vll(k + 1, INF64));
    FOR(i, 1, k)
    {
        dp[BIT(i - 1)][i] = d[0][i];
    }
    FOR(mask, 1, f)
    {
        FOR(i, 1, k)
        {
            if (!CHECK(i - 1, mask))
            {
                continue;
            }
            if (dp[mask][i] == INF64)
            {
                continue;
            }
            FOR(j, 1, k)
            {
                if (CHECK(j - 1, mask))
                {
                    continue;
                }
                int nmask = SET(j - 1, mask);
                dp[nmask][j] = min(dp[nmask][j], dp[mask][i] + d[i][j]);
            }
        }
    }
    ll ans = INF64;
    FOR(i, 1, k)
    {
        ans = min(ans, dp[f][i] + d[i][0]);
    }
    cout << ans;
}

int main()
{
    fixIO();
    File("716389B");
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
