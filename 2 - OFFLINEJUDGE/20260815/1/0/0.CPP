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

const int MAXN = 1e7 + 15;
const int INF = 1e9 + 7;
const ll INF64 = 2e18 + 7;
const int MOD = 1e9 + 7;

#define debug(x) clog << #x << " = " << (x) << endl

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

int t;

void Read()
{
   cin >> t; 
}

void Solve()
{
    while(t --)
    {
        int a, b;
        cin >> a >> b;
        if (a >= b)
        {
            cout << a - b << endl;
            continue;
        }
        vi dist(MAXN, -1);
        vb visited(MAXN, false);
        queue<int> q;
        q.push(a);
        visited[a] = true;
        dist[a] = 0;
        while(q.size())
        {
            int cur = q.front();
            q.pop();
            if (cur == b)
            {
                break;
            }
            int tmp1 = cur - 1;
            if (tmp1 >= 0 && tmp1 < MAXN && !visited[tmp1])
            {
                visited[tmp1] = true;
                dist[tmp1] = dist[cur] + 1;
                q.push(tmp1);
            }
            int tmp2 = cur * 2;
            if (tmp2 < MAXN && !visited[tmp2])
            {
                visited[tmp2] = true;
                dist[tmp2] = dist[cur] + 1;
                q.push(tmp2);
            }
        }
        cout << dist[b] << endl;
    }
}

int main() 
{
    fixIO();
    File("0");
    Read();
    Solve();
    return 0;
}

/**
 *  "Frieren: Vay theo cau chung ta phai lam gi de nguoi khac nho den chung ta chu?
 *   Himmel:  Cung khong co gi to tac, do la hay thay doi cuoc doi cua ai do 
 *            du chi mot chut. Toi thay chi can nhu vay la du roi."
 *
 *                                                   — Sousou no Frieren —
 *  =======================================================================
 *  Template by : Nguyen Minh Khoi (github/nmkdeveloper)
 *  Created     : 2026.08.11
 */