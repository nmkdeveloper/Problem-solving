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

struct Edge
{
    int u;
    int v;
    ll w;
    int id;
};

int N, M;
vector<Edge> adj;

void Read()
{
    cin >> N >> M;
    REP(i, M)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj.pb({u, v, w, i});
    }
}

namespace sub1
{
    /*
        Sort trong so tang dan
        Kruskal
    */

    bool cmp(const Edge& A, const Edge& B)
    {
        return A.w < B.w;
    }

    int Find(int u, vi& par)
    {
        if (par[u] == u)
        {
            return u;
        }
        return par[u] = Find(par[u], par);
    }

    bool Unite(int u, int v, vi& par, vi& siz)
    {
        u = Find(u, par);
        v = Find(v, par);
        if (u == v)
        {
            return false;
        }
        if (siz[u] < siz[v])
        {
            swap(u, v);
        }
        par[v] = u;
        siz[u] += siz[v];
        return true;
    }

    ll Krukal(int skip)
    {
        vi par(N + 1), siz(N + 1, 1);
        iota(all(par), 0);
        ll tw = 0, ec = 0;
        REP(i, M)
        {
            if (adj[i].id == skip)
            {
                continue;
            }
            if(Unite(adj[i].u, adj[i].v, par, siz))
            {
                tw += adj[i].w;
                ec ++;
            }
        }
        if (ec == N - 1)
        {
            return tw;
        }
        return -1;
    }

    void Solve()
    {
        vector<Edge> og = adj;
        sort(all(adj), cmp);
        REP(i, M)
        {
            cout << Krukal(og[i].id) << endl;
        }
    }
}

namespace sub2
{
    bool cmp(const Edge& A, const Edge& B)
    {
        return A.w < B.w;
    }

    int Find(int u, vi& par)
    {
        if (par[u] == u)
        {
            return u;
        }
        return par[u] = Find(par[u], par);
    }

    bool Unite(int u, int v, vi& par, vi& siz)
    {
        u = Find(u, par);
        v = Find(v, par);
        if (u == v)
        {
            return false;
        }
        if (siz[u] < siz[v])
        {
            swap(u, v);
        }
        par[v] = u;
        siz[u] += siz[v];
        return true;
    }

    void Solve()
    {
        vector<Edge> sorted = adj;
        sort(all(sorted), cmp);
        vi par(N + 1), siz(N + 1, 1);
        iota(all(par), 0);
        ll tw = 0;
        int ec = 0;
        vector<Edge> mst;
        vector<Edge> nonmst;
        vb inmst (M, false);
        REP(i, M)
        {
            if (Unite(sorted[i].u, sorted[i].v, par, siz))
            {
                tw += sorted[i].w;
                inmst[sorted[i].id] = true;
                mst.pb(sorted[i]);
                ec ++;
            }
            else
            {
                nonmst.pb(sorted[i]);
            }
        }
        if (ec < N - 1)
        {
            REP(i, M)
            {
                cout << -1 << endl;
            }
            return;
        }
        REP(i, M)
        {
            int cur = adj[i].id;
            if (!inmst[cur])
            {
                cout << tw << endl;
            }
            else
            {
                vi curpar(N + 1), cursiz(N + 1, 1);
                iota(all(curpar), 0);
                for (const auto& e : mst)
                {
                    if (e.id == cur)
                    {
                        continue;
                    }
                    Unite(e.u, e.v, curpar, cursiz);
                }
                ll repw = -1;
                for (const auto& e : nonmst)
                {
                    if (Find(e.u, curpar) != Find(e.v, curpar))
                    {
                        repw = e.w;
                        break;
                    }
                }
                cout << ((repw == -1) ? -1 : tw - adj[i].w + repw) << endl;
            }
        }
    }
}

void Solve()
{
    if (N <= 2000 && M <= 2000)
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
    File("DUPHONG");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
