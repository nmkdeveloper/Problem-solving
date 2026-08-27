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
string s;
vector<vi> adj;
vb visited;

void Read()
{
    cin >> n;
    cin >> s;
    adj.resize(n + 1);
    visited.assign(n + 1, false);
    FOR(i, 1, n - 1)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
}

vi BFS(int x)
{
    vi tmp;
    queue<int> q;
    q.push(x);
    tmp.pb(x);
    visited[x] = true;
    while(q.size())
    {
        int u = q.front();
        q.pop();
        for (auto v : adj[u])
        {
            if (!visited[v])
            {
                visited[v] = true;
                tmp.pb(v);
                q.push(v);
            }
        }
    }
    return tmp;
}

void Solve()
{
    int cnt = 0;
    vector<vi> tmp;
    FOR(i, 1, n)
    {
        if (!visited[i])
        {
           tmp.pb(BFS(i));
        }
    }
    for (auto e : tmp)
    {
        int cnt_black = 0, cnt_white = 0;
        for (auto node : e)
        {
            if (s[node - 1] == '0')
            {
                cnt_white++;
            }
            else
            {
                cnt_black++;
            }
        }
        cnt += (min(cnt_white, cnt_black) + 1);
    }
    cout << cnt;
}

int main() 
{
    fixIO();
    File("TRANGDEN");
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