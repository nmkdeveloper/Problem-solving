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
  int u;
  int v;
};

struct Query
{
  int u;
  int v;
  int id;
};

int n, m, q;
vector<Edge> edges;
vector<Query> queries;

void Read()
{
  cin >> n >> m >> q;
  REP(i, m)
  {
    int u, v;
    cin >> u >> v;
    edges.pb({u, v});
  }
  REP(i, q)
  {
    int u, v;
    cin >> u >> v;
    queries.pb({u, v, i});
  }
}

vi siz, par;

int Find(int u)
{
  if (u == par[u])
  {
    return u;
  }
  return par[u] = Find(par[u]);
}

void Unite(int u, int v)
{
    u = Find(u);
    v = Find(v);
    if (u == v)
    {
      return;
    }
    if (siz[u] < siz[v])
    {
      swap(u, v);
    }
    par[v] = u;
    siz[u] += siz[v];
}

void Solve()
{
  vi left(q, 1), right(q, m), ans(q, -1);
  vector<vi> midb(m + 1);
  while(true)
  {
    bool have = false;
    FOR(i, 1, m)
    {
        midb[i].clear();
    }
    REP(i, q)
    {
      if (queries[i].u == queries[i].v)
      {
        ans[i] = 0;
        continue;
      }
      if (left[i] <= right[i])
      {
        have = true;
        int mid = left[i] + (right[i] - left[i]) / 2;
        midb[mid].pb(i);
      }
    }
    if (!have)
    {
      break;
    }
    siz.assign(n + 1, 1);
    par.resize(n + 1);
    iota(all(par), 0);
    FOR(i, 1, m)
    {
      Unite(edges[i - 1].u, edges[i - 1].v);
      for (auto j : midb[i])
      {
        int u = queries[j].u, v = queries[j].v;
        if (Find(u) == Find(v))
        {
          ans[j] = i;
          right[j] = i - 1;
        }
        else
        {
          left[j] = i + 1;
        }
      }
    }
  }
  REP(i, q)
  {
    cout << ans[i] << endl;
  }
}

int main()
{
    fixIO();
    File("2101");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
