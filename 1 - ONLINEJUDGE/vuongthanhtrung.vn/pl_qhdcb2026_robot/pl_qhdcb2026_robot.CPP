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

int n;
vector<vector<char>> mp;

void Read()
{
    cin >> n;
    mp.resize(n + 1, vector<char>(n + 1));
    FOR(i, 1, n)
    {
        FOR(j, 1, n)
        {
            cin >> mp[i][j];
        }
    }
}

void Solve()
{
    vector<vector<string>> dp;
    dp.assign(n + 1, vector<string>(n + 1, "11111111111111111111111111111111111111111111111111"));
    dp[1][1] = string(1, mp[1][1]);
    FOR(i, 1, n)
    {
        FOR(j, 1, n)
        {
            if (i == 1 && j == 1)
            {
                continue;
            }
            else if (i == 1)
            {
                dp[1][j] = dp[1][j - 1] + mp[1][j];
            }
            else if (j == 1)
            {
                dp[i][1] = dp[i - 1][1] + mp[i][1];
            }
            else
            {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + mp[i][j];
            }
        }
    }
    cout << dp[n][n];
}

int main() 
{
    fixIO();
    File("ROBOT");
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