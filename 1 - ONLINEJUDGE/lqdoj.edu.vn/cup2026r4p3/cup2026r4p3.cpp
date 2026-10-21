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
#define SET(k, n) ((n)  | BIT(k))
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

int k, t;

void Read()
{
    cin >> k;
    cin >> t;
}

namespace Sub1
{
    const int MAXM = (int) 15 * 1e7 + 7;
    int precompute[MAXM];
    map<int, bool> visited;
    map<ll, pair<string, int>> trace;
    void Query(ll n)
    {
        queue<pli> q;
        if (sz(trace) == 0)
        {
            q.push({0, 0});
        }
        else if (sz(trace) == 1)
        {
            q.push({(*trace.begin()).first, (*trace.begin()).second.second});
        }
        else if (sz(trace) > 1)
        {
            q.push({(*trace.rbegin()).first, (*trace.rbegin()).second.second});
        }
        visited[0] = true;
        trace[0] = {"", 0};
        while(sz(q))
        {
            ll cur_sum = q.front().first;
            if (cur_sum == n || cur_sum > (int) (1e5 + 7))
            {
                break;
            }
            int cur_pos = q.front().second;
            q.pop();
            cur_pos ++;
            ll sum1 = cur_sum - precompute[cur_pos];
            ll sum2 = cur_sum + precompute[cur_pos];
            if(!visited[sum1] && abs(sum1) <= (int) (1e5 + 7))
            {
                visited[sum1] = true;
                trace[sum1] = {trace[cur_sum].first + '-', cur_pos};
                q.push({sum1, cur_pos});
            }
            if(!visited[sum2] && abs(sum2) <= (int) (1e5 + 7))
            {
                visited[sum2] = true;
                trace[sum2] = {trace[cur_sum].first + '+', cur_pos};
                q.push({sum2, cur_pos});
            }
        }
        cout << sz(trace[n].first) << ' ' << trace[n].first;
    }
    void Solve()
    {
        iota(precompute, precompute + MAXM, 0);
        while(t --)
        {
            ll n;
            cin >> n;
            Query(n);
            cout << endl;
        }
    }
}

void Solve()
{
    if (k == 1)
    {
        Sub1::Solve();
    }
}

int main()
{
    fixIO();
    File("sign");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
