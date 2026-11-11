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

void Read()
{
    cin >> N >> Q;
}

vll tree, lazy;

void Pushdown(int node, int left, int right)
{
    if (lazy[node] == -1)
    {
        return;
    }
    int mid = left + (right - left) / 2;
    tree[2 * node] = lazy[node] * (mid - left + 1);
    lazy[2 * node] = lazy[node];
    tree[2 * node + 1] = lazy[node] * (right - mid);
    lazy[2 * node + 1] = lazy[node];
    lazy[node] = -1;
}

void Update(int node, int left, int right, int qleft, int qright, int val)
{
    if (qright < left || right < qleft)
    {
        return;
    }
    if (qleft <= left && right <= qright)
    {
        tree[node] = (right - left + 1) * val;
        lazy[node] = val;
        return;
    }
    Pushdown(node, left, right);
    int mid = left + (right - left) / 2;
    if (qleft <= mid)
    {
        Update(node * 2, left, mid, qleft, qright, val);
    }
    if (qright > mid)
    {
        Update(node * 2 + 1, mid + 1, right, qleft, qright, val);
    }
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll Query(int node, int left, int right, int qleft, int qright)
{
    if (qright < left || right < qleft)
    {
        return 0;
    }
    if (qleft <= left && right <= qright)
    {
        return tree[node];
    }
    Pushdown(node, left, right);
    ll sum = 0;
    int mid = left + (right - left) / 2;
    if (qleft <= mid)
    {
        sum += Query(node * 2, left, mid, qleft, qright);
    }
    if (qright > mid)
    {
        sum += Query(node * 2 + 1, mid + 1, right, qleft, qright);
    }
    return sum;
}

void Solve()
{
    tree.assign(4 * N + 7, 0);
    lazy.assign(4 * N + 7, -1);
    while(Q --)
    {
        int type, left, right;
        cin >> type >> left >> right;
        if (type == 0)
        {
            Update(1, 1, N, left, right, 0);
        }
        else if (type == 1)
        {
            Update(1, 1, N, left, right, 1);
        }
        else
        {
            cout << Query(1, 1, N, left, right) << endl;
        }
    }
}

int main()
{
    fixIO();
    File("it_fill");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
