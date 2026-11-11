///*
//    ---------------
//          TLE
//    ---------------
//*/
//
//#include <bits/stdc++.h>
//using namespace std;
//
//using ll  = long long;
//using ull = unsigned long long;
//using vi  = vector<int>;
//using vll = vector<long long>;
//using vb  = vector<bool>;
//using pii = pair<int, int>;
//using pll = pair<ll, ll>;
//
//#define FOR(a, b, c) for (auto a = (b); a <= (c); a++)
//#define FORD(a, b, c) for (auto a = (b); a >= (c); a--)
//#define REP(i, n) for (auto i = 0; i < (n); i++)
//#define REPD(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
//#define fi first
//#define se second
//#define pb push_back
//#define eb emplace_back
//#define all(x) (x).begin(), (x).end()
//#define rall(x) (x).rbegin(), (x).rend()
//#define sz(x) (int)(x).size()
//
//const char el = '\n';
//
////mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
////
////int Randint(int minium, int maxium){
////    return uniform_int_distribution<int>(minium, maxium)(rng);
////}
////
////ll Randll(ll minium, ll maxium){
////    return uniform_int_distribution<ll>(minium, maxium)(rng);
////}
////
////int Randvectorint(const vi& a){
////    return a[Randint(0, sz(a) - 1)];
////}
////
////ll Randvectorll(const vll& a){
////    return a[Randint(0, sz(a) - 1)];
////}
//
//void Fast(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//}
//
//void File(const string& filename = ""){
//    if(fopen((filename +".INP").c_str(), "r")){
//        freopen((filename + ".INP").c_str(), "r", stdin);
//        freopen((filename + ".OUT").c_str(), "w", stdout);
//    }
//}
//
///*
//---------------------------------------------------
//        Kuhn Munkres + Greedy + Static Array
//---------------------------------------------------
//*/
//
//const int MAXN = 40005;
//int wish[MAXN][2], wishcnt[MAXN], seats[MAXN][4], seatcnt[MAXN], visited[MAXN], timer = 0, N, M;
//
//void Read(){
//    cin >> N >> M;
//    FOR(i, 1, M){
//        int u, v;
//        cin >> u >> v;
//        wish[i][0] = u;
//        wishcnt[i] = 1;
//        if (u != v){
//            wish[i][1] = v;
//            wishcnt[i] = 2;
//        }
//    }
//}
//
//bool DFS(int u){
//    REP(i, wishcnt[u]){
//        int r = wish[u][i];
//        if(visited[r] == timer) continue;
//        visited[r] = timer;
//        if(seatcnt[r] < 4){
//            seats[r][seatcnt[r]++] = u;
//            return true;
//        }
//        REP(k, 4){
//            if(DFS(seats[r][k])){
//                seats[r][k] = u;
//                return true;
//            }
//        }
//    }
//    return false;
//}
//
//void Solve(){
//    int ans = 0;
//    static bool matched[MAXN]; // == memset(matched, 0, sizeof(mached));
//    FOR(i, 1, M){
//        REP(cur, wishcnt[i]){
//            int r = wish[i][cur];
//            if(seatcnt[r] < 4){
//                seats[r][seatcnt[r]++] = i;
//                matched[i] = true;
//                ans ++;
//                break;
//            }
//        }
//    }
//    FOR(i, 1, M){
//        if(matched[i]) continue;
//        timer ++;
//        if(DFS(i)) ans ++;
//    }
//    cout << ans;
//}
//
//signed main(){
//    Fast();
//    File("AIRPLANE");
//    Read();
//    Solve();
//    return 0;
//}
//
///*
//    ---------------------------------------------------
//               Code By github/toiyeuyuriiiii
//                   I Love You My Girl <3
//    ---------------------------------------------------
//*/
//
///*
//    ---------------
//          TLE
//    ---------------
//*/
//
//#include <bits/stdc++.h>
//using namespace std;
//
//using ll  = long long;
//using ull = unsigned long long;
//using vi  = vector<int>;
//using vll = vector<long long>;
//using vb  = vector<bool>;
//using pii = pair<int, int>;
//using pll = pair<ll, ll>;
//
//#define FOR(a, b, c) for (auto a = (b); a <= (c); a++)
//#define FORD(a, b, c) for (auto a = (b); a >= (c); a--)
//#define REP(i, n) for (auto i = 0; i < (n); i++)
//#define REPD(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
//#define fi first
//#define se second
//#define pb push_back
//#define eb emplace_back
//#define all(x) (x).begin(), (x).end()
//#define rall(x) (x).rbegin(), (x).rend()
//#define sz(x) (int)(x).size()
//
//const char el = '\n';
//
////mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
////
////int Randint(int minium, int maxium){
////    return uniform_int_distribution<int>(minium, maxium)(rng);
////}
////
////ll Randll(ll minium, ll maxium){
////    return uniform_int_distribution<ll>(minium, maxium)(rng);
////}
////
////int Randvectorint(const vi& a){
////    return a[Randint(0, sz(a) - 1)];
////}
////
////ll Randvectorll(const vll& a){
////    return a[Randint(0, sz(a) - 1)];
////}
//
//void Fast(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//}
//
//void File(const string& filename = ""){
//    if(fopen((filename +".INP").c_str(), "r")){
//        freopen((filename + ".INP").c_str(), "r", stdin);
//        freopen((filename + ".OUT").c_str(), "w", stdout);
//    }
//}
//
///*
//---------------------------------------------------
//                    Maximum Flow
//---------------------------------------------------
//*/
//
//const int MAXN = 80010;
//
//struct Edge{
//    int v;
//    int cap;
//    int flow;
//    int rev;
//};
//
//vector<vector<Edge>> adj;
//int level[MAXN];
//
//void Add(int u, int v, int cap){
//    adj[u].pb({v, cap, 0, sz(adj[v])});
//    adj[v].pb({u, 0, 0, sz(adj[u]) - 1});
//}
//
//bool BFS(int s, int t){
//    memset(level, -1, sizeof(level));
//    level[s] = 0;
//    queue<int> q;
//    q.push(s);
//    while(sz(q)){
//        int u = q.front();
//        q.pop();
//        for (auto& e : adj[u]){
//            if (e.cap - e.flow > 0 && level[e.v] == -1){
//                level[e.v] = level[u] + 1;
//                q.push(e.v);
//            }
//        }
//    }
//    return level[t] != -1;
//}
//
//int ptr[80010];
//
//int DFS(int u, int t, int pushed){
//    if (pushed == 0 || u == t) return pushed;
//    for (int& cid = ptr[u]; cid < sz(adj[u]); cid ++){
//        auto &e = adj[u][cid];
//        int tr = e.v;
//        if (level[u] + 1 != level[tr] || e.cap - e.flow == 0) continue;
//        int trpushed = DFS(tr, t, min(pushed, e.cap - e.flow));
//        if (trpushed == 0) continue;
//        e.flow += trpushed;
//        adj[tr][e.rev].flow -= trpushed;
//        return trpushed;
//    }
//    return 0;
//}
//
//int Dinic(int s, int t){
//    int flow = 0;
//    while (BFS(s, t)){
//        memset(ptr, 0, sizeof(ptr));
//        while (int pushed = DFS(s, t, 1e9)){
//            flow += pushed;
//        }
//    }
//    return flow;
//}
//
//int N, M;
//
//void Read(){
//    cin >> N >> M;
//    int total = M + N + 2;
//    adj.resize(total + 1);
//    int s = 0, t = M + N + 1;
//    FOR(i, 1, M){
//        Add(s, i, 1);
//    }
//    FOR(i, 1, M){
//        int u, v;
//        cin >> u >> v;
//        Add(i, M + u, 1);
//        if (u != v) Add(i, M + v, 1);
//    }
//    FOR(j, 1, N) Add(M + j, t, 4);
//}
//
//void Solve(){
//    int s = 0, t = M + N + 1;
//    cout << Dinic(s, t);
//}
//
//signed main(){
//    Fast();
//    File("AIRPLANE");
//    Read();
//    Solve();
//    return 0;
//}
//
///*
//    ---------------------------------------------------
//               Code By github/toiyeuyuriiiii
//                   I Love You My Girl <3
//    ---------------------------------------------------
//*/
//
///*
//    --------------
//          WA
//    --------------
//*/
//
//#include <bits/stdc++.h>
//using namespace std;
//
//using ll  = long long;
//using ull = unsigned long long;
//using vi  = vector<int>;
//using vll = vector<long long>;
//using vb  = vector<bool>;
//using pii = pair<int, int>;
//using pll = pair<ll, ll>;
//
//#define FOR(a, b, c) for (auto a = (b); a <= (c); a++)
//#define FORD(a, b, c) for (auto a = (b); a >= (c); a--)
//#define REP(i, n) for (auto i = 0; i < (n); i++)
//#define REPD(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
//#define fi first
//#define se second
//#define pb push_back
//#define eb emplace_back
//#define all(x) (x).begin(), (x).end()
//#define rall(x) (x).rbegin(), (x).rend()
//#define sz(x) (int)(x).size()
//
//const char el = '\n';
//
////mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
////
////int Randint(int minium, int maxium){
////    return uniform_int_distribution<int>(minium, maxium)(rng);
////}
////
////ll Randll(ll minium, ll maxium){
////    return uniform_int_distribution<ll>(minium, maxium)(rng);
////}
////
////int Randvectorint(const vi& a){
////    return a[Randint(0, sz(a) - 1)];
////}
////
////ll Randvectorll(const vll& a){
////    return a[Randint(0, sz(a) - 1)];
////}
//
//void Fast(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//}
//
//void File(const string& filename = ""){
//    if(fopen((filename +".INP").c_str(), "r")){
//        freopen((filename + ".INP").c_str(), "r", stdin);
//        freopen((filename + ".OUT").c_str(), "w", stdout);
//    }
//}
//
///*
//---------------------------------------------------
//                         DSU
//---------------------------------------------------
//*/
//
//const int MAXN = 40005;
//int par[MAXN], vcnt[MAXN], ecnt[MAXN];
//
//int Find(int u){
//    return (par[u] == u ? u : par[u] = Find(par[u]));
//}
//
//void Unite(int u, int v){
//    u = Find(u);
//    v = Find(v);
//    if (u == v){
//        ecnt[u] ++;
//        return;
//    }
//    par[v] = u;
//    vcnt[u] += vcnt[v];
//    ecnt[u] += ecnt[v] + 1;
//}
//
//int N, M;
//
//void Read(){
//    cin >> N >> M;
//    FOR(i, 1, N){
//        par[i] = i;
//        vcnt[i] = 1;
//        ecnt[i] = 0;
//    }
//    FOR(i, 1, M){
//        int u, v;
//        cin >> u >> v;
//        Unite(u, v);
//    }
//}
//
//void Solve(){
//    int total = 0;
//    FOR(i, 1, N){
//        if (par[i] == i){
//            total += min(ecnt[i], 4 * vcnt[i]);
//        }
//    }
//    cout << total;
//}
//
//signed main(){
//    Fast();
//    File("AIRPLANE");
//    Read();
//    Solve();
//    return 0;
//}
//
///*
//    ---------------------------------------------------
//               Code By github/toiyeuyuriiiii
//                   I Love You My Girl <3
//    ---------------------------------------------------
//*/
//
///*
//    ---------------
//          TLE
//    ---------------
//*/
//
//#include <bits/stdc++.h>
//using namespace std;
//
//using ll  = long long;
//using ull = unsigned long long;
//using vi  = vector<int>;
//using vll = vector<long long>;
//using vb  = vector<bool>;
//using pii = pair<int, int>;
//using pll = pair<ll, ll>;
//
//#define FOR(a, b, c) for (auto a = (b); a <= (c); a++)
//#define FORD(a, b, c) for (auto a = (b); a >= (c); a--)
//#define REP(i, n) for (auto i = 0; i < (n); i++)
//#define REPD(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
//#define fi first
//#define se second
//#define pb push_back
//#define eb emplace_back
//#define all(x) (x).begin(), (x).end()
//#define rall(x) (x).rbegin(), (x).rend()
//#define sz(x) (int)(x).size()
//
//const char el = '\n';
//
////mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
////
////int Randint(int minium, int maxium){
////    return uniform_int_distribution<int>(minium, maxium)(rng);
////}
////
////ll Randll(ll minium, ll maxium){
////    return uniform_int_distribution<ll>(minium, maxium)(rng);
////}
////
////int Randvectorint(const vi& a){
////    return a[Randint(0, sz(a) - 1)];
////}
////
////ll Randvectorll(const vll& a){
////    return a[Randint(0, sz(a) - 1)];
////}
//
//void Fast(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//}
//
//void File(const string& filename = ""){
//    if(fopen((filename +".INP").c_str(), "r")){
//        freopen((filename + ".INP").c_str(), "r", stdin);
//        freopen((filename + ".OUT").c_str(), "w", stdout);
//    }
//}
//
///*
//------------------------------------------------------
//Kuhn Munkres + Greedy + Static Array + MT19937 + Lucky
//------------------------------------------------------
//*/
//
//const int MAXN = 40005;
//int wish[MAXN][2], wishcnt[MAXN], seats[MAXN][4], seatcnt[MAXN], visited[MAXN], timer = 0, N, M;
//
//void Read(){
//    cin >> N >> M;
//    mt19937 rng(1337);
//    FOR(i, 1, M){
//        int u, v;
//        cin >> u >> v;
//        if (rng() % 2 && u != v) swap(u, v);
//        wish[i][0] = u;
//        wishcnt[i] = 1;
//        if (u != v){
//            wish[i][1] = v;
//            wishcnt[i] = 2;
//        }
//    }
//}
//
//int step = 0;
//
//bool DFS(int u){
//    if (++ step > 80) return false;
//    REP(i, wishcnt[u]){
//        int r = wish[u][i];
//        if(visited[r] == timer) continue;
//        visited[r] = timer;
//        if(seatcnt[r] < 4){
//            seats[r][seatcnt[r]++] = u;
//            return true;
//        }
//        REP(k, 4){
//            if(DFS(seats[r][k])){
//                seats[r][k] = u;
//                return true;
//            }
//        }
//    }
//    return false;
//}
//
//void Solve(){
//    int ans = 0;
//    static bool matched[MAXN]; // == memset(matched, 0, sizeof(mached));
//    vector<int> p(M);
//    iota(p.begin(), p.end(), 1);
//    mt19937 rng(2026);
//    shuffle(p.begin(), p.end(), rng);
//    for (int i : p){
//        for (int cur = 0; cur < wishcnt[i]; ++cur){
//            int r = wish[i][cur];
//            if (seatcnt[r] < 4){
//                seats[r][seatcnt[r]++] = i;
//                matched[i] = true;
//                ans++;
//                break;
//            }
//        }
//    }
//    for (int i : p){
//        if (matched[i]) continue;
//        step = 0;
//        ++timer;
//        if (DFS(i)) ans++;
//    }
//    cout << ans;
//}
//
//signed main(){
//    Fast();
//    File("AIRPLANE");
//    Read();
//    Solve();
//    return 0;
//}
//
///*
//    ---------------------------------------------------
//               Code By github/toiyeuyuriiiii
//                   I Love You My Girl <3
//    ---------------------------------------------------
//*/

