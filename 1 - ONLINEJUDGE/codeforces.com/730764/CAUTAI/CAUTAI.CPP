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

#define BIT(n) (1ULL << (n))
#define SET(k, n) ((n) |  BIT(k))
#define CLEAR(k, n) ((n) & ~BIT(k))
#define TOGGLE(k, n) ((n) ^  BIT(k))
#define CHECK(k, n) (((n) & BIT(k)) != 0)
#define MSB(x) ((x) == 0 ? -1 : 63 - __builtin_clzll((ull)(x)))

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

struct EdgeVW
{
    int v;
    ll w;
};

struct EdgeUVW
{
    int u;
    int v;
    ll w;
};

struct Query
{
    int v;
    ll h, x;
};

int n, m, q;
vector<vector<EdgeVW>> adj;
vll a;
vector<Query> queries;
vector<EdgeUVW> edges;

ll pref = -INF64;
bool sub2passed = true;

void Read()
{
    cin >> n >> m >> q;
    adj.resize(n + 1);
    edges.resize(m);
    REP(i, m)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    a.resize(n + 1);
    FOR(i, 1, n)
    {
        cin >> a[i];
    }
    queries.resize(q);
    REP(i, q)
    {
        cin >> queries[i].v >> queries[i].h >> queries[i].x;
    }

    if (q > 0)
    {
        pref = queries[0].h;
        FOR(i, 1, q - 1)
        {
            if (queries[i].h != pref)
            {
                sub2passed = false;
                break;
            }
        }
    }
}

namespace Sub1
{
    ll Solvequery(int v, ll h, ll x)
    {
        vb visited(n + 1, false);
        queue<int> que;
        que.push(v);
        visited[v] = true;
        ll ans = 0;
        while (sz(que))
        {
            int u = que.front();
            que.pop();
            if (a[u] <= x)
            {
                ans++;
            }
            for (const auto& e : adj[u])
            {
                if (e.w >= h && !visited[e.v])
                {
                    visited[e.v] = true;
                    que.push(e.v);
                }
            }
        }
        return ans;
    }

    void Solve()
    {
        for (const auto& [v, h, x] : queries)
        {
            cout << Solvequery(v, h, x) << endl;
        }
    }

    void Handle()
    {
        Solve();
    }
}

namespace Sub2
{
    void Solve()
    {
        ll h = pref;
        vector<vi> g(n + 1);
        for (const auto& e : edges)
        {
            if (e.w >= h)
            {
                g[e.u].pb(e.v);
                g[e.v].pb(e.u);
            }
        }
        vi comp(n + 1, 0);
        vector<vll> compval;
        int curcomp = 0;
        FOR(i, 1, n)
        {
            if (!comp[i])
            {
                curcomp++;
                vll vals;
                queue<int> que;
                comp[i] = curcomp;
                que.push(i);
                while (sz(que))
                {
                    int u = que.front();
                    que.pop();
                    vals.pb(a[u]);
                    for (int v : g[u])
                    {
                        if (!comp[v])
                        {
                            comp[v] = curcomp;
                            que.push(v);
                        }
                    }
                }
                sort(all(vals));
                compval.pb(vals);
            }
        }
        for (const auto& qr : queries)
        {
            int root = comp[qr.v] - 1;
            auto it = upper_bound(all(compval[root]), qr.x);
            cout << (it - compval[root].begin()) << endl;
        }
    }

    void Handle()
    {
        Solve();
    }
}

void Solve()
{
    if (sub2passed)
    {
        Sub2::Handle();
    }
    else
    {
        Sub1::Handle();
    }
}

int main()
{
    fixIO();
    File("CAUTAI");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
