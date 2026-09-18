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

int m;
unordered_map<ull, pair<int, char>> rules;

void Read()
{
    cin >> m;
}

void parseIP(const string &s, uint32_t &ip, int &n)
{
    int a = 0, b = 0, c = 0, d = 0;
    n = 32;
    int cnt = sscanf(s.c_str(), "%d.%d.%d.%d/%d", &a, &b, &c, &d, &n);
    if (cnt == 4) n = 32;
    ip = ((uint32_t)a << 24) | ((uint32_t)b << 16) | ((uint32_t)c << 8) | (uint32_t)d;
}

void Solve()
{
    rules.reserve(m * 2 + 5);
    FOR(i, 1, m)
    {
        char c;
        string s;
        cin >> c >> s;
        uint32_t ip;
        int n;
        parseIP(s, ip, n);
        if (c == '?')
        {
            int bestTime = INF;
            char bestType = 'A';
            FOR(L, 0, 32)
            {
                uint32_t prefix = (L == 0) ? 0u : (ip >> (32 - L));
                ull key = ((ull)L << 32) | prefix;

                auto it = rules.find(key);
                if (it != rules.end() && it->se.fi < bestTime)
                {
                    bestTime = it->se.fi;
                    bestType = it->se.se;
                }
            }
            if (bestTime == INF)
            {
                cout << 'Y' << endl;
            }
            else
            {
                cout << (bestType == 'A' ? 'Y' : 'N') << endl;
            }
        }
        else
        {
            uint32_t prefix = (n == 0) ? 0u : (ip >> (32 - n));
            ull key = ((ull)n << 32) | prefix;
            if (rules.find(key) == rules.end())
            {
                rules[key] = {i, c};
            }
        }
    }
}

int main()
{
    fixIO();
    File("717263C");
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
