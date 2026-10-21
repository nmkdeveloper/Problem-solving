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

const int MAXN = 500000 + 7;
int n, T;
int a[MAXN];

void Read()
{
	cin >> n >> T;
	FOR(i, 1, n)
	{
		cin >> a[i];
	}
}

int tree[4 * MAXN];

void Build(int id, int left, int right)
{
	if (left == right)
	{
		tree[id] = a[left];
		return;
	}
	int mid = (left + right) / 2;
	Build(id * 2, left, mid);
	Build(id * 2 + 1, mid + 1, right);
	tree[id] = max(tree[id * 2], tree[id * 2 + 1]);
}

void Update(int id, int left, int right, int pos, int val)
{
	if (left == right)
	{
		tree[id] = val;
		return;
	}
	int mid = (left + right) / 2;
	if (pos <= mid)
	{
		Update(id * 2, left, mid, pos, val);
	}
	else
	{
		Update(id * 2 + 1, mid + 1, right, pos, val);
	}
	tree[id] = max(tree[id * 2], tree[id * 2 + 1]);
}

int Query(int id, int left, int right, int qleft, int qright)
{
	if (qright < left || right < qleft)
	{
		return INT_MIN;
	}
	if (qleft <= left && right <= qright)
	{
		return tree[id];
	}
	int mid = (left + right) / 2;
	return max(Query(id * 2, left, mid, qleft, qright), Query(id * 2 + 1, mid + 1, right, qleft, qright));
}

void Solve()
{
	Build(1, 1, n);
	while(T --)
	{
		int left, right;
		cin >> left >> right;
		cout << Query(1, 1, n, left, right) << endl;
	}
}

int main()
{
    fixIO();
    File("SEQ13");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I Love You, My Love <3
 */