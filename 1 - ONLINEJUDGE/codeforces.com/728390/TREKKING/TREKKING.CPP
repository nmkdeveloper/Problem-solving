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


int N, M, Q;
vll S;

void Read()
{
    cin >> N >> M >> Q;
        S.resize(N + 1);
        FOR(i, 1, N)
        {
            cin >> S[i];
        }
}

namespace sub1
{
    struct Edge
    {
        int v;
        ll w;
    };

    vector<vector<Edge>> adj;

    void Read()
    {
        adj.resize(N + 1);
        REP(i, M)
        {
            int u, v;
            ll w;
            cin >> u >> v >> w;
            adj[u].pb({v, w});
            adj[v].pb({u, w});
        }
    }

    vb visited;
    vll c;
    void DFS(const int& u, const ll& x)
    {
        visited[u] = true;
        c.pb(S[u]);
        for (const Edge& e : adj[u])
        {
            if (!visited[e.v] && e.w <= x)
            {
                DFS(e.v, x);
            }
        }
    }

    void Solve()
    {
        Read();
        while(Q --)
        {
            int type;
            cin >> type;
            if (type == 1)
            {
                int i;
                ll s;
                cin >> i >> s;
                S[i] = s;
            }
            else
            {
                int v, x, k;
                cin >> v >> x >> k;
                visited.assign(N + 1, false);
                c.clear();
                DFS(v, x);
                if (sz(c) < k)
                {
                    cout << -1 << endl;
                    continue;
                }
                sort(all(c), greater<ll>());
                cout << c[k - 1] << endl;
            }
        }
    }
}

namespace sub2
{
    struct Edge
    {
        int u;
        int v;
        ll w;
    };

    vector<Edge> adj;

    struct Query
    {
        int v;
        ll x;
        int k;
        int id;
    };

    vector<Query> query;

    bool Sortedge(const Edge& A, const Edge& B)
    {
        return A.w < B.w;
    }

    bool Sortquery(const Query& A, const Query& B)
    {
        return A.x < B.x;
    }

    void Read()
    {
        REP(i, M)
        {
            int u, v;
            ll w;
            cin >> u >> v >> w;
            adj.pb({u, v, w});
        }
    }

    vi Par;
    vll Siz;

    int Find(int u)
    {
        if (Par[u] == u)
        {
            return u;
        }
        return Par[u] = Find(Par[u]);
    }

    void Unite(int u, int v)
    {
        u = Find(u);
        v = Find(v);
        if (u != v)
        {
            Par[v] = u;
            Siz[u] = max(Siz[u], Siz[v]);
        }
    }

    void Solve()
    {
        Read();
        REP(i, Q)
        {
            int type;
            int v;
            ll x;
            int k;
            cin >> type >> v >> x >> k;
            query.pb({v, x, k, i});
        }
        sort(all(adj), Sortedge);
        sort(all(query), Sortquery);
        Par.resize(N + 1);
        Siz.resize(N + 1);
        FOR(i, 1, N)
        {
            Par[i] = i;
            Siz[i] = S[i];
        }
        vll ans(Q);
        int idx = 0;
        for (const Query& q : query)
        {
            while(idx < M && adj[idx].w <= q.x)
            {
                Unite(adj[idx].u, adj[idx].v);
                idx ++;
            }
            ans[q.id] = Siz[Find(q.v)];
        }
        REP(i, Q)
        {
            cout << ans[i] << endl;
        }
    }
}

void Solve()
{
    if (N <= 2000)
    {
        sub1::Solve();
    }
    else
    {
        sub2::Solve();
    }
}

int main()
{
    fixIO();
    File("TREKKING");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
