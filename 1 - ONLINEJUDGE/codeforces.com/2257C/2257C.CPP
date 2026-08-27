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

vi cnt_ds(int n, const vi& p, const vb& d)
{
    vi ds(n + 1, 0);
    FOR(i, 1, n)
    {
        if (d[i])
        {
            ds[i] = 1;
        }
    }
    FORD(i, n, 2)
    {
        ds[p[i]] += ds[i];
    }
    return ds;
}

vi cnt_cp(int n, const vector<vi>& child, const vb& d, const vi& ds)
{
    vi c;
    FOR(u, 1, n)
    {
        vi db;
        for (auto v : child[u])
        {
            if (ds[v] > 0)
            {
                db.pb(v);
            }
        }
        if (!db.size())
        {
            continue;
        }
        if (d[u])
        {
            for (auto v : db)
            {
                c.pb(v);
            }
        }
        else
        {
            FOR(i, 1, sz(db) - 1)
            {
                c.pb(db[i]);
            }
        }
    }
    return c;
}

void ReadSolve()
{
    int t;
    cin >> t;
    while(t --)
    {
        int n;
        cin >> n;
        vi p(n + 1);
        vector<vi> child(n + 1);
        FOR(i, 2, n)
        {
            cin >> p[i];
            child[p[i]].pb(i);
        }
        int m;
        cin >> m;
        vb d(n + 1, false);
        REP(i, m)
        {
            int x;
            cin >> x;
            d[x] = true;
        }
        vi ds = cnt_ds(n, p, d);
        vi c = cnt_cp(n, child, d, ds);
        cout << sz(c);
        for (auto v : c)
        {
            cout << ' ' << v;
        }
        cout << endl;
    }
}

int main() 
{
    fixIO();
    File("2257C");
    ReadSolve();
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