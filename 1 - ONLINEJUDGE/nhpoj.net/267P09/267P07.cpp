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

ll n, a, b, c, p, q, r, d, m;

void Read()
{
	cin >> n >> a >> b >> c >> p >> q >> r >> d >> m;
}

struct Matrix
{
	int siz;
	ll mat[5][5];
};

Matrix iden(int s)
{
	Matrix I;
	I.siz = s;
	FOR(i, 1, s)
	{
		FOR(j, 1, s)
		{
			I.mat[i][j] = (i == j) ? 1 : 0;
		}
	}
	return I;
}


Matrix Mul(Matrix A, Matrix B)
{
	Matrix C;
	C.siz = A.siz;
	FOR(i, 1, A.siz)
	{
		FOR(j, 1, B.siz)
		{
			C.mat[i][j] = 0;
			FOR(k, 1, A.siz)
			{
				C.mat[i][j] = (C.mat[i][j] + A.mat[i][k] * B.mat[k][j]) % m;
			}
		}
	}
	return C;
}

Matrix Pow(Matrix A, ll e)
{
	Matrix R = iden(A.siz);
	while (e > 0)
	{
		if (e & 1)
		{
			R = Mul(R, A);
		}
		A = Mul(A, A);
		e >>= 1;
	}
	return R;
}

ll SolveF()
{
	if (n == 0) 
	{
		return a % m;
	}
	if (n == 1) 
	{
		return b % m;
	}
	if (n == 2) 
	{
		return c % m;
	}
	if (m <= 1)
	{
		return 0;
	}
	Matrix M;
	M.siz = 4;
	M.mat[1][1] = p % m;
	M.mat[1][2] = q % m;
	M.mat[1][3] = r % m;
	M.mat[1][4] = d % m;
	M.mat[2][1] = 1;
	M.mat[2][2] = 0;
	M.mat[2][3] = 0;
	M.mat[2][4] = 0;
	M.mat[3][1] = 0;
	M.mat[3][2] = 1;
	M.mat[3][3] = 0;
	M.mat[3][4] = 0;
	M.mat[4][1] = 0;
	M.mat[4][2] = 0;
	M.mat[4][3] = 0;
	M.mat[4][4] = 1;
	Matrix P = Pow(M, n - 2);
	ll ans = 0;
	ans = (ans + P.mat[1][1] * (c % m)) % m;
	ans = (ans + P.mat[1][2] * (b % m)) % m;
	ans = (ans + P.mat[1][3] * (a % m)) % m;
	ans = (ans + P.mat[1][4]) % m;
	return ans;
}

void Solve()
{
	cout << SolveF();
}

int main()
{
    fixIO();
    File("P07");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I Love You, My Love <3
 */