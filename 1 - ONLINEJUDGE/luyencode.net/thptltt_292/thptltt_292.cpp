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

struct Point
{
	ll x, y;
	int id, yidx;
};

int n, m;
vector<Point> p;
vi tree;
vll valsy;

void Read()
{
	cin >> n;
	p.resize(n + 1);
	FOR(i, 1, n)
	{
		cin >> p[i].x >> p[i].y;
		p[i].id = i;
		valsy.pb(p[i].y);
	}
}

bool cmp(const Point &a, const Point &b)
{
	if (a.x != b.x)
	{
		return a.x < b.x;
	}
	return a.y < b.y;
}

void Update(int id, int left, int right, int pos, int val)
{
	if (left == right)
	{
		tree[id] += val;
		return;
	}
	int mid = (left + right) / 2;
	if (pos <= mid)
	{
		Update(2 * id, left, mid, pos, val);
	}
	else
	{
		Update(2 * id + 1, mid + 1, right, pos, val);
	}
	tree[id] = tree[2 * id] + tree[2 * id + 1];
}

int Query(int id, int left, int right, int qleft, int qright)
{
	if (qleft > right || qright < left || qleft > qright)
	{
		return 0;
	}
	if (qleft <= left  && right <= qright)
	{
		return tree[id];
	}
	int mid = (left + right) / 2;
	return Query(2 * id, left, mid, qleft, qright) + Query(2 * id + 1, mid + 1, right, qleft, qright);
}

void Solve()
{
	sort(all(valsy));
	valsy.erase(unique(all(valsy)), valsy.end());
	m = sz(valsy);
	FOR(i, 1, n)
	{
		p[i].yidx = lower_bound(all(valsy), p[i].y) - valsy.begin() + 1;
	}
	sort(p.begin() + 1, p.end(), cmp);
	tree.assign(4 * (m + 5), 0);
	vll leftcnt(n + 1, 0), rightcnt(n + 1, 0);
	for (int i = 1; i <= n;)
	{
		int j = i;
		while (j <= n && p[j].x == p[i].x)
		{
			j ++;
		}
		FOR(k, i, j - 1)
		{
			leftcnt[p[k].id] = Query(1, 1, m, 1, p[k].yidx - 1);
		}
		FOR(k, i, j - 1)
		{
			Update(1, 1, m, p[k].yidx, 1);
		}
		i = j;
	}
	tree.assign(4 * (m + 5), 0);
	for (int i = n; i >= 1;)
	{
	    int j = i;
	    while (j >= 1 && p[j].x == p[i].x)
	    {
	        j --;
	    }
	    FORD(k, i, j + 1)
	    {
	        rightcnt[p[k].id] = Query(1, 1, m, p[k].yidx + 1, m);
	    }
	    FORD(k, i, j + 1)
	    {
	        Update(1, 1, m, p[k].yidx, 1);
	    }
	    i = j;
	}
	tree.assign(4 * n, 0);
	ll ans = 0;
	FOR(i, 1, n)
	{
		ans += leftcnt[i] * rightcnt[i];
	}
	cout << ans;
}

int main()
{
    fixIO();
    File("thptltt_292");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */