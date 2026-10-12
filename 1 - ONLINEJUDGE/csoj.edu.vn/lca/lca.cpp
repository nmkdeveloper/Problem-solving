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

int n, q;
vector<vi> adj;

void Read()
{
	cin >> n >> q;
	adj.resize(n + 1);
	REP(i, n - 1)
	{
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
}

const int MAXLOG = 19;
const int MAXN = (int) 1e5 + 7;
int up[MAXN][MAXLOG];
int dep[MAXN];
int tin[MAXN];
int timer = 0;

void DFS(int u, int p)
{
	tin[u] = ++timer;
	up[u][0] = p;
	FOR(j, 1, MAXLOG - 1)
	{
		up[u][j] = up[up[u][j - 1]][j - 1];
	}
	for (auto v : adj[u])
	{
		if (v != p)
		{
			dep[v] = dep[u] + 1;
			DFS(v, u);
		}
	}
}

bool cmp(int u, int v)
{
	return tin[u] < tin[v];
}

void Solve()
{
	dep[1] = 0;
	DFS(1, 1);
	while(q --)
	{
		int t;
		vi k;
		cin >> t;
		k.resize(t);
		REP(i, t)
		{
			cin >> k[i];
		}
		if (t == 1)
		{
			cout << k[0] << ' ' << k[0] << endl;
			continue;
		}
		k.erase(unique(all(k)), k.end());
        if (sz(k) == 1) {
            cout << k[0] << ' ' << k[0] << endl;
            continue;
        }
		sort(all(k), cmp);
		int u = k[0];
		int v = k[sz(k) - 1];
		cout << u << ' ' << v << endl;
	}
}

int main()
{
    fixIO();
    File("lca");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I love you as certain dark things are to be loved, in secret, between the shadow and the soul.
 * - Pablo Neruda, 100 Love Sonnets (Sonnet XVII) -
 */