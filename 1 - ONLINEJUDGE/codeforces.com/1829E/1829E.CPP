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

ll Solve(int n, int m, vector<vi>& a)
{
    ll max_volume = 0;
    
    int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};

    vector<vb> visited(n, vb(m, false));
    FOR(i, 0, n - 1)
    {
        FOR(j, 0, m - 1)
        {
            if (!visited[i][j] && a[i][j] != 0)
            {
                
                ll cur_volume = 0;
                queue<pii> q;
                visited[i][j] = true;
                q.push({i, j});

                while(q.size())
                {
                    pii cur = q.front();
                    q.pop();
                    
                    cur_volume += a[cur.fi][cur.se];
                    
                    FOR(d, 0, 3)
                    {
                        int x = dx[d] + cur.fi, y = dy[d] + cur.se;
                        if (x >= 0 && x < n && y >= 0 && y < m && !visited[x][y] && a[x][y] != 0)
                        {
                            q.push({x, y});
                            visited[x][y] = true;
                        }
                    }
                }
                
                max_volume = max(max_volume, cur_volume);
            }
        }
    }

    return max_volume;
}

void Read()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n, m;
        cin >> n >> m;
        vector<vi> a;
        a.resize(n, vi(m));
        FOR(i, 0, n - 1)
        {
            FOR(j, 0, m - 1)
            {
                cin >> a[i][j];
            }
        }
        cout << Solve(n, m, a) << endl;
    }
}



int main() 
{
    fixIO();
    File("1829E");
    Read();
    return 0;
}

/**
 *  "Frieren: Vay theo cau chung ta phai lam gi de nguoi khac nho den chung ta chu?
 *   Himmel:  Cung khong co gi to tac, do la hay thay doi cuoc doi cua ai do 
 *            du chi mot chut. Toi thay chi can nhu vay la du roi."
 *
 *                                                   — Sousou no Frieren —
 *  ───────────────────────────────────────────────────────────────────────
 *  Template by : Nguyen Minh Khoi (github/nmkdeveloper)
 *  Created     : 2026.08.11
 */