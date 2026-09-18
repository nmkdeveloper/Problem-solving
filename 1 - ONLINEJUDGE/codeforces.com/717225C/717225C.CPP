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
    ll b;
};

struct Query
{
    int u;
    int v;
    ll x;
    int id;
};

int n, m, q;

vector<Edge> adj;
vector<Query> qry;

void Read()
{
    cin >> n >> m >> q;
    REP(i, m)
    {
        int u, v;
        ll b;
        cin >> u >> v >> b;
        adj.pb({u, v, b});
        // adj.pb({v, u, b});
    }
    REP(i, q)
    {
        int u, v;
        ll x;
        cin >> u >> v >> x;
        qry.pb({u, v, x, i + 1});
    }
}

bool cmp_adj(Edge a, Edge b)
{
    return a.b > b.b;
}

bool cmp_qry(Query a, Query b)
{
    return a.x > b.x;
}

vi Parent, sizeParent;

int Find(int u)
{
    if (Parent[u] == u)
    {
        return u;
    }
    return Parent[u] = Find(Parent[u]);
}

void Unite(int u, int v)
{
    u = Find(u);
    v = Find(v);
    if (u == v)
    {
        return;
    }
    if (sizeParent[u] < sizeParent[v])
    {
        swap(u, v);
    }
    Parent[v] = u;
    sizeParent[u] += sizeParent[v];
}

vb res;

void Solve()
{
    Parent.resize(n + 1);
    iota(all(Parent), 0);
    sizeParent.resize(n + 1, 1);
    sort(all(adj), cmp_adj);
    sort(all(qry), cmp_qry);
    res.resize(q + 1, false);
    int Cur = 0;
    REP(i, q)
    {
        int u = qry[i].u;
        int v = qry[i].v;
        ll x = qry[i].x;
        int id = qry[i].id;
        while(Cur < m && adj[Cur].b >= x )
        {
            Unite(adj[Cur].u, adj[Cur].v);
            Cur ++;
        }
        res[id] = (Find(u) == Find(v));
    }
    FOR(i, 1, q)
    {
        cout << (res[i] ? 1 : 0) << endl;
    }
}

int main()
{
    fixIO();
    File("717225C");
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
