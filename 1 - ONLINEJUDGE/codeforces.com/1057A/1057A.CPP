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
vector<vi> router;

void Read()
{
    cin >> n;
    router.resize(n + 1);
    FOR(u, 2, n)
    {
        int v;
        cin >> v;
        router[v].pb(u);
    }
}

vi par;

void BFS()
{
    vb visited(n + 1, false);
    par.assign(n + 1, -1);
    queue<int> q;
    visited[1] = true;
    q.push(1);
    while(q.size())
    {
        int u = q.front();
        q.pop();
        for (auto v : router[u])
        {
            if (!visited[v])
            {
                visited[v] = true;
                par[v] = u;
                q.push(v);
            }
        }
    }
}

void Solve()
{
    BFS();
    stack<int> res;
    for (int x = n; x != -1; x = par[x])
    {
        res.push(x);
    }
    while(res.size())
    {
        cout << res.top() << ' ';
        res.pop();
    }
}

int main()
{
    fixIO();
    File("1057A");
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
