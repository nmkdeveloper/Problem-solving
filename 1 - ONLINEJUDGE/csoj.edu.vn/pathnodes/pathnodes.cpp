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

int n, m;
vector<vi> adj;

void Read()
{
	cin >> n >> m;
	adj.resize(n + 1);
	REP(i, m)
	{
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
}

vi BFS(int s)
{
	vi dist(n + 1, INF);
	queue<int> q;
	q.push(s);
	dist[s] = 0;
	while(sz(q))
	{
		int u = q.front();
		q.pop();
		for (auto v : adj[u])
		{
			if (dist[v] == INF)
			{
				q.push(v);
				dist[v] = dist[u] + 1;
			}
		}
	}
	return dist;
}

void Solve()
{
	vi d1 = BFS(1), d2 = BFS(n);
	if (d1[n] == INF)
	{
		cout << 0;
		return;
	}
	vi res;
	int D = d1[n];
	FOR(u, 1, n)
	{
		if (d1[u] + d2[u] == D)
		{
			res.pb(u);
		}
	}
	cout << sz(res) << endl;
	for (auto e : res)
	{
		cout << e << ' ';
	}
}

int main()
{
    fixIO();
    File("");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I Love You, My Love <3
 */