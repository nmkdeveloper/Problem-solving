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

int N, Q, K;
string S;

void Read()
{
    cin >> N >> Q >> K;
    cin >> S;
}

void BFS(string s)
{
    unordered_set<string> visited;
    queue<string> q;
    q.push(s);
    visited.insert(s);
    while(sz(q))
    {
        string cur = q.front();
        q.pop();

        ll pref[sz(cur) + 1];
        pref[0] = 0;
        FOR(i, 1, sz(cur))
        {
            pref[i] = pref[i - 1] + cur[i - 1] - '0';
        }
        REP(i, sz(cur))
        {
            if (cur[i] == '1')
            {
                for (int left = i - K; left >= 0; left -= K)
                {
                    if (pref[i + 1] - pref[left] == 1)
                    {
                        string tmp = cur;
                        tmp[i] = '0';
                        tmp[left] = '1';
                        if (!visited.count(tmp))
                        {
                            visited.insert(tmp);
                            q.push(tmp);
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                for (int right = i + K; right < sz(cur); right += K)
                {
                    if (pref[right + 1] - pref[i] == 1)
                    {
                        string tmp = cur;
                        tmp[i] = '0';
                        tmp[right] = '1';
                        if (!visited.count(tmp))
                        {
                            visited.insert(tmp);
                            q.push(tmp);
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }
    cout << sz(visited) % MOD << endl;
}

void Solve()
{
    while(Q --)
    {
        int left, right;
        cin >> left >> right;
        left --;
        right --;
        string tmp = "";
        FOR(i, left, right)
        {
            tmp += S[i];
        }
        BFS(tmp);
    }
}

int main()
{
    fixIO();
    File("SEATS");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
