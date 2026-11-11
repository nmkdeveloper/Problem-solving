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

int N;
ll A, B;

void Read()
{
    cin >> N >> A >> B;
}

namespace sub1
{
    struct Edge
    {
        int v;
        ll w;
        ll c;
    };

    vector<vector<Edge>> adj;

    void Read()
    {
        adj.resize(N + 1);
        REP(i, N - 1)
        {
            int u, v;
            ll w, c;
            cin >> u >> v >> w >> c;
            adj[u].pb({v, w, c});
            adj[v].pb({u, w, c});
        }
    }

    ll ans;

    void DFS(int root, int u, int p, ll curl, ll curt)
    {
        if (curl > A || curt > B)
        {
            return;
        }
        if (root < u)
        {
            ans ++;
        }
        for (const Edge& e : adj[u])
        {
            int v = e.v;
            if (v != p)
            {
                DFS(root, v, u, curl + e.w, curt + e.c);
            }
        }
    }

    void Solve()
    {
        Read();
        FOR(i, 1, N)
        {
            DFS(i, i, 0, 0, 0);
        }
        cout << ans;
    }
}

namespace sub3
{
    void Solve()
    {
        vll prefw(N + 1, 0), prefc(N + 1, 0);
        FOR(i, 1, N - 1)
        {
            int u, v;
            ll w, c;
            cin >> u >> v >> w >> c;
            prefw[i + 1] = prefw[i] + w;
            prefc[i + 1] = prefc[i] + c;
        }
        ll ans = 0;
        int p1 = 1, p2 = 1;
        FOR(i, 2, N)
        {
            while(prefw[i] - prefw[p1] > A)
            {
                p1 ++;
            }
            while(prefc[i] - prefc[p2] > B)
            {
                p2 ++;
            }
            int left = max(p1, p2);
            if (left <= i - 1)
            {
                ans += (i - 1) - left + 1;
            }
        }
        cout << ans;
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
        sub3::Solve();
    }
}

int main()
{
    fixIO();
    File("BRT");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