/*
    ---------------
           AC
    ---------------
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

void Fast(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}

void File(const string& filename = ""){
    if(fopen((filename + ".INP").c_str(), "r")){
        freopen((filename + ".INP").c_str(), "r", stdin);
        freopen((filename + ".OUT").c_str(), "w", stdout);
    }
}

/*
---------------------------------------------------------------------
  Kuhn Munkres + Greedy + Static Array + Permanent Dead-end Pruning
---------------------------------------------------------------------
*/

const int MAXN = 40005;
int wish[MAXN][2], wishcnt[MAXN], seats[MAXN][4], seatcnt[MAXN], visited[MAXN], timer = 0, hisr[MAXN], hcnt = 0;
bool dead[MAXN];
int N, M;

void Read(){
    cin >> N >> M;
    mt19937 rng(1337);
    FOR(i, 1, M){
        int u, v;
        cin >> u >> v;
        if ((rng() & 1) && u != v) swap(u, v);
        wish[i][0] = u;
        wishcnt[i] = 1;
        if (u != v){
            wish[i][1] = v;
            wishcnt[i] = 2;
        }
    }
}

bool DFS(int u){
    REP(i, wishcnt[u]){
        int r = wish[u][i];
        if (dead[r] || visited[r] == timer) continue;
        visited[r] = timer;
        hisr[hcnt++] = r;
        if (seatcnt[r] < 4){
            seats[r][seatcnt[r]++] = u;
            return true;
        }
        REP(k, 4){
            if (DFS(seats[r][k])){
                seats[r][k] = u;
                return true;
            }
        }
    }
    return false;
}

void Solve(){
    int ans = 0;
    static bool matched[MAXN];
    vector<int> p(M);
    iota(p.begin(), p.end(), 1);
    mt19937 rng(2026);
    shuffle(p.begin(), p.end(), rng);
    for (int i : p){
        for (int cur = 0; cur < wishcnt[i]; ++cur){
            int r = wish[i][cur];
            if (seatcnt[r] < 4){
                seats[r][seatcnt[r]++] = i;
                matched[i] = true;
                ans++;
                break;
            }
        }
    }
    for (int i : p){
        if (matched[i]) continue;
        ++ timer;
        hcnt = 0;
        if (DFS(i)){
            ans++;
        } else {
            REP(j, hcnt){
                dead[hisr[j]] = true;
            }
        }
    }
    cout << ans;
}

signed main(){
    Fast();
    File("AIRPLANE");
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
