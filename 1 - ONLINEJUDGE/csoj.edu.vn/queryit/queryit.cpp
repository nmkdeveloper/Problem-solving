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

int n, q;

void Read()
{
    cin >> n >> q;
}

vll tree, lazyadd, lazymul;


// $x \rightarrow (x \times mul + add) \pmod{MOD}$
void Apply(int node, int left, int right, ll mul, ll add)
{
    ll len = right - left + 1;
    tree[node] = (tree[node] * mul % MOD + add * len % MOD) % MOD;
    lazymul[node] = (lazymul[node] * mul) % MOD;
    lazyadd[node] = (lazyadd[node] * mul % MOD + add) % MOD;
}

void Pushdown(int node, int left, int right)
{
    if (lazyadd[node] == 0 && lazymul[node] == 1)
    {
        return;
    }
    int mid = left + (right - left) / 2;
    Apply(node * 2, left, mid, lazymul[node], lazyadd[node]);
    Apply(node * 2 + 1, mid + 1, right, lazymul[node], lazyadd[node]);
    lazymul[node] = 1;
    lazyadd[node] = 0;
}

void Update1(int node, int left, int right, int qleft, int qright, ll val)
{
    if (qleft <= left && right <= qright)
    {
        Apply(node, left, right, 1, val % MOD);
        return;
    }
    Pushdown(node, left, right);
    int mid = left + (right - left) / 2;
    if (qleft <= mid)
    {
        Update1(node * 2, left, mid, qleft, qright, val);
    }
    if (qright > mid)
    {
        Update1(node * 2 + 1, mid + 1, right, qleft, qright, val);
    }
    tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % MOD;
}

void Update2(int node, int left, int right, int qleft, int qright, ll val)
{
    if (qleft <= left && right <= qright)
    {
        Apply(node, left, right, val % MOD, 0);
        return;
    }
    Pushdown(node, left, right);
    int mid = left + (right - left) / 2;
    if (qleft <= mid)
    {
        Update2(node * 2, left, mid, qleft, qright, val);
    }
    if (qright > mid)
    {
        Update2(node * 2 + 1, mid + 1, right, qleft, qright, val);
    }
    tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % MOD;
}

ll Query(int node, int left, int right, int qleft, int qright)
{
    if (qleft <= left && right <= qright)
    {
        return tree[node];
    }
    Pushdown(node, left, right);
    int mid = left + (right - left) / 2;
    ll res = 0;
    if (qleft <= mid)
    {
        res = (res + (Query(node * 2, left, mid, qleft, qright))) % MOD;
    }
    if (qright > mid)
    {
        res = (res + (Query(node * 2 + 1, mid + 1, right, qleft, qright))) % MOD;
    }
    return res;
}

void Solve()
{
    tree.assign(4 * n + 7, 0);
    lazyadd.assign(4 * n + 7, 0);
    lazymul.assign(4 * n + 7, 1);
    while(q --)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int left, right, val;
            cin >> left >> right >> val;
            Update1(1, 1, n, left, right, val);
        }
        else if (type == 2)
        {
            int left, right, val;
            cin >> left >> right >> val;
            Update2(1, 1, n, left, right, val);
        }
        else
        {
            int left, right;
            cin >> left >> right;
            cout << Query(1, 1, n, left, right) << endl;
        }
    }
}

int main()
{
    fixIO();
    File("queryit");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
