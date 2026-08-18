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

const int MAXARR = 1e7 + 15;
const int INF = 1e9 + 7;
const ll INF64 = 2e18 + 7;
const int MOD = 1e9 + 7;

#define debug(x) clog << #x << " = " << (x) << endl

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
    int u, v;
    ll w;
    int id;
};

struct TreeEdge
{
    int to;
    ll w;
    int id;
};

bool cmp(Edge a, Edge b)
{
    return a.w < b.w;
}

int n, m;
vector<Edge> adj;

void Read()
{
    cin >> n >> m;
    FOR(i, 1, m)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj.pb({u, v, w, i});
    }
}

vi unionsetsize, parent;

int Find(int u)
{
    if (u == parent[u])
    {
        return u;
    }
    return parent[u] = Find(parent[u]);
}

bool Unite(int u, int v)
{
    int root_u = Find(u);
    int root_v = Find(v);
    if (root_u == root_v)
    {
        return false;
    }
    if (unionsetsize[root_u] < unionsetsize[root_v])
    {
        swap(root_u, root_v);
    }
    parent[root_v] = root_u;
    unionsetsize[root_u] += unionsetsize[root_v];
    return true;
}

vb in_mst;
vector<vector<TreeEdge>> tree;
vi edgeChild, tin, tout;
int timer = 0;

const int LOG = 20;
vi depth;
vector<vi> up;
vector<vector<ll>> mx;

void DFS(int u, int p, ll w)
{
    tin[u] = ++ timer;

    up[u][0] = p;
    mx[u][0] = w;

    FOR(k, 1, LOG)
    {
        up[u][k] = up[up[u][k - 1]][k - 1];
        mx[u][k] = max(
            mx[u][k - 1],
            mx[up[u][k - 1]][k - 1]
        );
    }

    for (auto [v, weight, eid] : tree[u])
    {
        if (v != p)
        {
            depth[v] = depth[u] + 1;
            edgeChild[eid] = v;
            DFS(v, u, weight);
        }
    }
    tout[u] = timer;
}

ll LCA(int u, int v)
{
    ll ans = 0;
    if (depth[u] < depth[v])
    {
        swap(u, v);
    }
    FORD(k, LOG, 0)
    {
        if (depth[u] - (1 << k) >= depth[v])
        {
            ans = max(ans, mx[u][k]);
            u = up[u][k];
        }
    }
    if (u == v)
    {
        return ans;
    }
    FORD(k, LOG, 0)
    {
        if (up[u][k] != up[v][k])
        {
            ans = max(ans, mx[u][k]);
            ans = max(ans, mx[v][k]);
            u = up[u][k];
            v = up[v][k];
        }
    }
    ans = max(ans, mx[u][0]);
    ans = max(ans, mx[v][0]);
    return ans;
}

bool isAncestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

ll HandleQuery(int a, int b, int eid)
{
    if (!in_mst[eid])
    {
        return LCA(a, b);
    }
    int v = edgeChild[eid];
    bool ina = isAncestor(v, a);
    bool inb = isAncestor(v, b);
    if (ina == inb)
    {
        return LCA(a, b);
    }

    // Do something crazy before return

    return -1;
}

void Solve()
{
    sort(all(adj), cmp);
    edgeChild.resize(m + 1);
    tin.resize(n + 1);
    tout.resize(n + 1);
    unionsetsize.resize(n + 1, 1);
    parent.resize(n + 1);
    tree.resize(n + 1);
    in_mst.resize(m + 1, false);
    iota(all(parent), 0);
    for (Edge e : adj)
    {
        if(Unite(e.u, e.v))
        {
            in_mst[e.id] = true;
            tree[e.u].pb({e.v, e.w, e.id});
            tree[e.v].pb({e.u, e.w, e.id});
        }
    }
    up.resize(n + 1, vi(LOG + 1));
    mx.resize(n + 1, vector<ll>(LOG + 1));
    depth.resize(n + 1);
    depth[1] = 0;
    DFS(1, 1, 0);
}

int main() 
{
    fixIO();
    File("ROUTE");
    Read();
    Solve();
    return 0;
}

/**
 *  "Frieren: Vay theo cau chung ta phai lam gi de nguoi khac nho den chung ta chu?
 *   Himmel:  Cung khong co gi to tac, do la hay thay doi cuoc doi cua ai do 
 *            du chi mot chut. Toi thay chi can nhu vay la du roi."
 *
 *                                                   — Sousou no Frieren —
 *  =======================================================================
 *  Template by : Nguyen Minh Khoi (github/nmkdeveloper)
 *  Created     : 2026.08.11
 */