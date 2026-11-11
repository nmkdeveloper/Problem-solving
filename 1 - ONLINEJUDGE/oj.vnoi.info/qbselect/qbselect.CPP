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

int n;
vector<vi> a;

bool pos = false;
ll maxval = - INF64;

void Read()
{
    cin >> n;
    a.resize(4, vi(n));
    REP(i, 4)
    {
        REP(j, n)
        {
            cin >> a[i][j];
            if (a[i][j] >= 0)
            {
                pos = true;
            }
            maxval = max(maxval, 1LL * a[i][j]);
        }
    }
}

bool Issafe(ll mask)
{
    if (mask & (mask >> 1))
    {
        return false;
    }
    if (mask & (mask << 1))
    {
        return false;
    }
    return true;
}

ll Getsum(int j, int mask)
{
    ll sum = 0;
    REP(i, 4)
    {
        if ((mask >> i) & 1)
        {
            sum += a[i][j];
        }
    }
    return sum;
}

void Solve()
{
    if (!pos)
    {
        cout << maxval;
        return;
    }
    vector<vll> DP(n, vll(16, - INF64));
    REP(mask, 16)
    {
        if (Issafe(mask))
        {
            DP[0][mask] = Getsum(0, mask);
        }
    }
    FOR(j, 1, n - 1)
    {
        REP(mask, 16)
        {
            if (!Issafe(mask))
            {
                continue;
            }
            ll cursum = Getsum(j, mask);
            REP(mask2, 16)
            {
                if (!Issafe(mask2))
                {
                    continue;
                }
                if (!(mask & mask2))
                {
                    DP[j][mask] = max(DP[j][mask], DP[j - 1][mask2] + cursum);
                }
            }
        }
    }
    ll ans = -INF64;
    REP(mask, 16)
    {
        ans = max(ans, DP[n - 1][mask]);
    }
    cout << ((ans == -INF64) ? 0 : ans);
}

int main()
{
    fixIO();
    File("qbselect");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
