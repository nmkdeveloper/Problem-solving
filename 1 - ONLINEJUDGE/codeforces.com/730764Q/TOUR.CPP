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

int N, K;
vi a;

void Read(){
    cin >> N >> K;
    a.resize(N);
    REP(i, N) cin >> a[i];
}

int memo[1005][25];

int Backtrack(int pos, int g){
    if (pos >= N) return ((g == K) ? 0 : 1e9);
    if (g >= K || (N - pos) < (K - g)) return 1e9;
    if (memo[pos][g] != -1) return memo[pos][g];
    int res = 1e9;
    int cost = 0;
    FOR(j, pos, N - 1){
        FOR(i, pos, j - 1) if (a[i] > a[j]) cost ++;
        res = min(res, cost + Backtrack(j + 1, g + 1));
    }
    return memo[pos][g] = res;
}

void Solve(){
    memset(memo, -1, sizeof(memo));
    cout << Backtrack(0, 0);
}

signed main(){
    Fast();
    File("TOUR");
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
