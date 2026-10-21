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
typedef pair<ll, pii> plpii;
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

int n, m;
vector<vll> a;
int k;

void Read()
{
    cin >> n >> m;
    a.resize(n + 2, vll(m + 2));
    FOR(i, 1, n)
    {
        FOR(j, 1, m)
        {
            cin >> a[i][j];
        }
    }
    cin >> k;
}

void Solve()
{
    int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
    vector<vll> dp(n + 2, vll(m + 2, INF64));
    vector<vector<pii>> trace(n + 2, vector<pii>(m + 2));
    priority_queue<plpii, vector<plpii>, greater<plpii>> pq;
    dp[1][1] = a[1][1];
    pq.push({dp[1][1], {1, 1}});
    while(sz(pq))
    {
        plpii cur = pq.top();
        pq.pop();
        ll curd = cur.fi;
        int u = cur.se.fi, v = cur.se.se;
        if (curd > dp[u][v])
        {
            continue;
        }
        if (u == n && v == m)
        {
            break;
        }
        REP(i, 4)
        {
            int x = u + dx[i], y = v + dy[i];
            if (x >= 1 && x <= n && y >= 1 && y <= m)
            {
                if (dp[x][y] > dp[u][v] + a[x][y])
                {
                    dp[x][y] = dp[u][v] + a[x][y];
                    trace[x][y] = {u, v};
                    pq.push({dp[x][y], {x, y}});
                }
            }
        }
    }
    vll path;
    int x = n, y = m;
    while(x != 0 && y != 0)
    {
        path.pb(a[x][y]);
        pii p = trace[x][y];
        x = p.fi;
        y = p.se;
    }
    reverse(all(path));
    for (auto t : path)
    {
        int cur = 0;
        for (auto val : path)
        {
            if (val > t)
            {
                cur++;
            }
        }
        if (cur <= k)
        {
            cout << t;
            exit(0);
        }
    }
}

int main()
{
    fixIO();
    File("ROBOT");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
