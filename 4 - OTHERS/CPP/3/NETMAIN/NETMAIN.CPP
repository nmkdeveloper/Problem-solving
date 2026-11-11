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

int N, Q;
vll a;

void Read()
{
    cin >> N >> Q;
    a.resize(N + 1);
    FOR(i, 1, N)
    {
        cin >> a[i];
    }
}

namespace Sub1
{
    vector<vi> adj;

    pll Countbfs(int start)
    {
        ll cnt = 1, maxserver = a[start];
        vb visited(N + 1, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        while(sz(q))
        {
            int u = q.front();
            q.pop();
            for (auto v : adj[u])
            {
                if (v != -1 && !visited[v])
                {
                    cnt ++;
                    maxserver = max(maxserver, a[v]);
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        return {cnt, maxserver};
    }

    void Solve()
    {
        adj.resize(N + 1);
        while(Q --)
        {
            int type;
            cin >> type;
            if (type == 1)
            {
                int u, v;
                cin >> u >> v;
                adj[u].pb(v);
                adj[v].pb(u);
            }
            else if (type == 2)
            {
                int u, v;
                cin >> u >> v;
                for (auto &e : adj[u])
                {
                    if (e == v)
                    {
                        e = -1;
                        break;
                    }
                }
                for (auto &e : adj[v])
                {
                    if (e == u)
                    {
                        e = -1;
                        break;
                    }
                }
            }
            else if (type == 3)
            {
                int u;
                ll x;
                cin >> u >> x;
                a[u] = x;
            }
            else
            {
                int u;
                cin >> u;
                pll ans = Countbfs(u);
                cout << ans.fi << ' ' << ans.se << endl;
            }
        }
    }

    void Init()
    {
        Solve();
    }
}

namespace Sub2
{
    vll siz, par;
    vector<multiset<ll>> maxserver;

    int Find(int u)
    {
        if (par[u] == u)
        {
            return u;
        }
        return par[u] = Find(par[u]);
    }

    void Solve()
    {
        while(Q --)
        {
            int type;
            cin >> type;
            if (type == 1)
            {
                int u, v;
                cin >> u >> v;
                int rootu = Find(u);
                int rootv = Find(v);
                if (rootu != rootv)
                {
                    if (siz[rootu] < siz[rootv])
                    {
                        swap(rootu, rootv);
                    }
                    par[rootv] = rootu;
                    siz[rootu] += siz[rootv];
                    if (sz(maxserver[rootu]) < sz(maxserver[rootv]))
                    {
                        maxserver[rootu].swap(maxserver[rootv]);
                    }
                    for (ll x : maxserver[rootv])
                    {
                        maxserver[rootu].insert(x);
                    }
                    maxserver[rootv].clear();
                }
            }
            else if (type == 3)
            {
                int u, x;
                cin >> u >> x;
                int rootu = Find(u);
                auto it = maxserver[rootu].find(a[u]);
                if (it != maxserver[rootu].end())
                {
                    maxserver[rootu].erase(it);
                }
                a[u] = x;
                maxserver[rootu].insert(x);
            }
            else
            {
                int u;
                cin >> u;
                int rootu = Find(u);
                cout << siz[rootu] << ' ' << *maxserver[rootu].rbegin() << endl;
            }
        }
    }

    void Init()
    {
        siz.resize(N + 1);
        par.resize(N + 1);
        maxserver.resize(N + 1);
        FOR(i, 1, N)
        {
            siz[i] = 1;
            par[i] = i;
            maxserver[i].insert(a[i]);
        }
        Solve();
    }
}

void Solve()
{
    if (N <= 2000 && Q <= 2000)
    {
        Sub1::Init();
    }
    else
    {
        Sub2::Init();
    }
}

int main()
{
    fixIO();
    File("NETMAIN");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
