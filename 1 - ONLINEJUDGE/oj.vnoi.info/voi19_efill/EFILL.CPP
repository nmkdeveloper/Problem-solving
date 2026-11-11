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
const long double EPS = 1e-9;

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
    long double x;
    long double y;
    int id;
};

int n;
vector<Point> points;
long double cx = 0, cy = 0;
Point a, b, c, d;

void Read()
{
    cin >> n;
    FOR(i, 1, n)
    {
        long double x, y;
        cin >> x >> y;
        Point p = {x, y, i};
        points.pb(p);
        cx += x;
        cy += y;
        if (i == 1) a = p;
        if (i == 2) b = p;
    }
    cin >> c.x >> c.y >> d.x >> d.y;
    c.id = 3;
    d.id = 4;
}

bool Compare(const Point& A, const Point& B)
{
    return atan2(A.y - cy, A.x - cx) < atan2(B.y - cy, B.x - cx);
}

long double Calcdistance(const Point& A, const Point& B)
{
    long double x = B.x - A.x;
    long double y = B.y - A.y;
    return sqrt(x * x + y * y);
}

long double Crossproduct(const Point& A, const Point& B, const Point& C)
{
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

bool Iscollinear()
{
    return abs(Crossproduct(a, b, c)) < EPS && abs(Crossproduct(a, b, d)) < EPS;
}

bool IsSquare()
{
    vector<long double> dists;
    Point p[4] = {a, b, c, d};
    REP(i, 4)
    {
        FOR(j, i + 1, 3)
        {
            dists.pb(Calcdistance(p[i], p[j]));
        }
    }
    sort(all(dists));
    return (abs(dists[0] - dists[3]) < 1e-4) && (abs(dists[4] - dists[5]) < 1e-4);
}

long double SolvePart1()
{
    cx /= n;
    cy /= n;
    if (!Iscollinear())
    {
        sort(all(points), Compare);
    }

    long double total = 0, maxedgedistance = 0;
    REP(i, n)
    {
        Point A = points[i], B = points[(i + 1) % n];
        long double curdistance = Calcdistance(A, B);
        if ((A.id == 1 && B.id == 2) || (A.id == 2 && B.id == 1))
        {
            continue;
        }
        total += curdistance;
        maxedgedistance = max(maxedgedistance, curdistance);
    }
    return total - maxedgedistance;
}

long double Part2Sub1()
{
    Point p[4] = {a, b, c, d};
    long double maxdist = 0;
    REP(i, 4)
    {
        FOR(j, i + 1, 3)
        {
            maxdist = max(maxdist, Calcdistance(p[i], p[j]));
        }
    }
    return maxdist;
}

long double Wireonline(const Point& p1, const Point& p2, const Point& p3)
{
    long double d12 = Calcdistance(p1, p2);
    long double d23 = Calcdistance(p2, p3);
    long double d13 = Calcdistance(p1, p3);
    return max({d12, d23, d13});
}

long double Costsub23(long double t, const Point& M, const Point& T)
{
    Point e;
    e.x = M.x + t * (T.x - M.x);
    e.y = M.y + t * (T.y - M.y);
    e.id = 5;
    return Wireonline(c, d, e) + Calcdistance(e, a) + Calcdistance(e, b);
}

long double Part2Sub23()
{
    Point M = {(a.x + b.x) / (long double)2.0, (a.y + b.y) / (long double)2.0, 0};
    Point T = (Calcdistance(M, c) > Calcdistance(M, d)) ? c : d;
    long double low = 0.0, high = 1.0;
    REP(iter, 80)
    {
        long double m1 = low + (high - low) / (long double)3.0;
        long double m2 = high - (high - low) / (long double)3.0;
        if (Costsub23(m1, M, T) < Costsub23(m2, M, T))
        {
            high = m2;
        }
        else
        {
            low = m1;
        }
    }
    return Costsub23(low, M, T);
}

long double Part2Sub4()
{
    Point p[4] = {a, b, c, d};
    long double s = 1e18;
    REP(i, 4)
    {
        FOR(j, i + 1, 3)
        {
            s = min(s, Calcdistance(p[i], p[j]));
        }
    }
    return s * ((long double)1.0 + sqrt((long double)3.0));
}

long double SolvePart2()
{
    if (Iscollinear())
    {
        return Part2Sub1();
    }
    if (IsSquare())
    {
        return Part2Sub4();
    }
    return Part2Sub23();
}

void Solve()
{
    long double totalpart1 = SolvePart1();
    long double totalpart2 = SolvePart2();
    cout << fixed << setprecision(2) << totalpart1 + totalpart2 << endl;
}

int main()
{
    fixIO();
    File("EFILL");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
