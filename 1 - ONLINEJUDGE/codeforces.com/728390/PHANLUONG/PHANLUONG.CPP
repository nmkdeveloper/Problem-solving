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

struct Query
{
    int s;
    int t;
};

struct Edge
{
    int u;
    int v;
};

int N, M, Q;
vector<vpii> adj;
vector<Query> query;
vector<Edge> edge;

void Read()
{
    cin >> N >> M >> Q;
    adj.resize(N + 1);
    edge.resize(M + 1);
    FOR(i, 1, M)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb({v, i});
        adj[v].pb({u, i});
        edge[i] = {u, v};
    }
    query.resize(Q + 1);
    FOR(i, 1, Q)
    {
        int s, t;
        cin >> s >> t;
        query[i] = {s, t};
    }
}

vi path;
vb visited;

bool DFS(const int& u, const int& t)
{
    if (u == t)
    {
        return true;
    }
    visited[u] = true;
    for (const auto& [v, i] : adj[u])
    {
        if (!visited[v])
        {
            path.pb(i);
            if (DFS(v, t))
            {
                return true;
            }
            path.pop_back();
        }
    }
    return false;
}

vi dir;

bool Check(int k)
{
    dir.assign(M + 1, 0);
    FOR(i, 1, k)
    {
        int s = query[i].s, t = query[i].t;
        if (s == t)
        {
            continue;
        }
        path.clear();
        visited.assign(N + 1, false);
        if (!DFS(s, t))
        {
            return false;
        }
        int cur = s;
        for (const auto& e : path)
        {
            int u = edge[e].u, v = edge[e].v;
            if (cur == u)
            {
                if (dir[e] == 2)
                {
                    return false;
                }
                dir[e] = 1;
                cur = v;
            }
            else
            {
                if (dir[e] == 1)
                {
                    return false;
                }
                dir[e] = 2;
                cur = u;
            }
        }
    }
    return true;
}

void Solve()
{
    int res = 0;
    int left = 1, right = Q;
    while(left <= right)
    {
        int mid = left + (right - left) / 2;
        if (Check(mid))
        {
            res = mid;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    cout << res;
}

int main()
{
    fixIO();
    File("PHANLUONG");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
