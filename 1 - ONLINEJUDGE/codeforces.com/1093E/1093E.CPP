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
    int type;
    int la, ra, lb, rb;
    int x, y;
};

const int MAXN = (int) 1e6 + 7;

int n, m;
vi a, b, posa, curb;
vector<vi> nodes, bit;
vector<Query> queries;

void Add(int x, int y)
{
    for (int i = x; i <= n; i += i & -i)
    {
        nodes[i].pb(y);
    }
}

void Read()
{
    cin >> n >> m;
    a.resize(n + 1);
    b.resize(n + 1);
    posa.resize(MAXN + 1);
    curb.resize(MAXN + 1);
    nodes.resize(n + 1);
    bit.resize(n + 1);
    FOR(i, 1, n)
    {
        cin >> a[i];
        posa[a[i]] = i;
    }
    FOR(i, 1, n)
    {
        cin >> b[i];
        curb[i] = b[i];
    }
    FOR(i, 1, n)
    {
        Add(i, posa[b[i]]);
    }
    queries.resize(m + 1);
    FOR(i, 1, m)
    {
        cin >> queries[i].type;
        if (queries[i].type == 1)
        {
            cin >> queries[i].la >> queries[i].ra >> queries[i].lb >> queries[i].rb;
        }
        else
        {
            cin >> queries[i].x >> queries[i].y;
            Add(queries[i].x, posa[curb[queries[i].y]]);
            Add(queries[i].y, posa[curb[queries[i].x]]);
            swap(curb[queries[i].x], curb[queries[i].y]);
        }
    }
}

int Get(int x, int y)
{
    return lower_bound(all(nodes[x]), y) - nodes[x].begin() + 1;
}

void Update(int x, int y, int val)
{
    for (int i = x; i <= n; i += i & -i)
    {
        int node = Get(i, y);
        for (int j = node; j < sz(bit[i]); j += j & -j)
        {
            bit[i][j] += val;
        }
    }
}

int Querybit(int x, int y)
{
    int sum = 0;
    for(int i = x; i > 0; i -= i & -i)
    {
        int node = upper_bound(all(nodes[i]), y) - nodes[i].begin();
        for(int j = node; j > 0; j -= j & -j)
        {
            sum += bit[i][j];
        }
    }
    return sum;
}

int Queryrec(int x, int y1, int y2)
{
    if (x <= 0 || y1 > y2)
    {
        return 0;
    }
    return Querybit(x, y2) - Querybit(x, y1 - 1);
}

void Solve()
{
    FOR(i, 1, n)
    {
        sort(all(nodes[i]));
        nodes[i].erase(unique(all(nodes[i])), nodes[i].end());
        bit[i].assign(sz(nodes[i]) + 1, 0);
    }
    FOR(i, 1, n)
    {
        Update(i, posa[b[i]], 1);
    }
    FOR(i, 1, m)
    {
        if(queries[i].type == 1)
        {
            int ans = Queryrec(queries[i].rb, queries[i].la, queries[i].ra) - Queryrec(queries[i].lb - 1, queries[i].la, queries[i].ra);
            cout << ans << endl;
        }
        else
        {
            int u = queries[i].x, v = queries[i].y;
            Update(u, posa[b[u]], -1);
            Update(v, posa[b[v]], -1);
            swap(b[u], b[v]);
            Update(u, posa[b[u]], 1);
            Update(v, posa[b[v]], 1);
        }
    }
}

int main()
{
    fixIO();
    File("1093E");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
