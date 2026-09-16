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

int n, m, invxy = 0, d, cnf;
int x1, y1, x2, y2, k, x0, y0;

void Read()
{
    cin >> n >> m;
    cin >> x1 >> y1 >> x2 >> y2;
}

void Solve()
{
    if (n * m & 1)
    {
        cout << -1;
        return;
    }
    if (min(n, m) == 2)
    {
        if (n == 2)
        {
            if (x1 != x2 && (y1 > 1 && y1 < m))
            {
                cout << -1;
                return;
            }
            FOR(j, 1, m)
            {
                cout << "1 " << j << endl;
            }
            REPD(j, m)
            {
                cout << "2 " << j << endl;
            }
            cout << "1 1";
            return;
        }
        else
        {
            if (y1 != y2 && x1 > 1 && x1 < n)
            {
                cout << -1;
                return;
            }
            FOR(i, 1,  n)
            {
                cout << i << " " << endl;
            }
            REPD(i, n)
            {
                cout << i << " 2" << endl;
            }
            cout << "1 1";
            return;
        }
    }
    auto check_3 = [&]()
    {
        if (min(m, n) == 2 || min(m, n) > 3)
        {
            return true;
        }
        if (n == 3)
        {
            if (x1 == x2 && (x1 == 2) && min(y1, y2) % 2 == 1)
            {
                return false;
            }
        }
        if (m == 3)
        {
            if (y1 == y2 && (y1 == 2) && (min(x1, x2) % 2 == 1))
            {
                return false;
            }
        }
        return true;
    }
    if (!check_3())
    {
        cout << -1;
        return;
    }
    x1 --;
    x2 --;
    y1 --;
    y2 --;
    bool invt = false;
    if (y1 == y2)
    {
        invt = true;
        swap(n, m);
        swap(x1, y1);
        swap(x2, y2);
    }
    if (y1 > y2)
    {
        swap(y1, y2);
    }
    vector<vector<char>> r(
        n, vector<char>(
            m, ' '
        )
    ), r_a(
        n, vector<char>(
            m, ' '
        )
    );
    auto move_v = [&]()
    {
        REP(j, m - 1)
        {
            r[0][j] = 'R';
        }
        r[0][m - 1] = 'D';
        for (int i = 1; i < n - 2; i += 2)
        {
            for (int j = 2; j < m - 1; j ++)
            {
                r[i][j] = 'L';
                r[i + 1][j] = 'R';
            }
            r[i][1] = 'D';
            r[i][m - 1] = 'L';
            r[i + 1][1] = 'R';
            r[i + 1][m - 1] = 'D';
        }
        for (int j = 1; j < m; j += 2)
        {
            r[n - 2][j] = 'D';
            r[n - 2][j + 1] = 'L';
            r[n - 1][j] = 'L';
            r[n - 1][j + 1] = 'U';
        }
        for (int i = 1; i < n; i ++)
        {
            r[i][0] = 'U';
        }
    }
    if (n & 1)
    {
        move_v();
    }
    else
    {
        move_v
    }
}

int main()
{
    fixIO();
    File("");
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