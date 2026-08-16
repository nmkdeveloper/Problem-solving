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

int n, m,k;
vi mv, ban;

void Read()
{
    cin >> n >> m >> k;
    mv.resize(m);
    ban.resize(k);
    FOR(i, 0, m - 1)
    {
        cin >> mv[i];
    }
    FOR(i, 0, k - 1)
    {
        cin >> ban[i];
    }
}

void Solve()
{
    int min_moves = 0, max_moves = 0, total_moves = 0;
    FOR(i, 0, m - 1)
    {
        if (mv[i] == 1)
        {
            total_moves--;
        }
        else
        {
            total_moves++;
        }
        min_moves = min(min_moves, total_moves);
        max_moves = max(max_moves, total_moves);
    }
    sort(all(ban));
    unordered_map<int, int> area;
    int lef = 1;
    for (auto rig : ban)
    {
        int cursz = rig - lef;
        if (cursz > 0)
        {
            area[lef] = cursz;
        }
        lef = rig + 1;
    }
    int tm = max_moves - min_moves;
    if (lef <= n)
    {
        area[lef] = n - lef + 1;
    }
    int total_pass = 0;
    for (auto e : area)
    {
        int siz = e.se;
        if (siz - tm > 0)
        {
            total_pass += (siz - tm);
        }
    }
    cout << total_pass;
}

int main()
{
    fixIO();
    File("pl_tk1_bai1");
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
