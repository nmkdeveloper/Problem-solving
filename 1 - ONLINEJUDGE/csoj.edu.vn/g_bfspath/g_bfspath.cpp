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

int n, m, s, t;
vector<vi> adj;

void Read()
{
	cin >> n >> m >> s >> t;
	adj.resize(n + 1);
	REP(i, m)
	{
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
	}
}

vb visited;

void Solve()
{
	FOR(i, 1, n)
	{
		sort(all(adj[i]));
	}
	visited.resize(n + 1, false);
	visited[s] = true;
	vi par(n + 1, 0);
	queue<int> q;
	q.push(s);
	while(sz(q))
	{
		int u = q.front();
		q.pop();
		if (u == t)
		{
			break;
		}
		for (auto v : adj[u])
		{
			if (!visited[v])
			{
				visited[v] = true;
				par[v] = u;
				q.push(v);
			}
		}
	}
	vi res;
	for (int u = t; u != 0; u = par[u])
	{
		res.pb(u);
	}
	reverse(all(res));
	for (auto e : res)
	{
		cout << e << ' ';
	}
}

int main()
{
    fixIO();
    File("g_bfspath");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I Love You, My Love <3
 */