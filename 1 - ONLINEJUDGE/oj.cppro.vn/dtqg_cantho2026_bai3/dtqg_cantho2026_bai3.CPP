#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

#define FOR(a, b, c) for (int a = (b); a <= (c); a++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define endl '\n'
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()

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
vpii Edge;
vi Parent, Size;

int findRoot(int u)
{
    if (Parent[u] == u) return u;
    return Parent[u] = findRoot(Parent[u]);
}

void DSU(int u, int v)
{
    int root_u = findRoot(u);
    int root_v = findRoot(v);
    if (root_u == root_v) return;
    if (Size[root_u] < Size[root_v]) swap(root_u, root_v);
    Parent[root_v] = root_u;
    Size[root_u] += Size[root_v];
}

void Read()
{
    cin >> n >> m;
    REP(i, m)
    {
        int u, v;
        cin >> u >> v;
        Edge.pb({u, v});
    }
}

void Solve()
{
    // Bước 1: Tính số thành phần liên thông gốc
    Parent.assign(n + 1, 0); iota(all(Parent), 0);
    Size.assign(n + 1, 1);
    REP(j, m) DSU(Edge[j].fi, Edge[j].se);

    int baseComponents = 0;
    FOR(u, 1, n) if (findRoot(u) == u) baseComponents++;

    // Bước 2: Dùng DSU tìm tất cả các cạnh cầu
    vector<vi> bridgeAdj(n + 1);
    REP(i, m)
    {
        Parent.assign(n + 1, 0); iota(all(Parent), 0);
        Size.assign(n + 1, 1);

        REP(j, m)
        {
            if (i == j) continue; // Thử xóa cạnh thứ i
            DSU(Edge[j].fi, Edge[j].se);
        }

        int currentComponents = 0;
        FOR(u, 1, n) if (findRoot(u) == u) currentComponents++;
        if (currentComponents > baseComponents)
        {
            bridgeAdj[Edge[i].fi].pb(Edge[i].se);
            bridgeAdj[Edge[i].se].pb(Edge[i].fi);
        }
    }
    int maxBridges = 0;
    FOR(start, 1, n)
    {
        vi dist(n + 1, -1);
        queue<int> q;
        q.push(start);
        dist[start] = 0;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            maxBridges = max(maxBridges, dist[u]);

            for (int v : bridgeAdj[u])
            {
                if (dist[v] == -1)
                {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
    }

    cout << maxBridges;
}

int main()
{
    fixIO();
    File("dtqg_cantho2026_bai3");
    Read();
    Solve();
    return 0;
}
