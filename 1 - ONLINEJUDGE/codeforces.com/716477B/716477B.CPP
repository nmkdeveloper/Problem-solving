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

int n;
set<string> vw;

void bw()
{
    const char* phuam[] =
    {
        "", "b", "c", "ch", "d", "g", "gh", "gi", "k", "kh", "l", "m",
        "n", "ng", "ngh", "p", "ph", "q", "r", "s", "t", "th", "tr", "v", "x"
    };

    const char* van[] =
    {
        "a", "ac", "ach", "ai", "am", "an", "ang", "anh", "ao", "ap", "at", "au", "ay",
        "e", "ec", "ech", "em", "en", "eng", "enh", "eo", "ep", "et", "eu",
        "i", "ia", "ich", "iec", "iem", "ien", "ieng", "iep", "iet", "ieu",
        "im", "in", "inh", "ip", "it", "iu",
        "o", "oc", "oi", "om", "on", "ong", "ooc", "oong", "op", "ot",
        "u", "ua", "uc", "ui", "um", "un", "ung", "uoc", "uoi", "uom", "uon",
        "uong", "uop", "uot", "uou", "up", "ut", "uu", "uy", "uya", "uych",
        "uyen", "uynh", "uyt", "uyu",
        "y", "yeu", "yem", "yen", "yet"
    };

    for (const char* p : phuam)
    {
        for (const char* v : van)
        {
            string i = p;
            string r = v;
            bool phuam = !i.empty();
            char r0 = r[0];
            if (i == "c" || i == "g" || i == "ng")
            {
                if (r0 == 'i' || r0 == 'e')
                {
                    continue;
                }
            }
            if (i == "k" || i == "gh" || i == "ngh")
            {
                if (!(r0 == 'i' || r0 == 'e'))
                {
                    continue;
                }
            }
            if (i == "q")
            {
                if (r0 != 'u')
                {
                    continue;
                }
            }
            if (sz(r) >= 2 && r[0] == 'i' && r[1] == 'e' && !phuam)
            {
                continue;
            }

            if (r0 == 'y' && phuam)
            {
                continue;
            }
            string w = i + r;
            bool ok = true;
            for (size_t j = 0; j + 1 < sz(w); ++j)
            {
                if (w[j] == w[j + 1])
                {
                    ok = false;
                    break;
                }
            }
            if (ok)
            {
                vw.insert(w);
            }
        }
    }
}

void Read()
{
    cin >> n;
}

void Solve()
{
    bw();
    string s;
    while (n--)
    {
        cin >> s;
        if (vw.find(s) != vw.end())
        {
            cout << "co" << endl;
        }
        else
        {
            cout << "khong" << endl;
        }
    }
}

int main()
{
    fixIO();
    File("716477B");
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
