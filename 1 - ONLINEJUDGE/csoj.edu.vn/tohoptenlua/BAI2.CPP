#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef map<int, int> mii;

#define FOR(a, b, c) for(int a = (b); a <= (c); a++)
#define REV(a, b, c) for(int a = (b); a >= (c); a--)
#define endl '\n'
#define fi first
#define se second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()

void fixIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}

void File(const string &fileName = "")
{
    if(fopen((fileName + ".INP").c_str(), "r"))
    {
        freopen((fileName + ".INP").c_str(), "r", stdin);
        freopen((fileName + ".OUT").c_str(), "w", stdout);
    }
}

int N;
ll P;
vector<pli> a;

void Read()
{
    cin >> N >> P;
    FOR(i, 0, N - 1)
    {
        ll x;
        cin >> x;
        a.pb({x, i + 1});
    }
}

void Solve()
{
    priority_queue<int, vi, greater<int>> pq;
    multiset<pli> st(all(a));

    FOR(i, 0, N - 1)
    {
        pli cur = a[i];
        ll sum = cur.fi;
        multiset<pli> cura = st;
        cura.erase(cura.find(cur));

        while (sum < P && !cura.empty())
        {
            ll target = P - sum;
            auto it = cura.lower_bound({target, -1});
            auto best_it = cura.end();

            if (it == cura.end())
            {
                best_it = prev(cura.end());
            }
            else if (it == cura.begin())
            {
                best_it = it;
            }
            else
            {
                auto prev_it = prev(it);
                if (llabs(target - it->fi) < llabs(target - prev_it->fi))
                    best_it = it;
                else
                    best_it = prev_it;
            }

            if (best_it != cura.end())
            {
                sum += best_it->fi;
                cura.erase(best_it);
            }
        }
        if (sum - cur.fi < P)
        {
            pq.push(cur.se);
        }
    }
    while(!pq.empty())
    {
        cout << pq.top() << ' ';
        pq.pop();
    }
}

int main() 
{
    fixIO();
    File("BAI2");
    Read();
    Solve();
    return 0;
}