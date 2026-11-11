#include <bits/stdc++.h>
using namespace std;
#define oo 1000000007

int a[100001], n, k, x, ans[100001], N, pos[100001];
long long req[100001][4];

vector<int> tinhmid(const vector<int>& a, const vector<int>& b, int coso) {
    vector<int> c(N + 1, 0);
    int nhocong = 0;
    for (int i = N; i >= 0; --i) {
        int sum = a[i] + b[i] + nhocong;
        c[i] = sum % coso;
        nhocong = sum / coso;
    }

    vector<int> res(N + 1, 0);
    int nho = 0;
    for (int i = 0; i <= N; ++i) {
        int cur = nho * coso + c[i];
        res[i] = cur / 2;
        nho = cur % 2;
    }
    return res;
}

vector<int> cong(vector<int> a, int coso) {
    ++a[N];
    for (int i = N - 1; i >= 0; --i) {
        if (a[i + 1] >= coso) {
            ++a[i];
            a[i + 1] = 0;
        } else break;
    }
    return a;
}

vector<int> tru(vector<int> a, int coso) {
    --a[N];
    for (int i = N - 1; i >= 0; --i) {
        if (a[i + 1] < 0) {
            --a[i];
            a[i + 1] = coso - 1;
        } else break;
    }
    return a;
}

bool lowcompare(const vector<int>& a, const vector<int>& b) {
    for (int i = 0; i <= N; ++i) {
        if (a[i] > b[i]) return false;
        if (a[i] < b[i]) return true;
    }
    return true;
}

bool check(const vector<int>& t) {
    for (int j = 1; j <= k; ++j) {
        long long tot = 0;
        for (int v = req[j][1]; v <= req[j][2]; ++v) {
            if (a[v] == -oo) {
                tot += 1LL * (t[pos[v]] - x) * v;
            } else {
                tot += 1LL * a[v] * v;
            }
        }
        if (tot < req[j][3]) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

     freopen("ONTHI.INP", "r", stdin);
     freopen("ONTHI.OUT", "w", stdout);

    if (!(cin >> n >> k >> x)) return 0;

    int cntban = 0, cntcham = 0;
    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        if (s == "*") {
            a[i] = -oo;
            ++cntcham;
            pos[i] = cntcham;
        } else if (s[0] == '-') {
            ++cntban;
            int res = 0;
            for (int j = 1; j < (int)s.size(); ++j) res = res * 10 + (s[j] - '0');
            a[i] = -res;
        } else {
            ++cntban;
            int res = 0;
            for (int j = 0; j < (int)s.size(); ++j) res = res * 10 + (s[j] - '0');
            a[i] = res;
        }
    }

    for (int i = 1; i <= k; ++i) {
        cin >> req[i][1] >> req[i][2] >> req[i][3];
    }

    N = n - cntban;
    int coso = 2 * x + 1;

    vector<int> l(N + 1, 0), h(N + 1, 2 * x), ans_vec;
    h[0] = 0;

    while (lowcompare(l, h)) {
        vector<int> mid = tinhmid(l, h, coso);
        if (check(mid)) {
            ans_vec = mid;
            h = tru(mid, coso);
        } else {
            l = cong(mid, coso);
        }
    }

    if (!ans_vec.empty()) {
        for (int i = 1; i <= n; ++i) {
            if (a[i] != -oo) cout << a[i] << ' ';
            else cout << ans_vec[pos[i]] - x << ' ';
        }
        cout << '\n';
    } else {
        cout << "Impossible\n";
    }

    return 0;
}
