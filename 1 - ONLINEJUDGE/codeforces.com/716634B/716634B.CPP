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

const int MAXN = 1e5 + 7;
int n;
int a[4 * MAXN];
int q;

void Read()
{
    cin >> n;
    FOR(i, 1, n)
    {
        cin >> a[i];
    }
}

int cnt[4 * MAXN][20], lazy[4 * MAXN];

void Build(int id, int left, int right)
{
    if (left == right)
    {
        REP(b, 20)
        {
            if ((a[left] >> b) & 1)
            {
                cnt[id][b] = 1;
            }
        }
        return;
    }
    int mid = (left + right) / 2;
    Build(id * 2, left, mid);
    Build(id * 2 + 1, mid + 1, right);
    REP(b, 20)
    {
        cnt[id][b] = cnt[id * 2][b] + cnt[id * 2 + 1][b];
    }
}

void pushDown(int id, int left, int right)
{
    if (lazy[id] == 0)
    {
        return;
    }
    int mid = (left + right) / 2;
    int pdleft = id * 2, pdright = id * 2 + 1;
    int x = lazy[id];
    REP(b, 20)
    {
        if ((x >> b) & 1)
        {
            cnt[pdleft][b] = (mid - left + 1) - cnt[pdleft][b];
            cnt[pdright][b] = (right - mid) - cnt[pdright][b];
        }
    }
    lazy[pdleft] ^= x;
    lazy[pdright] ^= x;
    lazy[id] = 0;
}

void Update(int id, int left, int right, int uleft, int uright, int value)
{
    if (left > uright || right < uleft)
    {
        return;
    }
    if (left >= uleft && right <= uright)
    {
        REP(b, 20)
        {
            if ((value >> b) & 1)
            {
                cnt[id][b] = (right - left + 1) - cnt[id][b];
            }
        }
        lazy[id] ^= value;
        return;
    }
    pushDown(id, left, right);
    int mid = (left + right) / 2;
    Update(2 * id, left,  mid, uleft, uright, value);
    Update(2 * id + 1, mid + 1, right, uleft, uright, value);
    REP(b, 20)
    {
        cnt[id][b] = cnt[2 * id][b] + cnt[2 * id + 1][b];
    }
}

ll Query(int id, int left, int right, int qleft, int qright)
{
    if (left > qright || right < qleft)
    {
        return 0;
    }
    if (left >= qleft && right <= qright)
    {
        ll sum = 0;
        REP(b, 20)
        {
            sum += (1LL << b) * cnt[id][b];
        }
        return sum;
    }
    pushDown(id, left, right);
    int mid = (left + right) / 2;
    return Query(2 * id, left, mid, qleft, qright) + Query(2 * id + 1, mid + 1, right, qleft, qright);
}

void Solve()
{
    Build(1, 1, n);
    cin >> q;
    while(q --)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int left, right;
            cin >> left >> right;
            cout << Query(1, 1, n, left, right) << endl;
        }
        else
        {
            int left, right, value;
            cin >> left >> right >> value;
            Update(1, 1, n, left, right, value);
        }
    }
}

int main()
{
    fixIO();
    File("716634B");
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