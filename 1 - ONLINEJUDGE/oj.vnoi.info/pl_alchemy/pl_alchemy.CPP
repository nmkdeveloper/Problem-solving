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
unordered_map<string, vector<string>> prepa;
unordered_map<string, bool> visited;
unordered_map<string, int> dist;
string A, B;

void Read()
{
    cin >> n;
    FOR(i, 0, n - 1)
    {
        string a, b, c;
        cin >> a >> b >> c;
        prepa[a].pb(c);
        visited[a] = visited[c] = false;
        dist[a] = dist[c] = -1;
    }
    cin >> A;
    cin >> B;
    visited[A] = visited[B] = false;
}

void Solve()
{
    queue<string> q;
    q.push(A);
    visited[A] = true;
    dist[A] = 0;
    while(q.size())
    {
        string u = q.front();
        q.pop();
        for (auto v : prepa[u])
        {
            if (!visited[v])
            {
                visited[v] = true;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    if (!visited[B])
    {
        cout << -1;
    }
    else
    {
        cout << dist[B];
    }
}

int main() 
{
    fixIO();
    File("ALCHEMY");
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