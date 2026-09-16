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

const int MAXN = 1005;
int n;
char c[MAXN];
int a[MAXN];

void Read()
{
    cin >> n;
    FOR(i, 1, n)
    {
        cin >> c[i] >> a[i];
    }
}

struct Node
{
    bool leaf;
    int m;
    int miny;
    int left;
    int right;
    Node() : leaf(false), m(0), miny(0), left(-1), right(-1) {}
};
vector<Node> tr;

int Build(int left, int right)
{
    if (left > right)
    {
        int id = sz(tr);
        tr.pb(Node());
        tr[id].leaf = true;
        tr[id].miny = INF + 1;
        return id;
    }
    int pos = -1;
    int maxm = -1;
    FOR(i, left, right)
    {
        if (c[i] == 'n' && a[i] > maxm)
        {
            maxm = a[i];
            pos = i;
        }
    }
    if (pos == -1)
    {
        int mn = INF + 1;
        FOR(i, left, right)
        {
            if (c[i] == 'y')
            {
                mn = min(mn, a[i]);
            }
        }
        int id = sz(tr);
        tr.pb(Node());
        tr[id].leaf = true;
        tr[id].miny = mn;
        return id;
    }
    else
    {
        int id = sz(tr);
        tr.pb(Node());
        tr[id].leaf = false;
        tr[id].m = maxm;
        int le = Build(left, pos - 1);
        int ri = Build(pos + 1, right);
        tr[id].left = le;
        tr[id].right = ri;
        return id;
    }
}

void Solve()
{
    tr.clear();
    int root = Build(1, n);
    vector<int> val;
    for (auto &node : tr)
    {
        if (!node.leaf)
        {
            val.pb(node.m);
        }
    }
    val.pb(INF);
    sort(all(val));
    val.erase(unique(all(val)), val.end());
    int N = sz(tr);
    int K = sz(val);
    vector<vector<int>> dp(N, vector<int>(K, 0));
    for (int u = N - 1; u >= 0; --u)
    {
        if (tr[u].leaf)
        {
            for (int j = 0; j < K; ++j)
            {
                if (tr[u].miny <= val[j])
                {
                    dp[u][j] = 1;
                }
                else
                {
                    dp[u][j] = 0;
                }
            }
        }
        else
        {
            int L = tr[u].left;
            int R = tr[u].right;
            int idxM = lower_bound(all(val), tr[u].m) - val.begin();
            for (int j = 0; j < K; ++j)
            {
                int noInc = dp[L][j] + dp[R][j];
                int res = noInc;
                if (val[j] >= tr[u].m)
                {
                    int inc = 1 + dp[L][idxM] + dp[R][idxM];
                    if (inc < res)
                    {
                        res = inc;
                    }
                }
                dp[u][j] = res;
            }
        }
    }
    int idxINF = lower_bound(all(val), INF) - val.begin();
    cout << dp[root][idxINF];
}

int main()
{
    fixIO();
    File("716323C");
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