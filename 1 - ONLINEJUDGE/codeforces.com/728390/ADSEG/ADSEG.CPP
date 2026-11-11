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

int N, Q;
vll A;

void Read()
{
    cin >> N >> Q;
    A.resize(N + 1);
    FOR(i, 1, N)
    {
        cin >> A[i];
    }
}

void Solve()
{
    while(Q --)
    {
        int type;
        cin >> type;
        if(type == 1)
        {
            int i, v;
            cin >> i >> v;
            A[i] = v;
        }
        else if (type == 2)
        {
            int left, right;
            cin >> left >> right;
            FOR(i, left, right)
            {
                A[i] *= -1;
            }
        }
        else
        {
            int left, right, k;
            cin >> left >> right >> k;
            int m = right - left + 1;
            vector<vector<vll>>  DP(m + 1, vector<vll>(k + 1, vll(2, -INF64)));
            DP[0][0][0] = 0;
            FOR(i, 1, m)
            {
                int cur = left + i - 1;
                FOR(j, 0, k)
                {
                    DP[i][j][0] = max(DP[i - 1][j][0], DP[i - 1][j][1]);
                    if (j > 0)
                    {
                        ll o = max(DP[i - 1][j - 1][0], DP[i - 1][j - 1][1]);
                        ll e = DP[i - 1][j][1];
                        ll pre = max(o, e);
                        if (pre != -INF64)
                        {
                            DP[i][j][1] = pre + A[cur];
                        }
                    }
                }
            }
            ll ans = 0;
            FOR(j, 0, k)
            {
                ans = max({ans, DP[m][j][0], DP[m][j][1]});
            }
            cout << ans << endl;
        }
    }
}

int main()
{
    fixIO();
    File("ADSEG");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
