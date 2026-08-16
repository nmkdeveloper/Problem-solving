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

int N, K, M;
queue<pii> q;


void Read()
{
    cin >> N >> K >> M;
    FOR(i, 0, N - 1)
    {
        int x;
        cin >> x;
        q.push({x, i});
    }
}

void Solve()
{
    vector<int> res(N);
    FOR(i, 0, M - 1)
    {
        if (q.size())
        {
            pii cur = q.front();
            q.pop();
            res[cur.second]++;
            if (cur.first > K)
            {
                q.push(cur);
            }
        }
        else
        {
            break;
        }
    }
    FOR(i, 0, N - 1)
    {
        cout << res[i] << ' ';
    }
}

int main() 
{
    fixIO();
    File("MUAVE");
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