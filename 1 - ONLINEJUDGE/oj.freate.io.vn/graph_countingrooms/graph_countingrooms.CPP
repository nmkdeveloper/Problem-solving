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

int n, m;
vector<string> mp;

void Read()
{
    cin >> n >> m;
    mp.resize(n);
    FOR(i, 0, n - 1)
    {
        cin >> mp[i];
    }
}

vector<vb> visited;

int dx [] = {1, -1, 0, 0}, dy [] = {0, 0, 1, -1};

void DFS(int x, int y)
{
    if (visited[x][y])
    {
        return;
    }
    visited[x][y] = true;
    FOR(i, 0, 3)
    {
        int nx = dx[i] + x, ny = dy[i] + y;
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && mp[nx][ny] != '#')
        {
            DFS(nx, ny);
        }
    }
}

void Solve()
{
    int res = 0;
    visited.assign(n, vb(m, false));
    FOR(i, 0, n - 1)
    {
        FOR(j,  0, m - 1)
        {
            if (mp[i][j] == '.' && !visited[i][j])
            {
                DFS(i, j);
                res++;
            }
        }
    }
    cout << res;
}

int main() 
{
    fixIO();
    File("graph_countingrooms");
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