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

int N;

void Read()
{
    cin >> N;
}

vector<pii> divs(int num)
{
    vector<pii> tmp;
    for (int i = 1; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            tmp.pb({i, num / i});
        }
    }
    return tmp;
}

vector<bool> visited;

void Solve()
{
    set<int> st;
    visited.assign(N + 1, false);
    queue<vector<pii>> q;
    visited[N] = true;
    q.push(divs(N));
    while(!q.empty())
    {
        vector<pii> cur = q.front();
        q.pop();
        for (auto i : cur)
        {
            int x = i.fi, y = i.se, cal = (x - 1) * (y + 1);
            st.insert(cal);
            if (cal != 0)
            {
                if (!visited[cal])
                {
                    q.push(divs(cal));
                    visited[cal] = true;
                }
            }
        }
    }
    cout << sz(st) << endl;
    while(st.size())
    {
        auto it = st.begin();
        cout << *it << ' ';
        st.erase(it);
    }
}

int main() 
{
    fixIO();
    File("ZERO");
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