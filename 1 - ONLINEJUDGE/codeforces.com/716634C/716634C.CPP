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

const int MAXN = 5e5 + 7;
int n, m;
int a[MAXN];

struct Query
{
    int left;
    int right;
    int id;
};

Query q[MAXN];

void Read()
{
    cin >> n >> m;
    FOR(i, 1, n)
    {
        cin >> a[i];
    }
    FOR(i, 1, m)
    {
        cin >> q[i].left >> q[i].right;
        q[i].id = i;
    }
}

int prv[MAXN];
int Seg[4 * MAXN];
int ans[MAXN];

void Build(int id, int left, int right)
{
    Seg[id] = INF;
    if (left == right)
    {
        return;
    }
    int mid = (left + right) / 2;
    Build(id * 2, left, mid);
    Build(id * 2 + 1, mid + 1, right);
}

void Update(int id, int left, int right, int i, int value)
{
    if (left == right)
    {
        Seg[id] = min(Seg[id], value);
        return;
    }
    int mid = (left + right) / 2;
    if (i <= mid)
    {
        Update(id * 2, left, mid, i, value);
    }
    else
    {
        Update(id * 2 + 1, mid +1, right, i, value);
    }
    Seg[id] = min(Seg[id * 2], Seg[id * 2 + 1]);
}

int getMin(int id, int left, int right, int qleft, int qright)
{
    if (left > qright || right < qleft)
    {
        return INF;
    }
    if (left >= qleft && right <= qright)
    {
        return Seg[id];
    }
    int mid = (left + right) / 2;
    return min(getMin(id * 2, left, mid, qleft, qright), getMin(id * 2 + 1, mid + 1, right, qleft, qright));
}

void Solve()
{
    vi val(a + 1, a + n + 1);
    sort(all(val));
    val.erase(unique(all(val)), val.end());
    FOR(i, 1, n)
    {
        a[i] = lower_bound(all(val), a[i]) - val.begin() + 1;
    }
    vi last(sz(val) + 1, 0);
    FOR(i, 1, n)
    {
        prv[i] = last[a[i]];
        last[a[i]] = i;
    }
    sort(q + 1, q + m + 1, [](const Query &x, const Query &y)
    { return x.right < y.right; });
    Build(1, 1, n);
    int cur = 1; 
    FOR(i, 1, m)
    {
        while (cur <= q[i].right)
        {
            if (prv[cur] != 0)
            {
                Update(1, 1, n, prv[cur], cur - prv[cur]);
            }
            cur ++;
        }
        int res = getMin(1, 1, n, q[i].left, q[i].right);
        ans[q[i].id] = (res == INF ? -1 : res);
    }
    FOR(i, 1, m)
    {
        cout << ans[i] << endl;
    }
}

int main()
{
    fixIO();
    File("716634C");
    Read();
    Solve();
    return 0;
}

/**
 *  "Frieren: Vay theo cau chung ta phai lam gi de nguoi khac nho den chung ta chu?
 *   Himmel:  Cung khong co gi to tac, do la hay thay doi cuoc doi cua ai do
 *            du chi mot chut. Toi thay chi can nhu vay la du roi."
 *
 *                                                   - Sousou no Frieren -
 *  =======================================================================
 *  Template by : Nguyen Minh Khoi (github/nmkdeveloper)
 *  Created     : 2026.09.14
 */