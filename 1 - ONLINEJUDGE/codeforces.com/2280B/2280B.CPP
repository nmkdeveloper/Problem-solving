#include <bits/stdc++.h>
using namespace std;

#define REP(a, b) for(int a = 0; a < (b); a ++)

int n;
vector<int> a, half;

bool Isvalid(int l, int r, int x)
{
    if (l < 0 || r >= n || l > r)
    {
        return false;
    }
    if (l < r)
    {
        int cnt = half[r - 1] - (l > 0 ? half[l - 1] : 0);
        if (cnt > 0)
        {
            return false;
        }
    }
    if (l > 0)
    {
        if ((abs(a[l - 1] - 2 * a[r]) > x))
        {
            return false;
        }
    }
    if (r < n - 1)
    {
        if (abs(2 * a[l] - a[r + 1]) > x)
        {
            return false;
        }
    }
    return true;
}

bool Check(int x)
{
    vector<int> bad;
    REP(i, n - 1)
    {
        if (abs(a[i] - a[i + 1]) > x)
        {
            bad.push_back(i);
            if (bad.size() > 2)
            {
                return false;
            }
        }
    }
    if (bad.empty())
    {
        return true;
    }
    half.assign(n, 0);
    REP(i, n - 1)
    {
        half[i] = (i > 0 ? half[i - 1] : 0) + (abs(a[i] - a[i + 1]) > x / 2);
    }
    if (bad.size() == 2)
    {
        int l = bad[0] + 1;
        int r = bad[1];
        return Isvalid(l, r, x);
    }
    int p = bad[0];
    int l = p + 1;
    for (int r = l; r < n; r ++)
    {
        if (r > l && abs(a[r - 1] - a[r]) > x / 2)
        {
            break;
        }
        if (Isvalid(l, r, x))
        {
            return true;
        }
    }
    int r = p;
    for(int lc = r; lc >= 0; lc --)
    {
        if (lc < r && abs(a[lc] - a[lc + 1]) > x / 2)
        {
            break;
        }
        if (Isvalid(lc, r, x))
        {
            return true;
        }
    }
    return false;
}

void Solve()
{
    cin >> n;
    a.resize(n);
    REP(i, n)
    {
        cin >> a[i];
    }
    int low = 0, high = 2e6, ans = high;
    while(low <= high)
    {
        int mid = low + (high - low) / 2;
        if (Check(mid))
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while(t --)
    {
        Solve();
    }
    return 0;
}
