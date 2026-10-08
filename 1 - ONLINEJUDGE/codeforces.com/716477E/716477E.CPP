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

int n, m;
vector<vi> g, rg;
vi scc, order, comp_node;
vb vis;
int cntSCC = 0;

void Read()
{
    cin >> n >> m;
    g.assign(n + 1, {});
    rg.assign(n + 1, {});
    REP(i, m)
    {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        rg[b].pb(a);
    }
}

void Solve()
{
    vis.assign(n + 1, false);
    order.clear();
    order.reserve(n);

    FOR(i, 1, n)
    {
        if (vis[i]) continue;
        stack<pair<int, int>> st;
        st.push({i, 0});
        vis[i] = true;
        while (!st.empty())
        {
            int v = st.top().fi;
            int &idx = st.top().se;
            if (idx < sz(g[v]))
            {
                int u = g[v][idx++];
                if (!vis[u])
                {
                    vis[u] = true;
                    st.push({u, 0});
                }
            }
            else
            {
                order.pb(v);
                st.pop();
            }
        }
    }
    scc.assign(n + 1, -1);
    comp_node.clear();
    cntSCC = 0;

    REPD(i, n)
    {
        int v = order[i];
        if (scc[v] != -1) continue;
        stack<int> st;
        st.push(v);
        scc[v] = cntSCC;
        comp_node.pb(v);
        while (!st.empty())
        {
            int u = st.top();
            st.pop();
            for (int w : rg[u])
            {
                if (scc[w] == -1)
                {
                    scc[w] = cntSCC;
                    st.push(w);
                }
            }
        }
        ++cntSCC;
    }
    vector<vi> dag(cntSCC);
    vi indeg(cntSCC, 0), outdeg(cntSCC, 0);
    FOR(v, 1, n)
    {
        for (int u : g[v])
        {
            if (scc[v] != scc[u])
            {
                dag[scc[v]].pb(scc[u]);
                outdeg[scc[v]]++;
                indeg[scc[u]]++;
            }
        }
    }
    vi sources, sinks;
    REP(i, cntSCC)
    {
        if (indeg[i] == 0) sources.pb(i);
        if (outdeg[i] == 0) sinks.pb(i);
    }

    if (cntSCC == 1)
    {
        cout << 0 << endl;
        return;
    }
    vi topo;
    topo.reserve(cntSCC);
    vi in = indeg;
    queue<int> q;
    REP(i, cntSCC) if (in[i] == 0) q.push(i);
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        topo.pb(u);
        for (int v : dag[u])
        {
            if (--in[v] == 0) q.push(v);
        }
    }
    vi topo_idx(cntSCC);
    REP(i, cntSCC) topo_idx[topo[i]] = i;
    sort(all(sources), [&](int a, int b) {
        return topo_idx[a] < topo_idx[b];
    });
    sort(all(sinks), [&](int a, int b) {
        return topo_idx[a] < topo_idx[b];
    });
    int k = max(sz(sources), sz(sinks));
    cout << k << endl;
    REP(i, k)
    {
        int u = sinks[i % sz(sinks)];
        int v = sources[i % sz(sources)];
        cout << comp_node[u] << ' ' << comp_node[v] << endl;
    }
}

int main()
{
    fixIO();
    File("716477E");
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
