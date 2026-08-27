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

const int MAXN = (int) 1e5 + 1;
int n;
ll a[MAXN];

void Read()
{
    cin >> n;
    FOR(i, 0, n - 1)
    {
        cin >> a[i];
    }
}

void Solve()
{
    FOR(i, 0, n - 1)
    {
        ll res = 1, cnt_res = 1;
        FOR (x, 2, a[i])
        {
            ll dcnt = 0;
            FOR(d, 1, x / d)
            {
                if (x % d == 0)
                {
                    dcnt += 2;
                    if (d == x / d)
                    {
                        dcnt--;
                    }
                }
            }
            if (dcnt > cnt_res)
            {
                res = x;
                cnt_res = dcnt;
            }
        }
        cout << res << ' ' << cnt_res << endl;
    }
}

int main() 
{
    fixIO();
    File("BAI1");
    Read();
    Solve();
    return 0;
}

/**
 *  "Frieren: Vay theo cau chung ta phai lam gi de nguoi khac nho den chung ta chu?
 *   Himmel:  Cung khong co gi to tac, do la hay thay doi cuoc doi cua ai do 
 *            du chi mot chut. Toi thay chi can nhu vay la du roi."
 *
 *                                                   — Sousou no Frieren —
 *  =======================================================================
 *  Template by : Nguyen Minh Khoi (github/nmkdeveloper)
 *  Created     : 2026.08.11
 */