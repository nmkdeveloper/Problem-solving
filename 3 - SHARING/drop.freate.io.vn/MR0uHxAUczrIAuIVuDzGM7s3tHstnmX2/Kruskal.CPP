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
    int u;
    int v;
    ll w;
};

int N, M;
vector<Edge> adj;
vi parent,ussize;

void Read()
{
    cin >> N >> M;
    parent.resize(N + 1);
    ussize.resize(N + 1, 1);
    iota(all(parent), 0);
    FOR(i, 1, M)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj.pb({u, v, w});
    }
}

int Find(int u)
{
    if (u == parent[u])
    {
        return u;
    }
    return parent[u] = Find(parent[u]);
}

bool DSU(int u, int v)
{
    int root_u = Find(u);
    int root_v = Find(v);
    if (root_u == root_v)
    {
        return false;
    }
    if (ussize[root_u] < ussize[root_v])
    {
        swap(root_u, root_v);
    }
    parent[root_v] = root_u;
    ussize[root_u] += ussize[root_v];
    return true;
}

bool cmp(Edge a, Edge b)
{
    return a.w < b.w;
}

void Solve()
{
    sort(all(adj), cmp);
    int cnt = 0;
    ll total = 0;
    for (auto e : adj)
    {
        int u = e.u;
        int v = e.v;
        ll w = e.w;
        if (DSU(u, v))
        {
            total += w;
            cnt++;
        }
        if (cnt == N - 1)
        {
            break;
        }
    }
    if (cnt == N - 1)
    {
        cout << total;
    }
    else
    {
        cout << -1;
    }
}

int main() 
{
    fixIO();
    File("Kruskal");
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