#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<bool> vb;
typedef vector<string> vs;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef map<int, int> mii;
typedef map<ll, ll> mll;
typedef set<int> si;
typedef set<ll> sll;
typedef priority_queue<int> max_heap_i;
typedef priority_queue<int, vi, greater<int>> min_heap_i;
typedef priority_queue<ll> max_heap_ll;
typedef priority_queue<ll, vll, greater<ll>> min_heap_ll;

#define FOR(a, b, c) for (int a = (b); a <= (c); a++)
#define FORD(a, b, c) for (int a = (b); a >= (c); a--)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define REPD(i, n) for (int i = (n) - 1; i >= 0; i--)
#define endl '\n'
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;
const ll INF64 = 2e18 + 7;
const int MOD = 1e9 + 7;

#define debug(x) clog << #x << " = " << (x) << endl

void fixIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}

void File(const string &fileName = "")
{
    if (fopen((fileName + ".INP").c_str(), "r"))
    {
        freopen((fileName + ".INP").c_str(), "r", stdin);
        freopen((fileName + ".OUT").c_str(), "w", stdout);
    }
}

int n;
string s, t;

void Read()
{
    cin >> n;
    cin >> s;
    cin >> t;
}

void Solve()
{
    vi dif1, dif2;
    REP(i, n)
    {
        if (s[i] != t[i])
        {
            if (s[i] == '0')
            {
                dif1.pb(i);
            }
            else
            {
                dif2.pb(i);
            }
        }
    }
    if ((sz(dif1) + sz(dif2)) % 2 != 0)
    {
        cout << -1;
        return;
    }
    vpii operations;
    while(sz(dif1) > 1)
    {
        int pos1 = dif1.back();
        dif1.pop_back();
        int pos2 = dif1.back();
        dif1.pop_back();
        operations.pb({pos1 + 1, pos2 + 1});
    }
    while(sz(dif2) > 1)
    {
        int pos1 = dif2.back();
        dif2.pop_back();
        int pos2 = dif2.back();
        dif2.pop_back();
        operations.pb({pos1 + 1, pos2 + 1});
    }
    if (dif1.size() && dif2.size())
    {
        int pos1 = dif1.back();
        dif1.pop_back();
        int pos2 = dif2.back();
        dif2.pop_back();
        operations.pb({pos1 + 1, pos1 + 1});
        operations.pb({pos1 + 1, pos2 + 1});
    }
    cout << sz(operations) << endl;
    for (auto const& [fir, sec] : operations)
    {
        cout << fir << ' ' << sec << endl;
    }
}

int main()
{
    fixIO();
    File("ct_tst_25_bstr");
    Read();
    Solve();
    return 0;
}

/**
 *  "Frieren: Vay theo cau chung ta phai lam gi de nguoi khac nho den chung ta chu?
 *   Himmel:  Cung khong co gi to tac, do la hay thay doi cuoc doi cua ai do
 *            du chi mot chut. Toi thay chi can nhu vay la du roi."
 *
 *                                                   � Sousou no Frieren �
 *  =======================================================================
 *  Template by : Nguyen Minh Khoi (github/nmkdeveloper)
 *  Created     : 2026.08.11
 *
**/
