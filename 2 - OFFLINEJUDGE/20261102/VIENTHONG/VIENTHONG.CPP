#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<long long, int> pli;
typedef pair<int, long long> pil;
typedef pair<long long, long long> pll;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<long long> vll;

#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define FORD(i, a, b) for (int i = (a); i >= (b); i--)
#define pb push_back
#define sz(x) (int) x.size()
#define all(x) x.begin(), x.end()
#define fi first
#define se second
#define endl '\n'

const int MOD = (int) 1e9 + 7;

void Fixio()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

void File(const string& filename = "")
{
    if (fopen((filename + ".INP").c_str(), "r"))
    {
        freopen((filename + ".INP").c_str(), "r", stdin);
        freopen((filename + ".OUT").c_str(), "w", stdout);
    }
}

int N, Q;
string S;

void Read()
{
    cin >> N >> Q;
    cin >> S;
}

const int MAXPRIME = 1e6 + 5;
vb isprime(MAXPRIME, true);
vi primes;
void Sieve()
{

    isprime[0] = isprime[1] = false;
    for(int i = 4; i < MAXPRIME; i += 2)
    {
        isprime[i]= false;
    }
    for(int i = 3; i * i < MAXPRIME; i += 2)
    {
        if (isprime[i])
        {
            for (int j = i * i; j < MAXPRIME; j += i * 2)
            {
                isprime[j] = false;
            }
        }
    }
    primes.pb(2);
    for(int i = 3; i < MAXPRIME; i += 2)
    {
        if (isprime[i])
        {
            primes.pb(i);
        }
    }
}

namespace Sub12
{
    const int MAXN = 3005;
    vector<vll> pref;

    void Build()
    {
        pref.assign(N + 1, vll(N + 1, 0));
        FOR(i, 1, N)
        {
            FOR(j, 1, N)
            {
                int val = 0;
                if (i < j && S[i - 1] != S[j - 1] && isprime[j - i])
                {
                    val = 1;
                }
                pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + val;
            }
        }
    }

    void Solve()
    {
        Build();
        while (Q--)
        {
            int L1, R1, L2, R2;
            cin >> L1 >> R1 >> L2 >> R2;
            ll res = pref[R1][R2] - pref[L1 - 1][R2] - pref[R1][L2 - 1] + pref[L1 - 1][L2 - 1];
            res = (res % MOD + MOD) % MOD;
            cout << res << endl;
        }
    }
}

void Solve()
{
    Sieve();
    Sub12::Solve();
}

int main()
{
    Fixio();
    File("VIENTHONG");
    Read();
    Solve();
    return 0;
}
