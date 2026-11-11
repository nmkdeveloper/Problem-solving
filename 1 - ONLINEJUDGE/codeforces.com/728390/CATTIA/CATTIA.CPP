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

/*
    Eulertour de bien thanh mang 1d, sau do DP giua viec co chon hay khong chon nut do khong
    Neu chon, tinh A[u] tai nut do
    Neu khong chon, skil nut dp bang cach cong vi tri hien tai voi size cua nut do duoc tinh qua euler tour
*/

int N, K;
vector<vi> adj;
vll A;

void Read()
{
    cin >> N >> K;
    A.resize(N + 1);
    adj.resize(N + 1);
    FOR(i, 1, N)
    {
        cin >> A[i];
    }
    FOR(i, 1, N - 1)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
}

vi tour;
vi intime, siz;
int timer = 0;

/*
    Bien do thi 2d thanh do thi 1d, vi du
    tu do thi 2d
                    1
               /         \
        2                       3
    /       \               /       \
    4       5               6       7
        /       \                   /
        8       9               10

    thanh do thi 1d
    1 2 4 5 8 9 3 6 7 10
*/

void Eulertour(int u, int p)
{
    siz[u] = 1;
    intime[u] = timer ++;
    tour.pb(u);
    for (auto v : adj[u])
    {
        if (v != p)
        {
            Eulertour(v, u);
            siz[u] += siz[v];
        }
    }
}

void Solve()
{
    siz.assign(N + 1, 0);
    intime.assign(N + 1, 0);
    tour.pb(0);
    Eulertour(1, 0);
    vector<vll> DP(N + 2, vll(K + 1, -INF64));
    FOR(i, 1, N + 1)
    {
        DP[i][0] = 0;
    }
    FORD(i, N, 1)
    {
        int u = tour[i];
        FOR(j, 1, K)
        {
            // Chon phan tu A[u]
            ll pick = -INF64;
            if (DP[i + 1][j - 1] > -INF64)
            {
                pick = A[u] + DP[i + 1][j - 1];
            }
            // khong chon phan tu A[u]
            ll skip = -INF64;
            if (i > 1)
            {
                skip = DP[min(N + 1, i + siz[u])][j];
            }
            // Tinh max
            DP[i][j] = max(pick, skip);
        }
    }
    cout << DP[1][K];
}

int main()
{
    fixIO();
    File("CATTIA");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
