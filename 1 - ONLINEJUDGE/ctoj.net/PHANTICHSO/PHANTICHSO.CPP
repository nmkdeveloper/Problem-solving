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

vi Primes;

void Sieve()
{
    const int MAXPRIMES = (int) 1e5 + 7;
    vb isPrime(MAXPRIMES, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 4; i < MAXPRIMES; i += 2)
    {
        isPrime[i] = false;
    }
    for (int i = 3; i * i < MAXPRIMES; i += 2)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j < MAXPRIMES; j += i * 2)
            {
                isPrime[j] = false;
            }
        }
    }
    Primes.pb(2);
    for (int i = 3; i < MAXPRIMES; i += 2)
    {
        if (isPrime[i])
        {
            Primes.pb(i);
        }
    }
}

int Solve(int n)
{
    auto it = lower_bound(all(Primes), n);
    int cnt = 0;
    while (it != Primes.end())
    {
        if ()
    }
}

void Read()
{
    Sieve();
    int n;
    while(cin >> n)
    {
        cout << Solve(n) << endl;
    }
}

int main()
{
    fixIO();
    File("PHANTICHSO");
    Read();
    return 0;
}
