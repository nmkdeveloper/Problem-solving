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

struct Edge
{
    int v;
    int id;
};

int N, M, Q;
vector<vector<Edge>> adj;

void Read()
{
    cin >> N >> M >> Q;
    adj.resize(N + 1);
    FOR(i, 1, M)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb({v, i});
        adj[v].pb({u, i});
    }
}

const int MAXTREE = (int) 2e5 + 7;
int tin[MAXTREE], low[MAXTREE], timer = 0;
vi st;
int nodecnt;
vi tree[MAXTREE];

void Tarjan(int u, int pe = 0)
{
    tin[u] = low[u] = ++ timer;
    st.pb(u);
    for (const Edge& e : adj[u])
    {
        if (e.id == pe)    
        {
            continue;
        }
        int v = e.v;
        if (tin[v])
        {
            low[u] = min(low[u], tin[v]);
        }
        else
        {
            Tarjan(v, e.id);
            low[u] = min(low[u], low[v]);
            if (low[u] >= tin[u])
            {
                int block = ++ nodecnt;
                tree[u].pb(block);
                tree[block].pb(u);
                while(true)
                {
                    int x = st.back();
                    st.pop_back();
                    tree[x].pb(block);
                    tree[block].pb(x);
                    if (x == v)
                    {
                        break;
                    }
                }
            }
        }
    }
}

const int MAXLOG = 19;
int up[MAXTREE][MAXLOG];
int depth[MAXTREE];

void DFSLCA(int u, int p = 0)
{
    depth[u] = depth[p] + 1;
    up[u][0] = p;
    FOR(j, 1, MAXLOG - 1)
    {
        up[u][j] = up[up[u][j - 1]][j - 1];
    }
    for (const int v : tree[u])
    {
        if (v != p)
        {
            DFSLCA(v, u);
        }
    }
}

int Getlca(int u, int v)
{
    if (depth[u] < depth[v])
    {
        swap(u, v);
    }
    FORD(j, 18, 0)
    {
        if (depth[u] - (1 << j) >= depth[v])
        {
            u = up[u][j];
        }
    }
    if (u == v)
    {
        return u;
    }
    FORD(j, 18, 0)
    {
        if (up[u][j] != up[v][j])
        {
            u = up[u][j];
            v = up[v][j];
        }
    }
    return up[u][0];
}

int diff[MAXTREE];

void DFS(int u, int p = 0)
{
    for (int v : tree[u])
    {
        if (v != u)
        {
            DFS(v, u);
            diff[u] += diff[v];
        }
    }
}

void Solve()
{
    nodecnt = N;
    Tarjan(1);
    DFSLCA(1);
    while(Q --)
    {
        int u, v;
        cin >> u >> v;
        int l = Getlca(u, v);
        diff[u] ++;
        diff[v] ++;
        diff[l] --;
        if (up[l][0])
        {
            diff[up[l][0]] --;
        }
    }
    DFS(1);
    FOR(i, 1, N)
    {
        cout << diff[i] << endl;
    }
}

int main()
{
    fixIO();
    File("1047");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
