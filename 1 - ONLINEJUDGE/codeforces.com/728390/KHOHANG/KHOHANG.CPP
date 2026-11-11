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

int N;
ll W;

void Read()
{
    cin >> N >> W;
}

inline void updateDP(ll *dp, ll &cur_W, ll tw, ll tv, ll max_capacity)
{
    if (tw > max_capacity) return;
    cur_W = min(max_capacity, cur_W + tw);
    ll j = cur_W;
    ll limit = tw + 3;
    for (; j >= limit; j -= 4)
    {
        ll c0 = dp[j] - (dp[j - tw] + tv);
        dp[j] -= c0 & (c0 >> 63);
        ll c1 = dp[j - 1] - (dp[j - 1 - tw] + tv);
        dp[j - 1] -= c1 & (c1 >> 63);

        ll c2 = dp[j - 2] - (dp[j - 2 - tw] + tv);
        dp[j - 2] -= c2 & (c2 >> 63);

        ll c3 = dp[j - 3] - (dp[j - 3 - tw] + tv);
        dp[j - 3] -= c3 & (c3 >> 63);
    }
    for (; j >= tw; --j)
    {
        ll c = dp[j] - (dp[j - tw] + tv);
        dp[j] -= c & (c >> 63);
    }
}

void Solve()
{
    vll DP(W + 1, 0);
    ll *dp = DP.data();
    ll cur_W = 0;

    FOR(i, 1, N)
    {
        ll w, v, c;
        cin >> w >> v >> c;
        int p = MSB(c + 1);
        ll sum_powers = (1ULL << p) - 1;
        for (int b = 0; b < p; ++b)
        {
            ll t = 1LL << b;
            updateDP(dp, cur_W, w * t, v * t, W);
        }
        ll rem = c - sum_powers;
        if (rem > 0)
        {
            updateDP(dp, cur_W, w * rem, v * rem, W);
        }
    }

    cout << dp[W];
}

int main()
{
    fixIO();
    File("KHOHANG");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
