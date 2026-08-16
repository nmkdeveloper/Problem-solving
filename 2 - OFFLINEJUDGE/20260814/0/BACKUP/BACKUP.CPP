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

struct Edge
{
    int v;
    ll w;
};

struct Node{
    int u;
    ll Dist_U;
};
struct cmp
{
    bool operator() (Node a, Node b)
    {
        return a.Dist_U > b.Dist_U;
    }
};


int N, Q;
vector<vector<Edge>> adj;

void Read()
{
    cin >> N >> Q;
    adj.resize(N + 1);
    FOR(i, 1, N - 1)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
}

ll Dijkstra(int s, int t, const vb& visited)
{
    if (visited[s] || visited[t])
    {
        return -1;
    }
    if (s == t)
    {
        return 0;
    }
    ll Min_weight = INF64;
    vll Dist(N + 1, INF64);
    vi Parrent(N + 1, -1);
    vll etop(N + 1, INF64);
    vb done(N + 1, false);
    Dist[s] = 0;
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({s,Dist[s]});
    while(pq.size())
    {
        Node x = pq.top();
        pq.pop();
        int u = x.u; 
        if (done[u])
        {
            continue;
        }
        done[u] = true;
        if (u == t)
        {
            break;
        }
        for (auto e : adj[u])
        {
            int v = e.v;
            ll w = e.w;
            if (visited[v] || done[v])
            {
                continue;
            }
            if (Dist[v] > Dist[u] + w)
            {
                Dist[v] = Dist[u] + w;
                pq.push({v, Dist[v]});
                Parrent[v] = u;
                etop[v] = w;
            }
        }
    }
    if (!done[t])
    {
        return -1;
    }
    int curr = t;
    while (curr != s)
    {
        Min_weight = min(Min_weight, etop[curr]);
        curr = Parrent[curr];
    }
    return Min_weight;
}

void Solve()
{
    vb Visited(N + 1, false);
    while(Q--)
    {
        int q;
        cin >> q;
        if (q == 1)
        {
            int u, v;
            cin >> u >> v;
            cout << Dijkstra(u, v, Visited) << endl;
        }
        else
        {
            int u;
            cin >> u;
            Visited[u] = true;
        }
    }
}

int main() 
{
    fixIO();
    File("BACKUP");
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