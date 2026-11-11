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

const int MAXN = 3e5 + 7;
int n, m;
int a[MAXN], b[MAXN];
ll pref[MAXN];
bool isaequal = true;
bool isbzero = true;

void Read()
{
    cin >> n >> m;
    pref[0] = 0;
    FOR(i, 1, n)
    {
        cin >> a[i];
        if (i < n && a[i] != a[i + 1])
        {
            isaequal = false;
        }
    }
    FOR(i, 1, n)
    {
        cin >> b[i];
        pref[i] = 1LL * pref[i - 1] + b[i];
        if (b[i] != 0)
        {
            isbzero = false;
        }
    }
}

namespace AEQUAL
{
    struct Node
    {
        ll sum;
        ll pref;
        ll suff;
        ll maxsub;
        Node ()
        {
            sum = 0;
            pref = suff = maxsub = -INF64;
        }
        Node (ll val)
        {
            sum = val;
            pref = suff = maxsub = val;
        }
    };
    vector<Node> tree;
    Node Merge(Node A, Node B)
    {
        if (A.maxsub == -INF64)
        {
            return B;
        }
        if (B.maxsub == -INF64)
        {
            return A;
        }
        Node Par;
        Par.sum = A.sum + B.sum;
        Par.pref = max(A.pref, A.sum + B.pref);
        Par.suff = max(B.suff, B.sum + A.suff);
        Par.maxsub = max({A.maxsub, A.maxsub, A.suff + B.suff});
        return Par;
    }
    void Build(int node, int left, int right)
    {
        if (left == right)
        {
            tree[node] = Node(b[left]);
            return;
        }
        int mid = (left + right) / 2;
        Build(node * 2, left, mid);
        Build(node * 2 + 1, mid + 1, right);
        tree[node] = Merge(tree[2 * node], tree[2 * node + 1]);
    }
    Node Query(int node, int left, int right, int qleft, int qright)
    {
        if (qright < left || right < qleft)
        {
            return Node();
        }
        if (qleft <= left && right <= qright)
        {
            return tree[node];
        }
        int mid = (left + right) / 2;
        return Merge(Query(2 * node, left, mid, qleft, qright), Query(2 * node + 1, mid + 1, right, qleft, qright));
    }
    void Solve()
    {
        tree.resize(4 * MAXN);
        Build(1, 1, n);
        while(m --)
        {
            int left, right;
            cin >> left >> right;
            cout << Query(1, 1, n, left, right).maxsub + a[left] << endl;
        }
        exit(0);
    }
}

namespace BZERO
{
    struct Node
    {
        ll maxsub;
        Node ()
        {
            maxsub = -1;
        }
        Node (ll val)
        {
            maxsub = val;
        }
    };
    vector<Node> tree;
    Node Merge(Node A, Node B)
    {
        if (A.maxsub == -1)
        {
            return B;
        }
        if (B.maxsub == -1)
        {
            return A;
        }
        Node Par;
        Par.maxsub = max(A.maxsub, B.maxsub);
        return Par;
    }
    void Build(int node, int left, int right)
    {
        if (left == right)
        {
            tree[node] = Node(a[left]);
            return;
        }
        int mid = (left + right) / 2;
        Build(node * 2, left, mid);
        Build(node * 2 + 1, mid + 1, right);
        tree[node] = Merge(tree[2 * node], tree[2 * node + 1]);
    }
    Node Query(int node, int left, int right, int qleft, int qright)
    {
        if (qright < left || right < qleft)
        {
            return Node();
        }
        if (qleft <= left && right <= qright)
        {
            return tree[node];
        }
        int mid = (left + right) / 2;
        return Merge(Query(2 * node, left, mid, qleft, qright), Query(2 * node + 1, mid + 1, right, qleft, qright));
    }
    void Solve()
    {
        tree.resize(4 * MAXN);
        Build(1, 1, n);
        while(m --)
        {
            int left, right;
            cin >> left >> right;
            cout << Query(1, 1, n, left, right).maxsub << endl;
        }
        exit(0);
    }
}

namespace BRUTEFORCE
{
    void Solve()
    {
        while(m --)
        {
            int left, right;
            cin >> left >> right;
            ll ans = -INF64;
            FOR(i, left, right)
            {
                ll curand = a[i];
                ll cursum = b[i];
                ans = max(ans, curand + cursum);
                FOR(j, i + 1, right)
                {
                    curand &= a[j];
                    cursum += b[j];
                    ans = max(ans, curand + cursum);
                }
            }
            cout << ans << endl;
        }
        exit(0);
    }
}

void Solve()
{
    if (isaequal)
    {
        AEQUAL::Solve();
    }
    if (isbzero)
    {
        BZERO::Solve();
    }
    BRUTEFORCE::Solve();
}

int main()
{
    fixIO();
    File("SAND");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * I didn't fall in love with you. I walked into love with you, with my eyes wide open, choosing to take every step along the way <3.
 */
