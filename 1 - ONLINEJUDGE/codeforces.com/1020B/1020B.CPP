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
vector<vi> report;

void Read()
{
    cin >> n;
    report.resize(n + 1);
    FOR(i, 1, n)
    {
        int p;
        cin >> p;
        report[i].pb(p);
    }
}

int BFS(int x)
{
    vb visited(n + 1, false);
    queue<int> q;
    q.push(x);
    visited[x] = true;
    while(q.size())
    {
        int u = q.front();
        q.pop();
        for (auto v : report[u])
        {
            if (visited[v])
            {
                return v;
            }
            else
            {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return 0;
}

void Solve()
{
    FOR(i, 1, n)
    {
        cout << BFS(i) << ' ';
    }
}

int main()
{
    fixIO();
    File("1020B");
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
