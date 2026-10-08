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

#define BIT(n) (1 << (n))
#define SET(k, n) ((n) | BIT(k))
#define CLEAR(k, n) ((n) & ~BIT(k))
#define TOGGLE(k, n) ((n) ^ BIT(k))
#define CHECK(k, n) (!!((n) & BIT(k)))
#define MSB(x) ((x) == 0 ? -1 : 63 - __builtin_clzll(x))

#define debug(x) clog << #x << " = " << (x) << endl

const int MAXARR = 1e7 + 15;
const int INF = 1e9 + 7;
const ll INF64 = 2e18 + 7;
const int MOD = 1e9 + 7;

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

int t;

void Read()
{
    cin >> t;
}

vll money = {1000, 2000, 3000, 5000, 10000, 20000, 30000, 50000, 1000000, 2000000, 3000000, 5000000, 100000, 200000, 300000, 500000, 10000000000, 20000000000, 30000000000, 50000000000, 1000000000, 2000000000, 3000000000, 5000000000, 100000000, 200000000, 300000000, 500000000, 10000000, 20000000, 30000000, 50000000, 1000000000000000000, 2000000000000000000, 3000000000000000000, 5000000000000000000, 100000000000000000, 200000000000000000, 300000000000000000, 500000000000000000, 10000000000000000, 20000000000000000, 30000000000000000, 50000000000000000, 1000000000000000, 2000000000000000, 3000000000000000, 5000000000000000, 100000000000000, 200000000000000, 300000000000000, 500000000000000, 10000000000000, 20000000000000, 30000000000000, 50000000000000, 1000000000000, 2000000000000, 3000000000000, 5000000000000, 100000000000, 200000000000, 300000000000, 500000000000};

void Ans(ll w, int c)
{
    if (w % 1000 != 0)
    {
        cout << 0 << endl;
        return;
    }
    while(money[c] > w)
    {
        c --;
    }
    ll bestMoneyNotesCount = 0;
    ll ww = w;
    FORD(i, c, 0)
    {
        if (ww - money[i] >= 0)
        {
            bestMoneyNotesCount += (ww / money[i]);
            ww -= (money[i] * (ww / money[i]));
        }
    }
    vector<tuple<ll, ll, int>> cur, tmp;
    FORD(i, c, 0)
    {
        if (w / money[i] <= bestMoneyNotesCount)
        {
            cur.pb({w - (money[i] * (w / money[i])), w / money[i], i});
        }
    }
    int cnt = 0;
    FORD(i, c, 0)
    {
        for (auto e : cur)
        {
           auto [v, cn, curi] = e;
           if (v == 0 && cn == bestMoneyNotesCount)
           {
               cnt ++;
               continue;
           }
            if (i > curi)
            {
                tmp.pb(e);
                continue;
            }
            if (v / money[i] + cn > bestMoneyNotesCount)
            {
                continue;
            }
            if (v - (money[i] * (v / money[i])) < 0)
            {
                continue;
            }
            tmp.pb({v - (money[i] * (v / money[i])), cn + (v / money[i]), i});
        }
        cur = tmp;
        tmp = {};
    }
    for (auto e : cur)
    {
        auto [v, cn, curi] = e;
        if (v == 0 && cn == bestMoneyNotesCount)
        {
            cnt ++;
        }
    }
    cout << bestMoneyNotesCount << ' ' << cnt << endl;
}

void Solve()
{
    while(t --)
    {
        ll w;
        int c;
        cin >> w;
        cin >> c;
        Ans(w, c);
    }
}

int main()
{
    fixIO();
    File("717462A");
    Read();
    Solve();
    return 0;
}

/**
 *  "Frieren: Vay theo cau chung ta phai lam gi de nguoi khac nho den chung ta chu?
 *   Himmel:  Cung khong co gi to tac, do la hay thay doi cuoc doi cua ai do
 *            du chi mot chut. Toi thay chi can nhu vay la du roi."
 *
 *                                                   - Sousou no Frieren -
 *  =======================================================================
 *  Template by : Nguyen Minh Khoi (github/nmkdeveloper)
 *  Created     : 2026.09.14
 */
