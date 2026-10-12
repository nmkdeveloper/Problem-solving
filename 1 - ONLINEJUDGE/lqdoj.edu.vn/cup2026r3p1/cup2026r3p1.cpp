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
const int MOD = 1e9 + 19972207;

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

int n;
vi a;

void Read()
{
	cin >> n;
	a.resize(n);
	REP(i, n)
	{
		cin >> a[i];
	}
}

namespace sub1
{
	map<vi, int> cnt_p;
	ll res = 0;
	void Backtrack(int pos, int cnt, ll sum, vi b, vi p)
	{
		cnt_p[p] ++;
		if ((cnt >= 3) && (cnt & 1))
		{
			sort(all(b));
			int median_pos = cnt / 2;
			double median = (double) b[median_pos];
			double average = (double) sum / cnt;			
			if (average < median)
			{				
				if (cnt_p[p] == 1)
				{
					res = (res + 1) % MOD;
				}
			}
		}
		pos ++;
		if (pos >= n)
		{
			return;
		}
		Backtrack(pos, cnt, sum, b, p);
		p.pb(pos);
		b.pb(a[pos]);
		Backtrack(pos, cnt + 1, sum += (1LL * a[pos]), b, p);
	}
	void Handle()
	{
		vi p;
		vi b;
		REP(i, n)
		{
			p.pb(i);
			b.pb(a[i]);
			Backtrack(i, 1, a[i], b, p);
			p.pop_back();
			b.pop_back();
		}
		cout << res;
	}
}

void Solve()
{
	if (n < 3)
	{
		cout << 0;
		return;
	}
	sub1::Handle();
}

int main()
{
    fixIO();
    File("mom");
    Read();
    Solve();
    return 0;
}