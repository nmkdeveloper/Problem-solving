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

#define BIT(n) (1LL << (n))
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

int m, n;
vector<string> maze;

void Read()
{
    cin >> m >> n;
    maze.resize(m);
    REP(i, m)
    {
        cin >> maze[i];
    }
}

int cells;
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

struct State
{
    int sx, sy;
    int bx, by;
};

struct Node
{
    int push;
    int step;
    ll id;
    State s;
    bool operator < (const Node &other) const
    {
        if (push != other.push)
        {
            return push > other.push;
        }
        return step > other.step;
    }
};

bool Issafe(int x, int y)
{
    return x >= 0 && x < m && y >= 0 && y < n;
}

bool Isfree(int x, int y)
{
    return Issafe(x, y) && maze[x][y] != '#';
}

ll Makeid(int ux, int uy, int bx, int by)
{
    return 1LL * (ux * n + uy) * cells + (bx * n + by);
}

void Solve()
{
    int sx, sy, bx, by, tx, ty;
    REP(i, m)
    {
        REP(j, n)
        {
            if (maze[i][j] == 'S')
            {
                sx = i;
                sy = j;
            }
            if (maze[i][j] == 'B')
            {
                bx = i;
                by = j;
            }
            if (maze[i][j] == 'T')
            {
                tx = i;
                ty = j;
            }
        }
    }
    cells = n * m;
    ll total = 1LL * cells * cells;
    vll distp(total, INF);
    vll dists(total, INF);
    priority_queue<Node> pq;
    ll start = Makeid(sx, sy, bx, by);
    distp[start] = 0;
    dists[start] = 0;
    pq.push({0, 0, start, {sx, sy, bx, by}});
    while(sz(pq))
    {
        Node top = pq.top();
        pq.pop();
        int curp = top.push;
        int curs = top.step;
        State curst = top.s;
        ll curid = top.id;
        if (curp > distp[curid])
        {
            continue;
        }
        if (curp == distp[curid] && curs > dists[curid])
        {
            continue;
        }
        if (curst.bx == tx && curst.by == ty)
        {
            cout << curp << ' ' << curs;
            return;
        }
        REP(i, 4)
        {
            int nx = curst.sx + dx[i], ny = curst.sy + dy[i];
            if (!Isfree(nx, ny))
            {
                continue;
            }
            int nhx = curst.bx, nhy = curst.by, np = curp, ns = curs + 1;
            if (nx == curst.bx && ny == curst.by) //stay in box
            {
                nhx = curst.bx + dx[i];
                nhy = curst.by + dy[i];
                if (!Isfree(nhx, nhy))
                {
                    continue;
                }
                np ++;
            }
            ll nid = Makeid(nx, ny, nhx, nhy);
            bool isbetter = (np < distp[nid]) || (np == distp[nid] && ns < dists[nid]);
            if (isbetter)
            {
                distp[nid] = np;
                dists[nid] = ns;
                pq.push({np, ns, nid, {nx, ny, nhx, nhy}});
            }
        }
    }
    cout << "Impossible.";
}

int main()
{
    fixIO();
    File("g_pushing");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
