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

string s;
int q;

void Read()
{
    cin >> s;
    cin >> q;
}

struct Node
{
    int t;
    int o;
    int c;
};

vector<Node> Seg(4000007);

Node Merge(const Node &left, const Node &right)
{
    Node res;
    int tmp = min(left.o, right.c);
    res.t = left.t + right.t + tmp;
    res.o = left.o + right.o - tmp;
    res.c = left.c + right.c - tmp;
    return res;
}

void Build(int id, int left, int right)
{
    if (left == right)
    {
        if (s[left] == '(')
        {
            Seg[id] = {0, 1, 0};
        }
        else
        {
            Seg[id] = {0, 0, 1};
        }
        return;
    }
    int mid = (left + right) / 2;
    Build(id * 2, left, mid);
    Build(id * 2 + 1, mid + 1, right);
    Seg[id] = Merge(Seg[id * 2], Seg[id * 2 + 1]);
}

Node Get(int id, int left, int right, int gleft, int gright)
{
    if (left > gright || right < gleft)
    {
        return {0, 0, 0};
    }
    if (left >= gleft && right <= gright)
    {
        return Seg[id];
    }
    int mid = (left + right) / 2;
    Node resLeft = Get(id * 2, left, mid, gleft, gright);
    Node resRight = Get(id * 2 + 1, mid + 1, right, gleft, gright);
    return Merge(resLeft, resRight);
}

void Solve()
{
    int n = sz(s);
    Build(1, 0, n - 1);
    while(q --)
    {
        int left, right;
        cin >> left >> right;
        left --;
        right --;
        Node ans = Get(1, 0, n - 1, left, right);
        cout << ans.t * 2 << endl;
    }
}

int main()x
{
    fixIO();
    File("716634A");
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