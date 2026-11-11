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
typedef vector<long, long> vll;

#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define FORD(i, a, b) for (int i = (a); i >= (b); i--)
#define pb push_back
#define sz(x) (int) x.size()
#define all(x) x.begin(), x.end()
#define fi first
#define se second
#define endl '\n'

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

void Read()
{

}

void Solve()
{

}

int main()
{
    Fixio();
    File("");
    Read();
    Solve();
    return 0;
}
