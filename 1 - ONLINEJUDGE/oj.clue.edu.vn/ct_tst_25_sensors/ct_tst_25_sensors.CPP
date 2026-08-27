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

const int MAXN = (int) 1e3 + 15;
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

int n, k;
vector<pii> sensors;

void Read()
{
    cin >> n >> k;
    sensors.resize(n);
    REP(i, n)
    {
        cin >> sensors[i].fi >> sensors[i].se;
    }
}

vector<string> plans;

void BT(string s)
{
    if (sz(s) == n)
    {
        plans.pb(s);
        return;
    }
    BT(s + '0');
    BT(s + '1');
}

int cnt(string plan)
{
    int tmp = 0;
    int x_min = -1, y_max = -1;
    REP(i, sz(plan))
    {
        if (plan[i] == '1')
        {
            if (x_min == -1 && y_max == -1)
            {
                tmp ++;
                x_min = sensors[i].fi;
                y_max = sensors[i].se;
                continue;
            }
            if (sensors[i].fi <= y_max)
            {
                x_min = min(x_min, sensors[i].fi);
                y_max = max(y_max, sensors[i].se);
            }
            else
            {
                tmp ++;
                x_min = sensors[i].fi;
                y_max = sensors[i].se;
            }
        }
    }
    return tmp;
}

ll POWER(ll a, int b)
{
    if (b == 0)
    {
        return 1;
    }
    if (b == 1)
    {
        return a;
    }
    ll tmp = POWER(a, b / 2) % MOD;
    if (b % 2 == 0)
    {
        return (tmp * tmp) % MOD;
    }
    else
    {
        return (((tmp * tmp) % MOD) * a) % MOD;
    }
}

void sub1()
{
    sort(all(sensors));
    ll res = 0;
    BT("");
    plans.erase(plans.begin());
    for (auto i : plans)
    {
        res = (res + POWER(1LL * cnt(i), k)) % MOD;
    }
    cout << res;
}

bool cmp(const pii &a, const pii &b)
{
    if (a.fi != b.fi)
    {
        return a.fi < b.fi;
    }
    return a.se > b.se;
}

void sub2()
{
    sort(all(sensors), cmp);
    ll res = 0;
    REP(i, n)
    {
        ll over = 0;
        REP(j, i)
        {
            if (sensors[j].se >= sensors[i].fi)
            {
                over++;
            }
        }
        ll fs = 1LL * n - 1LL - over;
        if (fs < 0)
        {
            continue;
        }
        res = (res + POWER(2, fs)) % MOD;
    }
    cout << res;
}

void Solve()
{
    if (n <= 16)
    {
        sub1();
    }
    else
    {
        sub2();
    }
}

int main()
{
    fixIO();
    File("ct_tst_25_sensors");
    Read();
    Solve();
    return 0;
}

/**
 *  "Frieren: Vay theo cau chung ta phai lam gi de nguoi khac nho den chung ta chu?
 *   Himmel:  Cung khong co gi to tac, do la hay thay doi cuoc doi cua ai do
 *            du chi mot chut. Toi thay chi can nhu vay la du roi."
 *
 *                                                   — Sousou no Frieren —
 *  =======================================================================
 *  Template by : Nguyen Minh Khoi (github/nmkdeveloper)
 *  Created     : 2026.08.11
 */
