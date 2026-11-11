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

const int MAXN = 107;
int n, W;
int w[MAXN], v[MAXN], c[MAXN];

void Read()
{
    cin >> n >> W;
    FOR(i, 1, n)
    {
        cin >> w[i] >> v[i] >> c[i];
    }
}

namespace Bruteforce
{
    vi cnt;
    ll res = -1;

    void BT(int pos, ll curv, ll curw)
    {
        if (pos > n)
        {
            res = max(res, curv);
            return;
        }
        FOR(i, pos, n)
        {
            if (cnt[i] <= c[i] && curw + w[i] <= W)
            {
                cnt[i] ++;
                BT(i, 1LL * curv + v[i], 1LL * curw + w[i]);
                cnt[i] --;
            }
        }
        BT(pos + 1, curv, curw);
    }
    void Solve()
    {
        cnt.assign(n + 1, 0);
        if (w[1] <= W)
        {
            cnt[1] ++;
            BT(1, 1LL * v[1], 1LL * w[1]);
            cnt[1] --;
        }
        if (w[2] <= W)
        {
            cnt[2] ++;
            BT(2, 1LL * v[2], 1LL * w[2]);
            cnt[2] --;
        }
        cout << res;
    }
}

void Solve()
{
    if (w[1] > W && w[2] > W)
    {
        cout << -1;
        return;
    }
    Bruteforce::Solve();
}

int main()
{
    fixIO();
    File("BAG5");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
