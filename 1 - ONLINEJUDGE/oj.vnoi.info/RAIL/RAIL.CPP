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
    int type;
};

int n, m;
vector<Edge> e;

void Read()
{
    cin >> n >> m;
    REP(i, m)
    {
        int u, v, type;
        cin >> u >> v >> type;
        e.pb({u, v, type});
    }
}

int Find(int u, vi& Parent)
{
    if (u == Parent[u])
    {
        return u;
    }
    return Parent[u] = Find(Parent[u], Parent);
}

void Unite(int u, int v, vi& Parent, vi& Size)
{
    u = Find(u, Parent);
    v = Find(v, Parent);
    if (u == v)
    {
        return;
    }
    if (Size[u] < Size[v])
    {
        swap(u, v);
    }
    Parent[v] = u;
    Size[u] += Size[v];
}

void Solve()
{
    int cnt = 0;
    REP(i, m)
    {
        vi Parent1(n + 1), Parent2(n + 1);
        vi Size1(n + 1, 1), Size2(n + 1, 1);
        iota(all(Parent1), 0);
        iota(all(Parent2), 0);
        REP(j, m)
        {
            if (i == j)
            {
                continue;
            }
            if (e[j].type == 1)
            {
                Unite(e[j].u, e[j].v, Parent1, Size1);
                Unite(e[j].u, e[j].v, Parent2, Size2);
            }
            if (e[j].type == 2)
            {
                Unite(e[j].u, e[j].v, Parent1, Size1);
            }
            if (e[j].type == 3)
            {
                Unite(e[j].u, e[j].v, Parent2, Size2);
            }
        }
        bool isPassed = true;
        FOR(u, 1, n)
        {
            FOR(v, u + 1, n)
            {
                if (Find(u, Parent1) != Find(v, Parent1) || Find(u, Parent2) != Find(v, Parent2))
                {
                    isPassed = false;
                    break;
                }
            }
            if (!isPassed)
            {
                break;
            }
        }
        if (!isPassed)
        {
            cnt ++;
        }
    }
    cout << cnt;
}

int main()
{
    fixIO();
    File("RAIL");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
