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
    Cay segment tree phuc vu tinh tong luong bom da doi o khoang thoi gian yeu cau
    Chat nhi phan thoi gian, neu o mid ma da bi pha huy thi suy ra duyet truoc do, con khong thi duyet sau do
*/

int n, m;
vll A;

struct Queryope
{
    int left, right;
    ll s;
};
vector<Queryope> operations;

void Read()
{
    cin >> n >> m;
    A.resize(n + 1);
    FOR(i, 1, n)
    {
        cin >> A[i];
    }
    operations.resize(m + 1);
    FOR(i, 1, m)
    {
        cin >> operations[i].left >> operations[i].right >> operations[i].s;
    }
}

vll tree, lazy;
vi ans;

void Pushdown(int node, int left, int right)
{
    if (lazy[node] == 0)
    {
        return;
    }
    int mid = left + (right - left) / 2;
    tree[node * 2] += lazy[node] * (mid - left + 1);
    lazy[node * 2] += lazy[node];
    tree[node * 2 + 1] += lazy[node] * (right - mid);
    lazy[node * 2 + 1] += lazy[node];
    lazy[node] = 0;
}

void Update(int node, int left, int right, int qleft, int qright, ll val)
{
    if (qright < left || right < qleft)
    {
        return;
    }
    if (qleft <= left && right <= qright)
    {
        tree[node] += val * (right - left + 1);
        lazy[node] += val;
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

ll Query(int node, int left, int right, int pos)
{
    if (left == right)
    {
        return tree[node];
    }
    Pushdown(node, left, right);
    int mid = left + (right - left) / 2;
    if (pos <= mid)
    {
        return Query(node * 2, left, mid, pos);
    }
    else
    {
        return Query(node * 2 + 1, mid + 1,  right, pos);
    }
}

void Backtrack(int left, int right, vi& cand)
{
    if (!sz(cand))
    {
        return;
    }
    if (left == right)
    {
        Update(1, 1, n, operations[left].left, operations[left].right, operations[left].s);
        for (int i : cand)
        {
            ll total = Query(1, 1, n, i);
            if (total >= A[i])
            {
                ans[i] = left;
            }
        }
        Update(1, 1, n, operations[left].left, operations[left].right, -operations[left].s);
        return;
    }
    int mid = left + (right - left) / 2;
    // Nap
    FOR(i, left, mid)
    {
        Update(1, 1, n, operations[i].left, operations[i].right, operations[i].s);
    }
    vi le, ri;
    for (int i : cand)
    {
        ll total = Query(1, 1, n, i);
        if (total >= A[i])
        {
            le.pb(i);
        }
        else
        {
            A[i] -= total;
            ri.pb(i);
        }
    }
    // Thao
    FOR(i, left, mid)
    {
        Update(1, 1, n, operations[i].left, operations[i].right, -operations[i].s);
    }
    Backtrack(left, mid, le);
    Backtrack(mid + 1, right, ri);
}

void Solve()
{
    tree.resize(4 * n + 7);
    lazy.resize(4 * n + 7, 0);
    ans.resize(n + 1, -1);
    vi cand;
    FOR(i, 1, n)
    {
        cand.pb(i);
    }
    Backtrack(1, m, cand);
    FOR(i, 1, n)
    {
        cout << ans[i] << ' ';
    }
}

int main()
{
    fixIO();
    File("it_times");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
