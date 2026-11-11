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

int n;
vi a, b;

void Read()
{
    cin >> n;
    a.resize(n);
    b.resize(n);
    REP(i, n)
    {
        cin >> a[i];
    }
    REP(i, n)
    {
        cin >> b[i];
    }
}

ll BFS1()
{
    if (a[0] != b[0] || a[n - 1] != b[n - 1])
    {
        return -1;
    }
    if (a == b)
    {
        return 0;
    }
    map<vi, int> dist;
    queue<vi> q;
    dist[a] = 0;
    q.push(a);
    while(sz(q))
    {
        vi cur = q.front();
        q.pop();
        int curd = dist[cur];
        FOR(i, 1, n - 2)
        {
            vi nxt = cur;
            nxt[i] = cur[i - 1] + cur[i + 1] - cur[i];
            if (nxt == b)
            {
                return curd + 1;
            }
            if (!dist.count(nxt))
            {
                dist[nxt] = curd + 1;
                q.push(nxt);
            }
        }
    }
    return -1;
}

bool CheckBFS(int left, int right)
{
    if (a[left] != b[left] || a[right] != b[right])
    {
        return false;
    }
    vi suba(a.begin() + left, a.begin() + right + 1);
    vi subb(b.begin() + left, b.begin() + right + 1);
    if (suba == subb)
    {
        return true;
    }
    int len = right - left + 1;
    set<vi> visited;
    queue<vi> q;
    visited.insert(suba);
    q.push(suba);
    while(sz(q))
    {
        vi cur = q.front();
        q.pop();
        FOR(i, 1, len - 2)
        {
            vi nxt = cur;
            nxt[i] = cur[i - 1] + cur[i + 1] - cur[i];
            if (nxt == subb)
            {
                return true;
            }
            if (!visited.count(nxt))
            {
                visited.insert(nxt);
                q.push(nxt);
            }
        }
    }
    return false;
}

ll Cntsub2()
{
    ll ans = 0;
    REP(l, n)
    {
        FOR(r, l + 1, n - 1)
        {
            if (CheckBFS(l, r))
            {
                ans ++;
            }
        }
    }
    return ans;
}

void Solve()
{
    cout << BFS1() << endl << Cntsub2();
}

int main()
{
    fixIO();
    File("730764A");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
