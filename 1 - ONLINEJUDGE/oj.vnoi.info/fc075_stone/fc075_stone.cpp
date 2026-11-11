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

int N, A, B;
vll W;

void Read(){
    cin >> N >> A >> B;
    W.resize(N);
    REP(i, N) cin >> W[i];
}

namespace Sub1{
    vll pref;
    bool dp[105][105];

    bool Check(ll tar){
        memset(dp, 0, sizeof(dp));
        dp[0][0] = true;
        FOR(i, 1, N) REP(j, i){
                ll sum = pref[i] - pref[j];
                if((sum | tar) == tar) FOR(k, 1, B) if(dp[j][k - 1]) dp[i][k] = true;
            }
        FOR(k, A, B) if(dp[N][k]) return true;
        return false;
    }

    void Solve(){
        pref.assign(N + 1, 0);
        REP(i, N) pref[i + 1] = pref[i] + W[i];
        ll ans = 0;
        FORD(bit, 41, 0){
            ll tar = ans | ((1LL << bit) - 1);
            if (!Check(tar)) ans |= (1LL << bit);
        }
        cout << ans;
    }

    void Init(){
        Solve();
    }
}

namespace Sub2{
    vll pref;
    int dp[2005];
    const int INF = (int)1e9;

    bool Check(ll tar){
        fill(dp, dp + N + 1, INF);
        dp[0] = 0;
        FOR(i, 1, N) REP(j, i){
            if(dp[j] == INF) continue;
            ll sum = pref[i] - pref[j];
            if ((sum | tar) == tar) dp[i] = min(dp[i], dp[j] + 1);
        }
        return dp[N] <= B;
    }

    void Solve(){
        pref.assign(N + 1, 0);
        REP(i, N) pref[i + 1] = pref[i] + W[i];
        ll ans = 0;
        FORD(bit, 41, 0){
            ll tar = ans | ((1LL << bit) - 1);
            if (!Check(tar)) ans |= (1LL << bit);
        }
        cout << ans;
    }

    void Init(){
        Solve();
    }
}

void Solve(){
    if(A == 1) Sub2::Init();
    else Sub1::Init();
}

signed main(){
    Fast();
    File();
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
