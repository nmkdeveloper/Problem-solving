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

const int MAXN = (int) 3e5 + 8;
const int MAXM = (int)1e6 + 8;
int n, m;
struct Segment
{
    int left;
    int right;
    int weight;
};
Segment a[MAXN];

void Read()
{
    cin >> n >> m;
    FOR(i, 1, n)
    {
        cin >> a[i].left >> a[i].right >> a[i].weight;
    }
}

int ST[4 * MAXM];
int lazy[4 * MAXM];

void Build(int id, int left, int right)
{
    ST[id] = 0;
    lazy[id] = 0;
    if (left == right)
    {
        return;
    }
    int mid = (left + right) / 2;
    Build(id * 2, left, mid);
    Build(id * 2, mid + 1, right);
}

void pushDown(int id)
{
    if (lazy[id] != 0)
    {
        ST[id * 2] += lazy[id];
        lazy[id * 2] += lazy[id];
        ST[id * 2 + 1] += lazy[id];
        lazy[id * 2 + 1] += lazy[id];
        lazy[id] = 0;
    }
}

void Update(int id, int left, int right, int qleft, int qright, int val)
{
    if (qleft > right || qright < left)
    {
        return;
    }
    if (qleft <= left && right <= qright)
    {
        ST[id] += val;
        lazy[id] += val;
        return;
    }
    pushDown(id);
    int mid = (left + right) / 2;
    Update(id * 2, left, mid, qleft, qright, val);
    Update(id * 2 + 1, mid + 1, right, qleft, qright, val);
    ST[id] = min(ST[id * 2], ST[id * 2 + 1]);
}

bool cmp(Segment &sega, Segment &segb)
{
    return sega.weight < segb.weight;
}

void Solve()
{
    sort(a + 1, a + n + 1, cmp);
    Build(1, 1, m - 1);
    int ans = INF, left = 1;
    FOR(right, 1, n)
    {
        if (a[right].left <= a[right].right - 1)
        {
            Update(1, 1, m - 1, a[right].left, a[right].right - 1, 1);
        }
        while(ST[1] >= 1)
        {
            ans = min(ans, a[right].weight - a[left].weight);
            if (a[left].left <= a[left].right - 1)
            {
                Update(1, 1, m - 1, a[left].left, a[left].right - 1, -1);
            }
            left++;
        }
    }
    cout << ans;
}

int main()
{
    fixIO();
    File("716634D");
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