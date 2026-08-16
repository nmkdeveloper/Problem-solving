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

int BFS(int x, int n, vi p)
{
    queue<int> q;
    q.push(x);
    int d = 0;
    while(q.size())
    {
        int u = q.front();
        q.pop();
        d++;
        int ne = p[u];
        if (ne == x)
        {
            return d;
        }
        q.push(ne);
    }
    return d;
}

void Solve(int n, vi p)
{
    FOR(i, 1, n)
    {
        cout << BFS(i, n, p) << " ";
    }
}

void Read()
{
    int q;
    cin >> q;
    while(q--)
    {
        int n;
        cin >> n;
        vi p(n + 1);
        FOR(i, 1, n)
        {
            cin >> p[i];
        }
        Solve(n, p);
        cout << endl;
    }
}

int main()
{
    fixIO();
    File("1249B1");
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
