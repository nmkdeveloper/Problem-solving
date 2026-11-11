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

struct Point
{
    int x, y, id;
};

int n;
vector<Point> points;

void Read()
{
    cin >> n;
    points.resize(n);
    REP(i, n)
    {
        cin >> points[i].x >> points[i].y;
        points[i].id = i;
    }
}

vi bit, vals;

bool Comparecor(const Point& A, const Point& B)
{
    if (A.x != B.x)
    {
        return A.x < B.x;
    }
    return A.y > B.y;
}

void Update(int node, int val)
{
    for(; node < sz(bit); node += node & -node)
    {
        bit[node] += val;
    }
}

int Query(int node)
{
    ll sum = 0;
    for(; node > 0; node -= node & -node)
    {
        sum += bit[node];
    }
    return sum;
}

int Gety(int y)
{
    return lower_bound(all(vals), y) - vals.begin() + 1;
}

void Solve()
{
    sort(all(points), Comparecor);
    for(const auto& p : points)
    {
        vals.pb(p.y);
    }
    sort(all(vals));
    vals.erase(unique(all(vals)), vals.end());
    int m = sz(vals);
    vi ans1(n), ans2(n);
    bit.assign(m + 1, 0);
    REPD(i, n)
    {
        int y = Gety(points[i].y);
        ans1[points[i].id] = Query(y);
        Update(y, 1);
    }
    bit.assign(m + 1, 0);
    REP(i, n)
    {
        int y = Gety(points[i].y);
        ans2[points[i].id] = i - Query(y - 1);
        Update(y, 1);
    }
    REP(i, n)
    {
        cout << ans1[i] << ' ';
    }
    cout << endl;
    REP(i, n)
    {
        cout << ans2[i] << ' ';
    }
}

int main()
{
    fixIO();
    File("2169");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
