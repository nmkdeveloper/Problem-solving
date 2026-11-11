/*
    ----------------
        Accepted
    ----------------
*/
#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ull = unsigned long long;
using vi  = vector<int>;
using vll = vector<long long>;
using vb  = vector<bool>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define FOR(a, b, c) for (auto a = (b); a <= (c); a++)
#define FORD(a, b, c) for (auto a = (b); a >= (c); a--)
#define REP(i, n) for (auto i = 0; i < (n); i++)
#define REPD(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()

const char el = '\n';

//mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
//
//int Randint(int minium, int maxium){
//    return uniform_int_distribution<int>(minium, maxium)(rng);
//}
//
//ll Randll(ll minium, ll maxium){
//    return uniform_int_distribution<ll>(minium, maxium)(rng);
//}
//
//int Randvectorint(const vi& a){
//    return a[Randint(0, sz(a) - 1)];
//}
//
//ll Randvectorll(const vll& a){
//    return a[Randint(0, sz(a) - 1)];
//}

void Fast(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}

void File(const string& filename = ""){
    if(fopen((filename +".INP").c_str(), "r")){
        freopen((filename + ".INP").c_str(), "r", stdin);
        freopen((filename + ".OUT").c_str(), "w", stdout);
    }
}

/*
    --------------------------------------------------
                Multi-source Shortest Path
    --------------------------------------------------
*/

const ll INF64 = (ll) 4e18;

struct Edge{
    int v;
    ll w;
};

int N, M;
vector<vector<Edge>> adj;

void Read(){
    cin >> N >> M;
    adj.resize(N + 1);
    REP(i, M){
        int u, v;
        cin >> u >> v;
        adj[u].pb({v, 1});
        adj[v].pb({u, 1});
    }
}

void BFS(int s, vll& dist){
    dist.assign(N + 1, INF64);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while(sz(q)){
        int u = q.front(); q.pop();
        for(const auto& e : adj[u]){
            int v = e.v;
            if(dist[v] == INF64){
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

void Dijkstra(int s, vll& dist){
    dist.assign(N + 1, INF64);
    dist[s] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({0, s});
    while(sz(pq)){
        ll d = pq.top().fi;
        int u = pq.top().se;
        pq.pop();
        if (d > dist[u]) continue;
        for (auto& e : adj[u]){
            int v = e.v;
            ll w = e.w;
            if (dist[v] > d + w){
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
}

void Solve(){
    vll dist1, dist2;
    BFS(1, dist1);
    BFS(2, dist2);
    FOR(i, 1, N){
        if (dist1[i] != INF64 && dist2[i] != INF64){
            adj[0].pb({i, dist1[i] + dist2[i]});
        }
    }
    vll dist;
    Dijkstra(0, dist);
    FOR(i, 3, N){
        cout << dist[i] << ' ';
    }
}

signed main(){
    Fast();
    File("NETCORE");
    Read();
    Solve();
    return 0;
}

/*
    ---------------------------------------------------
               Code By github/toiyeuyuriiiii
                   I Love You My Girl <3
    ---------------------------------------------------
*/
