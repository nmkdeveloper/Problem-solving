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

const int MAXARR = 1e7 + 15;
const int INF = 1e9 + 7;
const ll INF64 = 2e18 + 7;
const int MOD = 1e9 + 7;

#define debug(x) clog << #x << " = " << (x) << endl

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

void Solve(const int& n, const int& m, const vi& a)
{
    int ans = 0;
    vector<int> geq(m + 2, 0);
    FORD(x, m, 1)
    {
        geq[x] = geq[x + 1] + a[x];
    }
    FOR(x, 1, m)
    {

        int cnt = geq[x];
        if (2 * x <= m)
        {
            cnt += a[2 * x];
        }
        ans = max(ans, cnt);
    }
    int mi1 = 0;
    int mi2 = 0;
    FORD(v, m, 1)
    {
        if (mi1 != 0)
        {
            if (mi1 != 2 * v)
            {
                ans = max(ans, a[v] + a[mi1]);
            }
            else if (mi2 != 0)
            {
                ans = max(ans, a[v] + a[mi2]);
            }
        }
        if (mi1 == 0 || a[v] > a[mi1])
        {
            mi2 = mi1;
            mi1 = v;
        }
        else if (mi2 == 0 || a[v] > a[mi2])
        {
            mi2 = v;
        }
    }
    cout << ans << endl;
}

void Read()
{
    int t;
    cin >> t;
    while(t --)
    {
        int n, m;
        cin >> n >> m;
        vi a(m + 2, 0);
        REP(i, n)
        {
            int x;
            cin >> x;
            a[x] ++;
        }
        Solve(n, m, a);
    }
}

int main()
{
    fixIO();
    File("2258B1");
    Read();
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
 *  Created     : 2026.08.11
 */
