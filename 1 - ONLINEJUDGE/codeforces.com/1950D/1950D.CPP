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

vi binde;

void BT(int bin)
{
    if (bin > 1000000)
    {
        return;
    }
    if (bin > 1)
    {
        binde.pb(bin);
    }
    BT(bin * 10);
    BT(bin * 10 + 1);
}

bool BFS(int n)
{
    unordered_set<int> visited;
    queue<int> q;
    q.push(n);
    visited.insert(n);
    while(q.size())
    {
        int cur = q.front();
        q.pop();
        if (cur == 1)
        {
            return true;
        }
        for (int i : binde)
        {
            if (i > cur)
            {
                break;
            }
            if (cur % i == 0)
            {
                int nv = cur / i;
                if (visited.find(nv) == visited.end())
                {
                    visited.insert(nv);
                    q.push(nv);
                }
            }
        }
    }
    return false;
}

string Solve(int n)
{
    if (BFS(n))
    {
        return "YES";
    }
    return "NO";
}

void Read()
{
    BT(1);
    sort(all(binde));
    int t;
    cin >> t;
    while(t--)
    {
        ll n;
        cin >> n;
        if (n == 1)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << Solve(n) << endl;
        }
    }
}

int main()
{
    fixIO();
    File("1950D");
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
