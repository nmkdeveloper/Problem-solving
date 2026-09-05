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

const int MAXARR = 1e7 + 15;
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

int n, m;
vector<vi> adj;

void Read()
{
    cin >> n >> m;
    adj.resize(n + 1);
    REP(i, m)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
    }
}

vi tin, low;
vb in_stack;
stack<int> st;
int timer = 0;
vector<vi> scc_list;

void DFS(int u)
{
    tin[u] = low[u] = ++timer;
    st.push(u);
    in_stack[u] = true;
    for (int v : adj[u])
    {
        if (!tin[v])
        {
            DFS(v);
            low[u] = min(low[u], low[v]);
        }
        else if (in_stack[v])
        {
            low[u] = min(low[u], tin[v]);
        }
    }
    if (low[u] == tin[u])
    {
        vi cur_scc;
        while (true)
        {
            int v = st.top();
            st.pop();
            in_stack[v] = false;
            cur_scc.pb(v);
            if (v == u)
            {
                break;
            }
        }
        scc_list.pb(cur_scc);
    }
}

void Solve()
{
    tin.assign(n + 1, 0);
    low.assign(n + 1, 0);
    in_stack.assign(n + 1, false);
    timer = 0;
    scc_list.clear();
    FOR(i, 1, n)
    {
        if (!tin[i])
        {
            DFS(i);
        }
    }
    cout << "So luong SCC: " << sz(scc_list) << endl;
    for (auto &scc : scc_list)
    {
        for (int x : scc)
        {
            cout << x << " ";
        }
        cout << endl;
    }
}

int main()
{
    fixIO();
    File("5h6VKi9N");
    Read();
    Solve();
    return 0;
}

/**
 *  "Frieren: Vay theo cau chung ta phai lam gi de nguoi khac nho den chung ta chu?
 *   Himmel:  Cung khong co gi to tac, do la hay thay doi cuoc doi cua ai do
 *             du chi mot chut. Toi thay chi can nhu vay la du roi."
 *
 *                                                   - Sousou no Frieren -
 *  =======================================================================
 *  Template by : Nguyen Minh Khoi (github/nmkdeveloper)
 *  Created     : 2026.08.11
 */
