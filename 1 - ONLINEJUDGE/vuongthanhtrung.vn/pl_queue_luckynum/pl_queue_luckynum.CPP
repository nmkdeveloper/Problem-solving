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

const int N = 205;
int k;
int f[N][N];
int mu[N];

void Read()
{
    cin >> k;
}

void Solve()
{
    FOR(i, 0, 200)
    {
        FOR(j, 0, 200 - i)
        {
            f[i][j] = -1;
        }
    }
    mu[0] = 1 % k;
    FOR(i, 1, 200)
    {
        mu[i] = (mu[i - 1] * 10) % k;
    }
    queue<pii> q;
    q.push({0, 1});
    f[0][1] = 6 % k;
    q.push({1, 0});
    f[1][0] = 8 % k;
    while (sz(q))
    {
        int x = q.front().fi;
        int y = q.front().se;
        q.pop();
        if (f[x][y] == 0)
        {
            FOR(i, 1, x) cout << 8;
            FOR(i, 1, y) cout << 6;
            cout << endl;
            return;
        }
        if (x + y == 200) continue;
        if (f[x][y + 1] == -1)
        {
            f[x][y + 1] = (f[x][y] * 10 + 6) % k;
            q.push({x, y + 1});
        }
        if (f[x + 1][y] == -1)
        {
            f[x + 1][y] = (8 * mu[x + y] + f[x][y]) % k;
            q.push({x + 1, y});
        }
    }
    cout << -1;
}

int main() 
{
    fixIO();
    File("LUCKYNUM");
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
 *  Created   : 2026.08.03
 */
