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

struct Boxinfo{
    int a, b, c;
    bool operator <(const Boxinfo& other) const{
        if (this->a != other.a) return this->a < other.a;
        if (this->b != other.b) return this->b < other.b;
        return this->c < other.c;
    }
};

int N;
vector<Boxinfo> box;

void Read(){
    cin >> N;
    REP(i, N){
        int a, b, c;
        cin >> a >> b >> c;
        box.pb({a, b, c});
    }
}

const int MOD = (int) 1e9 + 7;

void Solve(){
    sort(all(box));
    ll dp[N];
    ll way[N];
    fill(dp, dp + N, 1);
    fill(way, way + N, 1);
    REP(i, N) REP(j, i){
        if (box[j].a < box[i].a && box[j].b < box[i].b && box[j].c < box[i].c){
            if (dp[j] + 1 > dp[i]){
                dp[i] = dp[j] + 1;
                way[i] = way[j];
            }
            else if (dp[j] + 1 == dp[i]) way[i] = (way[i] + way[j]) % MOD;
        }
    }
    ll maxl = 0;
    ll totalc = 0;
    REP(i, N){
        if (dp[i] > maxl) maxl = dp[i], totalc = way[i];
        else if (dp[i] == maxl) totalc = (totalc + way[i]) % MOD;
    }
    cout << maxl << ' ' << totalc;
}

signed main(){
    Fast();
    File("BOX");
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
