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

ll N;

void Read()
{
	cin >> N;
}

struct Matrix
{
	int m, n;
	ll mat[3][3];
};

Matrix Mul(Matrix A, Matrix B)
{
	Matrix C;
	C.m = A.m;
	C.n = B.n;
	FOR(i, 1, A.m)
	{
		FOR(j, 1, B.n)
		{
			C.mat[i][j] = 0;
			FOR(k, 1, A.n)
			{
				C.mat[i][j] = (C.mat[i][j] + A.mat[i][k] * B.mat[k][j]) % MOD;
			}
		}
	}
	return C;
}

Matrix Pow(Matrix A, ll p) { 
    if (p == 1)
    { 
        return A; 
    } 
    if (p % 2 == 1)
    { 
        return Mul(A, Pow(A, p - 1)); 
    }
    else
    { 
        Matrix B = Pow(A, p / 2); 
        return Mul(B, B); 
    } 
} 

ll Fib(ll n)
{
	if (n <= 2)
	{
		return 1;
	}
	Matrix A;
	A.m = 2;
	A.n = 2;
	A.mat[1][1] = 1;
	A.mat[1][2] = 1;
	A.mat[2][1] = 1;
	A.mat[2][2] = 0;
	A = Pow(A, n - 1);
	return A.mat[1][1];
}

void Solve()
{
	cout << Fib(N);
}

int main()
{
    fixIO();
    File("P09");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I Love You, My Love <3
 */