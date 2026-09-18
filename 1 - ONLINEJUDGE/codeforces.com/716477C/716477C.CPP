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
vector<vi> child;
vll dist;

void Read()
{
    cin >> n >> q;
    child.resize(n + 1);
    dist.resize(n + 1, 0);
    FOR(i, 2, n)
    {
        int p, ll c;
        cin >> p >> c;
        child[i].pb(i);
        dist[i] = dist[p] + c;
    }
}

vi leafIdx;
vll leafDist;
vi L, R;
int leafCnt = 0;
vll seg;
vb lazy;

void Build(int id, int left, int right)
{
    if (left == right)
    {
        seg[id] = leafDist[l];
        return;
    }
    int mid = (left + right) / 2;
    Build(1 << id, left, mid);
    Build(1 << id | 1, mid + 1, right);
    seg[id] = min(seg[id << 1], seg[id << 1 | 1]);
}

void Push(int id)
{
    if (lazy[id])
    {
        lazy[id << 1] = true;
        seg[id << 1] = INF64;
        lazy[id << 1 | 1] = true;
        seg[id << 1 | 1] = INF64;
        lazy[id] = false;
    }
}

void Update(int id, int l, int r, int u, int v)
{
    if (v < l || r < u)
    {
        return;
    }
    if (u <= l && r <= v)
    {
        lazy[id] = true;
        seg[id] = INF64;
        {
            return;
        }
    }
    Push(id);
    int mid = (l + r) >> 1;
    Update(id << 1, l, mid, u, v);
    Update(id << 1 | 1, mid + 1, r, u, v);
    seg[id] = min(seg[id << 1], seg[id << 1 | 1]);
}

void Solve()
{

}

int main()
{
    fixIO();
    File("716477C");
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
