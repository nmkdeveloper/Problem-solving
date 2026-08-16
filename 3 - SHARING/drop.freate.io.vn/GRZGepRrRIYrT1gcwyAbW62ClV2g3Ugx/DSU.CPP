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

int N, M;
vector<vi> adj;
vi parent, sizeunion;

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
    int root_u = Find(u), root_v = Find(v);
    if (root_u == root_v) return false;
    if (sizeunion[root_u] < sizeunion[root_v])
    {
        swap(root_u, root_v);
    }
    parent[root_v] = root_u;
    sizeunion[root_u] += sizeunion[root_v];
    return true;
}

void Read()
{
    cin >> N >> M;
    adj.resize(N + 1);
    parent.resize(N + 1);
    sizeunion.resize(N + 1, 1);
    iota(all(parent), 0);
    FOR(i, 1, M)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
        Unite(u, v);
    }
}

void Solve()
{
    cout << Find(3) << endl;
    Unite(10, 3);
    cout << Find(10);
}

int main() 
{
    fixIO();
    File("DSU");
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