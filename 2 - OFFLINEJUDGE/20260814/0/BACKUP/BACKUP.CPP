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
    int v;
    int w;
};

const int LOG = 17; // log_{2}(10000);
int N, Q;
vector<vector<Edge>> adj;
vi parent, sizeset;

int Find(int u)
{
    if (u == parent[u])
    {
        return u;
    }
    return parent[u] = Find(parent[u]);
}

void Unite(int u, int v)
{
    int root_u = Find(u);
    int root_v = Find(v);
    if (sizeset[root_u] < sizeset[root_v])
    {
        swap(root_u, root_v);
    }
    parent[root_v] = root_u;
    sizeset[root_u] += sizeset[root_v];
}

void Read()
{
    cin >> N >> Q;
    adj.resize(N + 1);
    FOR(i, 1, N - 1)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
}

vi depth;
vector<vi> minedge, up;

void DFS(int u, int p, int w)
{
    up[u][0] = p;
    minedge[u][0] = w;
    FOR(k, 1, LOG)
    {
        up[u][k] = up[up[u][k - 1]][k - 1];
        minedge[u][k] = min(minedge[u][k - 1], minedge[up[u][k - 1]][k - 1]);
    }
    for (auto e : adj[u])
    {
        int v = e.v;
        int w = e.w;
        if (v != p)
        {
            depth[v] = depth[u] + 1;
            DFS(v, u, w);
        }
    }
}

int LCA(int u, int v)
{
    if (u == v)
    {
        return 0;
    }
    int ans = INF;
    if (depth[u] < depth[v])
    {
        swap(u, v);
    }
    FORD(k, LOG, 0)
    {
        if (depth[u] - (1 << k) >= depth[v])
        {
            ans = min(ans, minedge[u][k]);
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
            ans = min(ans, minedge[u][k]);
            ans = min(ans, minedge[v][k]);
            u = up[u][k];
            v = up[v][k];
        }
    }
    ans = min(ans, minedge[u][0]);
    ans = min(ans, minedge[v][0]);
    return ans;
}

vb Removed;

void Restore(int x)
{
    Removed[x] = false;
    for (auto e : adj[x])
    {
        int v = e.v;
        if (!Removed[v])
        {
            Unite(x, v);
        }
    }
}

void Solve()
{
    Removed.resize(N + 1, false);
    sizeset.resize(N + 1, 1);
    parent.resize(N + 1);
    iota(all(parent), 0);
    depth.resize(N + 1);
    minedge.resize(N + 1, vi(LOG + 1));
    up.resize(N + 1, vi(LOG + 1));
    stack<pair<int, pii>> st;
    DFS(1, 1, INF);
    FOR(i, 1, Q)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int u, v;
            cin >> u >> v;
            st.push({t, {u, v}});
        }
        else
        {
            int u;
            cin >> u;
            st.push({t, {u, 0}});
            Removed[u] = true;
        }
    }
    FOR(u, 1, N)
    {
        if (!Removed[u])
        {
            for (auto e : adj[u])
            {
                int v = e.v;
                if (!Removed[v])
                {
                    Unite(u, v);
                }
            }
        }
    }
    vi res;
    while(st.size())
    {
        pair<int, pii> query = st.top();
        st.pop();
        if (query.fi == 1)
        {
            if (Removed[query.se.fi] || Removed[query.se.se] || Find(query.se.fi) != Find(query.se.se))
            {
                res.pb(-1);
            }
            else
            {
                res.pb(LCA(query.se.fi, query.se.se));
            }
        }
        else
        {
            Restore(query.se.fi);
        }
    }
    reverse(all(res));
    for (int val : res)
    {
        cout << val << endl;
    }
}

int main() 
{
    fixIO();
    File("BACKUP");
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