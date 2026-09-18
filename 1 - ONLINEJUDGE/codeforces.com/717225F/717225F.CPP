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

int n;
ll k;
vector<vector<pil>> adj;

void Read()
{
    cin >> n >> k;
    adj.resize(n + 1);
    REP(i, n - 1)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
}

vi siz, parent;
vb removed;
ll ans = 0;

ll count_pairs(vll &a)
{
    sort(all(a));
    ll res = 0;
    int l = 0, r = sz(a) - 1;
    while(l < r)
    {
        if (a[l] + a[r] <= k)
        {
            res += (r - l);
            l ++;
        }
        else
        {
            r --;
        }
    }
    return res;
}

void calc_size(int s, vi& order)
{
    stack<int> st;
    st.push(s);
    parent[s] = 0;
    while(sz(st))
    {
        int u = st.top();
        st.pop();
        order.pb(u);
        for (auto [v, w] : adj[u])
        {
            if (v == parent[u] || removed[v])
            {
                continue;
            }
            parent[v] = u;
            st.push(v);
        }
    }
    FORD(i, sz(order) - 1, 0)
    {
        int u = order[i];
        siz[u] = 1;
        for (auto [v, w] : adj[u])
        {
            if (v == parent[u] || removed[v])
            {
                continue;
            }
            siz[u] += siz[v];
        }
    }
}

int findCentroid(int s)
{
    vi order;
    calc_size(s, order);
    int total = siz[s];
    for (auto u : order)
    {
        int mx = total - siz[u];
        for (auto [v, w] : adj[u])
        {
            if (v == parent[u] || removed[v])
            {
                continue;
            }
            mx = max(mx, siz[v]);
        }
        if (mx <= total / 2)
        {
            return u;
        }
    }
    return s;
}

void Decompose(int s)
{
    int c = findCentroid(s);
    vll all;
    all.pb(0);
    for (auto [v, w] : adj[c])
    {
        if (removed[v])
        {
            continue;
        }
        vll vec;
        stack<tuple<int, int, ll>> st;
        st.push({v, c, w});
        while(sz(st))
        {
            auto [u, p, d] = st.top();
            st.pop();
            vec.pb(d);
            for (auto [to, ww] : adj[u])
            {
                if (to == p || removed[to])
                {
                    continue;
                }
                st.push({to, u, ww + d});
            }
        }
        ans -= count_pairs(vec);
        all.insert(all.end(), all(vec));
    }
    ans += count_pairs(all);
    removed[c] = true;
    for (auto [v, w] : adj[c])
    {
        if (!removed[v])
        {
            Decompose(v);
        }
    }
}

void Solve()
{
    siz.resize(n + 1, 0);
    parent.resize(n + 1, 0);
    removed.resize(n + 1, false);
    Decompose(1);
    cout << ans;
}

int main()
{
    fixIO();
    File("717225F");
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
