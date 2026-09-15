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

const int MAXN = 2e5 + 7;
int n, q;
ll a[MAXN];

void Read()
{
    cin >> n >> q;
    FOR(i, 1, n)
    {
        cin >> a[i];
    }
}

struct Node
{
    ll sum;
    ll mn;
    ll mvalue;
    ll lazy;
};

Node Seg[4 * MAXN];

void Build(int id, int left, int right)
{
    if (left == right)
    {
        Seg[id].sum = a[left];
        Seg[id].mn = a[left];
        Seg[id].mvalue = a[left];
        Seg[id].lazy = 0;
        return;
    }
    int mid = (left + right) / 2;
    Build(id * 2, left, mid);
    Build(id * 2 + 1, mid + 1, right);
    Seg[id].sum = Seg[id * 2].sum + Seg[id * 2 + 1].sum;
    Seg[id].mn = min(Seg[id * 2].mn, Seg[id * 2 + 1].mn);
    Seg[id].mvalue = max(Seg[id * 2].mvalue, Seg[id * 2 + 1].mvalue);
    Seg[id].lazy = 0;
}

void pushDown(int id, int left, int right)
{
    if (Seg[id].lazy == 0)
    {
        return;
    }
    ll value = Seg[id].lazy;
    int mid = (left + right) / 2;
    Seg[2 * id].sum = value * (mid - left + 1);
    Seg[2 * id].mn = value;
    Seg[2 * id].mvalue = value;
    Seg[2 * id].lazy = value;
    Seg[2 * id + 1].sum = value * (right - mid);
    Seg[2 * id + 1].mn = value;
    Seg[2 * id + 1].mvalue = value;
    Seg[2 * id + 1].lazy = value;
    Seg[id].lazy = 0;
}

void Update(int id, int left, int right, int uleft, int uright, ll value)
{
    if (uleft > right || uright < left || Seg[id].mn >= value)
    {
        return;
    }
    if (uleft <= left && right <= uright && Seg[id].mvalue <= value)
    {
        Seg[id].sum = value * (right - left + 1);
        Seg[id].mn = value;
        Seg[id].mvalue = value;
        Seg[id].lazy = value;
        return;
    }
    pushDown(id, left, right);
    int mid = (left + right) / 2;
    Update(2 * id, left, mid, uleft, uright, value);
    Update(2 * id + 1, mid + 1, right, uleft, uright, value);
    Seg[id].sum = Seg[id * 2].sum + Seg[id * 2 + 1].sum;
    Seg[id].mn = min(Seg[id * 2].mn, Seg[id * 2 + 1].mn);
    Seg[id].mvalue = max(Seg[id * 2].mvalue, Seg[id * 2 + 1].mvalue);
}

int Query(int id, int left, int right, int qleft, ll &money)
{
    if (right < qleft || Seg[id].mn > money)
    {
        return 0;
    }
    if (qleft <= left && Seg[id].sum <= money)
    {
        money -= Seg[id].sum;
        return right - left + 1;
    }
    if (left == right)
    {
        return 0;
    }
    pushDown(id, left, right);
    int mid = (left + right) / 2;
    int ans = 0;
    ans += Query(2 * id, left, mid, qleft, money);
    ans += Query(2 * id + 1, mid + 1, right, qleft, money);
    return ans;
}

void Solve()
{
    Build(1, 1, n);
    while (q--)
    {
        int t, x;
        ll y;
        cin >> t >> x >> y;
        if (t == 1)
        {
            Update(1, 1, n, 1, x, y);
        }
        else
        {
            ll ans = Query(1, 1, n, x, y);
            cout << ans << endl;
        }
    }
}

int main()
{
    fixIO();
    File("716634G");
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