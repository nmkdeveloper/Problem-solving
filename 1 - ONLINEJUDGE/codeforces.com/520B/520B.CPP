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

void Read()
{
    cin >> n >> m;
}

const int MAXN = 20005;

int BFS()
{
    if (n >= m)
    {
        return n - m;
    }
    queue<int> q;
    vi dist(MAXN, -1);
    q.push(n);
    dist[n] = 0;
    while(q.size())
    {
        int u = q.front();
        q.pop();
        if (u == m)
        {
            return dist[u];
        }
        if (u * 2 < MAXN && dist[u * 2] == -1)
        {
            dist[u * 2] = dist[u] + 1;
            q.push(u * 2);
        }
        if (u - 1 > 0 && dist[u - 1] == -1)
        {
            dist[u - 1] = dist[u] + 1;
            q.push(u - 1);
        }
    }
    return -1;
}

void Solve()
{
    cout << BFS();
}

int main()
{
    fixIO();
    File("520B");
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

