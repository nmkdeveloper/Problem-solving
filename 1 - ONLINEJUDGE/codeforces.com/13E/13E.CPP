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

const int MAXN = (int) 1e5 + 7;
int n, m, b;
int a[MAXN];
int nxt[MAXN], cnt[MAXN], last[MAXN];

void Read()
{
    cin >> n >> m;
    FOR(i, 1, n)
    {
        cin >> a[i];
    }
}

int Get(int x)
{
    return (x - 1) / b;
}

void Build(int id)
{
    int l = id * b + 1;
    int r = min(n, (id + 1) * b);
    FORD(i, r, l)
    {
        int j = i + a[i];
        if (j > n || Get(j) != id)
        {
            nxt[i] = j;
            cnt[i] = 1;
            last[i] = i;
        }
        else
        {
            nxt[i] = nxt[j];
            cnt[i] = cnt[j] + 1;
            last[i] = last[j];
        }
    }
}

void Solve()
{
    b = sqrt(n) + 1;
    for (int i = 0; i * b + 1 <= n; i ++)
    {
        Build(i);
    }
    while(m --)
    {
        int t;
        cin >> t;
        if (t == 0)
        {
            int p, val;
            cin >> p >> val;
            a[p] = val;
            Build(Get(p));
        }
        else
        {
            int x;
            cin >> x;
            int ans = 0;
            int lastx = -1;
            while(x <= n)
            {
                ans += cnt[x];
                lastx = last[x];
                x = nxt[x];
            }
            cout << lastx << ' ' << ans << endl;
        }
    }
}

int main()
{
    fixIO();
    File("13E");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
