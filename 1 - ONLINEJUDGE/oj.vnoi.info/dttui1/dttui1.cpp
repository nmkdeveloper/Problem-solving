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

#define BIT(n) (1ULL << (n))
#define SET(k, n) ((n) |  BIT(k))
#define CLEAR(k, n) ((n) & ~BIT(k))
#define TOGGLE(k, n) ((n) ^  BIT(k))
#define CHECK(k, n) (((n) & BIT(k)) != 0)
#define MSB(x) ((x) == 0 ? -1 : 63 - __builtin_clzll((ull)(x)))

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

const int MAXN = 53;
int N;
ll M;
ll W[MAXN], V[MAXN];

void Read()
{
    cin >> N >> M;
    FOR(i, 1, N)
    {
        cin >> W[i] >> V[i];
    }
}

vpll B;
vll WA, VA, WB, VB;

void BTA(int i, ll SW, ll CV)
{
    if (SW > M)
    {
        return;
    }
    if (i > N / 2)
    {
        WA.pb(SW);
        VA.pb(CV);
        return;
    }
    BTA(i + 1, SW, CV);
    BTA(i + 1, SW + W[i], CV + V[i]);
}

void BTB(int i, ll SW, ll CV)
{
    if (SW > M)
    {
        return;
    }
    if (i > N)
    {
        B.pb({SW, CV});
        return;
    }
    BTB(i + 1, SW, CV);
    BTB(i + 1, SW + W[i], CV + V[i]);
}

void Solve()
{
    BTA(1, 0, 0);
    BTB(N / 2 + 1, 0, 0);
    sort(all(B));
    int ma = -1;
    for (const auto i : B)
    {
        if (i.se > ma)
        {
            WB.pb(i.fi);
            VB.pb(i.se);
            ma = i.se;
        }
    }
    ll ans = -1;
    REP(i, sz(WA))
    {
        int k = upper_bound(all(WB), M - WA[i]) - WB.begin() - 1;
        if (k >= 0) {
            ans = max(ans, VA[i] + VB[k]);
        }
    }
    cout << ans;
}

int main()
{
    fixIO();
    File("dttui1");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
