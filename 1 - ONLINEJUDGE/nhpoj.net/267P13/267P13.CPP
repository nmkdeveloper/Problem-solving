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

ll m, n, k;
vector<pll> banned;

void Read()
{
    cin >> m >> n >> k;
    banned.resize(k);
    REP(i, k)
    {
        cin >> banned[i].fi >> banned[i].se;
    }
}

const int MAXM = 10;
struct Matrix
{
    ll mat[10][10] = {};
};

Matrix Mul(const Matrix& A, const Matrix& B)
{
    Matrix C;
    REP(i, m)
    {
        REP(t, m)
        {
            REP(j, m)
            {
                C.mat[i][j] = (C.mat[i][j] + A.mat[i][t] * B.mat[t][j]) % MOD;
            }
        }
    }
    return C;
}

Matrix Pow(Matrix A, ll B)
{
    Matrix P;
    REP(i, m)
    {
        P.mat[i][i] = 1;
    }
    while(B)
    {
        if (B & 1)
        {
            P = Mul(P, A);
        }
        A = Mul(A, A);
        B >>= 1;
    }
    return P;
}

void Solve()
{
    Matrix T;
    REP(i, m)
    {
        REP(j, m)
        {
            T.mat[i][j] = 1;
        }
    }
    REP(i, m)
    {
        T.mat[i][i] = 0;
    }
    for (auto [f, s] : banned)
    {
        T.mat[f - 1][s - 1] = 0;
    }
    T = Pow(T, n - 1);
    ll ans = 0;
    REP(i, m)
    {
        REP(j, m)
        {
            ans = (ans + T.mat[i][j]) % MOD;
        }
    }
    cout << ans;
}

int main()
{
    fixIO();
    File("267P13");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
