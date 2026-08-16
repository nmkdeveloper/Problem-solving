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

bool BFS(int n, int m, vb& visited)
{
    queue<int> q;
    visited[n] = true;
    q.push(n);
    while(q.size())
    {
        int u = q.front();
        q.pop();
        if (u == m)
        {
            clog << u << endl;
            return true;
        }
        if (u % 3 == 0)
        {
            int a = u / 3, b = u - a;
            q.push(a);
            q.push(b);
        }
    }
    return false;
}

string Solve(int n, int m)
{
    vb visited(n + 15, false);
    if (BFS(n, m, visited))
    {
        return "YES";
    }
    return "NO";
}

void Read()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n, m;
        cin >> n >> m;
        if (m > n)
        {
            cout << "NO" << endl;
        }
        else
        {
            cout << Solve(n, m) << endl;
        }
    }
}

int main()
{
    fixIO();
    File("1829D");
    Read();
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
