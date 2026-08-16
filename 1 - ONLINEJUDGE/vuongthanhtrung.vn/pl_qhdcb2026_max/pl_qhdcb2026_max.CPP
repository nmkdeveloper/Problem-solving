#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef pair<int, int> pii;
typedef map<int, int> mii;

#define FOR(a, b, c) for(int a = (b); a <= (c); a++)
#define REV(a, b, c) for(int a = (b); a >= (c); a--)
#define endl '\n'
#define fi first
#define se second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()

#define debug(x) clog << x << endl

void fixIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}

void File(const string &fileName = "")
{
    if(fopen((fileName + ".INP").c_str(), "r"))
    {
        freopen((fileName + ".INP").c_str(), "r", stdin);
        freopen((fileName + ".OUT").c_str(), "w", stdout);
    }
}

const ll INF = 1e18;
int m, n;
vector<vector<ll>> a;

void Read()
{
    cin >> m >> n;
    a.resize(m + 1, vector<ll>(n + 1));
    FOR(i, 1, m)
    {
        FOR(j, 1, n)
        {
            cin >> a[i][j];
        }
    }
}

void Solve()
{
    vector<vector<ll>> dp;
    dp.assign(m + 1, vector<ll>(n + 2, -INF));
    FOR(j, 1, n)
    {
        dp[1][j] = a[1][j];
    }
    FOR(i, 2, m)
    {
        FOR(j, 1, n)
        {
            dp[i][j] = max({dp[i - 1][j], dp[i - 1][j - 1], dp[i - 1][j + 1]}) + a[i][j];
        }
    }
    ll ans = -INF;
    FOR(j, 1, n)
    {
        ans = max(ans, dp[m][j]);
    }
    cout << ans;
}

int main() 
{
    fixIO();
    File("MAX");
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
 *  ───────────────────────────────────────────────────────────────────────
 *  Template by : Nguyen Minh Khoi (github/nmkdeveloper)
 *  Created     : 2026.08.11
 */