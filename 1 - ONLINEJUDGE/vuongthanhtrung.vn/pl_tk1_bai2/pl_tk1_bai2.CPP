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

int m, n;

void Read()
{
    cin >> m >> n;
}

void Solve()
{
    vi dp(m + 1, 0);
    int cnt = 0;
    while (dp[m] < n)
    {
        cnt ++;
        REV(i, n, 1)
        {
            dp[i] += 1 + dp[i - 1];
        }
    }
    cout << cnt;
}

int main()
{
    fixIO();
    File("pl_tk1_bai2");
    Read();
    Solve();
    return 0;
}

/**
 *  "Chua ngo, chua trao, chua gan bo,
 *   da hon, da nho, da dau thuong."
 *                              — Xuan Dieu
 *
 *  Code by   : Nguyen Minh Khoi (github/nmkdeveloper)
 *  Created   : 2026.08.02
 */
