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

using i128 = __int128_t;
void print_i128(i128 x)
{
    if (x == 0)
    {
        cout << 0;
        return;
    }
    if (x < 0)
    {
        cout << '-';
        x = -x;
    }
    string s;
    while (x > 0)
    {
        s += char('0' + x % 10);
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

i128 C2(i128 n)
{
    if (n < 2)
        return 0;
    return n * (n - 1) / 2;
}

i128 C3(i128 n)
{
    if (n < 3)
        return 0;
    return n * (n - 1) * (n - 2) / 6;
}

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

void Read()
{
}

void Solve()
{
    ll n_ll, k_ll;
    cin >> n_ll >> k_ll;
    i128 n = n_ll;
    i128 k = k_ll;
    i128 ans = 0;

    if (n == 2)
    {
        ans = 0;
    }
    else
    {
        if (k == 2)
        {
            ans = 4 * (n - 2) * (n + 1);
        }
        else if (k == 3)
        {
            i128 M = (n - 1) * (n - 1) - 4;
            i128 X = (n - 1) * (n - 3);
            i128 C_interior = 4 + 2 * M + 2 * M * M - 2 * X * X + 2 * X;
            i128 A = n * n - 2 * n;
            i128 B = (n - 2) * (n - 2);
            i128 C = n * (n - 2);
            i128 D = (n - 2) * (n - 1);
            i128 C_corner = C2(A) - C2(B) + C3(C) - 2 * C3(D) + C3(B);
            i128 S = n * n - 2 * n - 1;
            i128 n2_3n1 = n * n - 3 * n + 1;
            i128 n2_sq = (n - 2) * (n - 2);
            i128 n2_n3 = (n - 2) * (n - 3);
            i128 n1_n2 = (n - 1) * (n - 2);
            i128 n1_n3 = (n - 1) * (n - 3);
            i128 Case1 = S;
            i128 Case2 = 2 * (C2(S) - C2(n2_3n1) - C2(n2_sq) + C2(n2_n3));
            i128 Case3 = C3(S) - C3(n1_n2) - 2 * C3(n2_3n1) + 2 * C3(n2_sq) + C3(n1_n3) - C3(n2_n3);
            i128 C_edge = Case1 + Case2 + Case3;
            ans = 4 * C_corner + 4 * (n - 2) * C_edge + (n - 2) * (n - 2) * C_interior;
        }
    }
    print_i128(ans);
}

int main()
{
    fixIO();
    File("STALEMATE");
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