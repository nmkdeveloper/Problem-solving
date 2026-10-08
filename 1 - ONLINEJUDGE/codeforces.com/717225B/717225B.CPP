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

int N, K, V;
vector<vector<int>> g;
vector<vector<bool>> derby;

void ReadData()
{
    cin >> N >> K;
    V = 2 * N;
    derby.assign(V, vector<bool>(V, false));
    g.assign(V, {});
    for (int i = 0; i < K; i++)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        derby[u][v] = derby[v][u] = true;
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

vector<int> max_matching(int n, const vector<vector<int>> &g)
{
    vector<int> match(n, -1);
    vector<int> p(n), base(n);
    vector<bool> used(n), blossom(n);
    queue<int> q;
    auto lca = [&](int a, int b)
    {
        vector<bool> used_lca(n, false);
        while (true)
        {
            a = base[a];
            used_lca[a] = true;
            if (match[a] == -1)
                break;
            a = p[match[a]];
        }
        while (true)
        {
            b = base[b];
            if (used_lca[b])
                return b;
            b = p[match[b]];
        }
    };
    auto mark_path = [&](int v, int b, int children)
    {
        while (base[v] != b)
        {
            blossom[base[v]] = blossom[base[match[v]]] = true;
            p[v] = children;
            children = match[v];
            v = p[match[v]];
        }
    };
    auto find_path = [&](int root)
    {
        used.assign(n, false);
        p.assign(n, -1);
        for (int i = 0; i < n; i++)
            base[i] = i;
        while (!q.empty())
            q.pop();
        q.push(root);
        used[root] = true;
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            for (int to : g[v])
            {
                if (base[v] == base[to] || match[v] == to)
                    continue;
                if (to == root || (match[to] != -1 && p[match[to]] != -1))
                {
                    int curbase = lca(v, to);
                    blossom.assign(n, false);
                    mark_path(v, curbase, to);
                    mark_path(to, curbase, v);
                    for (int i = 0; i < n; i++)
                    {
                        if (blossom[base[i]])
                        {
                            base[i] = curbase;
                            if (!used[i])
                            {
                                used[i] = true;
                                q.push(i);
                            }
                        }
                    }
                }
                else if (p[to] == -1)
                {
                    p[to] = v;
                    if (match[to] == -1)
                    {
                        return to;
                    }
                    else
                    {
                        used[match[to]] = true;
                        q.push(match[to]);
                    }
                }
            }
        }
        return -1;
    };
    for (int i = 0; i < n; i++)
    {
        if (match[i] == -1)
        {
            int v = find_path(i);
            while (v != -1)
            {
                int pv = p[v];
                int ppv = match[pv];
                match[v] = pv;
                match[pv] = v;
                v = ppv;
            }
        }
    }
    return match;
}

int P;
vector<int> matchF, pi, inv;

void Solve()
{
    vector<int> matchM = max_matching(V, g);
    matchF = matchM;
    vector<int> unmatched;
    for (int i = 0; i < V; i++)
    {
        if (matchF[i] == -1)
            unmatched.push_back(i);
    }
    for (int i = 0; i < (int)unmatched.size(); i += 2)
    {
        int a = unmatched[i], b = unmatched[i + 1];
        matchF[a] = b;
        matchF[b] = a;
    }
    P = 0;
    for (int i = 0; i < V; i++)
    {
        if (i < matchF[i] && derby[i][matchF[i]])
            P++;
    }
    vector<pair<int, int>> stdEdges;
    stdEdges.push_back({V - 1, 0});
    for (int i = 1; i < N; i++)
    {
        stdEdges.push_back({i, V - 1 - i});
    }
    pi.assign(V, -1);
    inv.assign(V, -1);
    int idx = 0;
    for (int i = 0; i < V; i++)
    {
        if (i < matchF[i])
        {
            int a = i, b = matchF[i];
            int x = stdEdges[idx].first;
            int y = stdEdges[idx].second;
            pi[a] = x;
            pi[b] = y;
            inv[x] = a;
            inv[y] = b;
            idx++;
        }
    }
    cout << "YES\n"
         << P << "\n";
    int m = V - 1;
    int special = V - 1;
    for (int r = m - 1; r >= 0; r--)
    {
        cout << inv[special] + 1 << " " << inv[r] + 1 << "\n";
        for (int i = 1; i < N; i++)
        {
            int a = (r + i) % m;
            int b = (r - i) % m;
            if (b < 0)
                b += m;
            cout << inv[a] + 1 << " " << inv[b] + 1 << "\n";
        }
    }
}

int main()
{
    fixIO();
    File("717225B");
    ReadData();
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
