#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef pair<int, int> pii;
typedef map<int, int> mii;

#define FOR(a, b, c) for(int a = (b); a <= (c); a++)
#define REV(a, b, c) for(int a = (b); a >= (c); a--)
#define endl '\n'
#define fi first
#define se second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()

#define debug(x) clog << x << endl

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

string s1, s2;

void Read()
{
    cin >> s1;
    cin >> s2;
}

bool get_bit(int sta, int ind)
{
    return (sta >> ind) & 1;
}

int tog_bit(int sta, int ind)
{
    return sta ^ (1 << ind);
}

int sim(int sta, char doo)
{
    if (doo == 'A')
    {
        bool g1 = get_bit(sta, 0);
        sta = tog_bit(sta, 0);
        if (g1 == 1)
        {
            sta = tog_bit(sta, 5);
        } 
        else
        {
            bool g4 = get_bit(sta, 3);
            sta = tog_bit(sta, 3);
            if (g4 == 0)
            {
                sta = tog_bit(sta, 6);
            }
            else
            {
                sta = tog_bit(sta, 5);
            }
        }
    }
    else if (doo == 'B')
    {
        bool g2 = get_bit(sta, 1);
        sta = tog_bit(sta, 1);
        if (g2 == 1) {
            bool g4 = get_bit(sta, 3);
            sta = tog_bit(sta, 3);
            if (g4 == 0)
            {
                sta = tog_bit(sta, 6);
            } 
            else 
            {
                sta = tog_bit(sta, 5);
            }
        } 
        else 
        {
            bool g5 = get_bit(sta, 4);
            sta = tog_bit(sta, 4);    
            if (g5 == 1)
            {
                sta = tog_bit(sta, 6);
            }
            else 
            {
                sta = tog_bit(sta, 7);
            }
        }
    }
    else
    {
        bool g3 = get_bit(sta, 2);
        sta = tog_bit(sta, 2); 
        if (g3 == 0)
        {
            sta = tog_bit(sta, 7);
        }
        else 
        {
            bool g5 = get_bit(sta, 4);
            sta = tog_bit(sta, 4);
            if (g5 == 1)
            {
                sta = tog_bit(sta, 6);
            }
            else
            {
                sta = tog_bit(sta, 7);
            }
        }
    }
    return sta;
}

int its(const string& s)
{
    int state = 0;
    for (int i = 0; i < 8; ++i)
    {
        if (s[i] == '1')
        {
            state |= (1 << i);
        }
    }
    return state;
}

void Solve()
{
    vector<int> dist(256, -1);
    vector<int> par(256, -1);
    vector<char> mv(256, ' ');
    int sta1 = its(s1);
    int sta2 = its(s2);
    queue<int> q;
    q.push(sta1);
    dist[sta1] = 0;
    char doo[] = {'A', 'B', 'C'};
    bool found = false;
    while(q.size())
    {
        int u = q.front();
        q.pop();
        if (u == sta2)
        {
            found = true;
            break;
        }
        for (auto d : doo)
        {
            int v = sim(u, d);
            if (dist[v] == -1)
            {
                dist[v] =  dist[u] + 1;
                par[v] = u;
                mv[v] = d;
                q.push(v);
            }
        }
    }
    if (!found || dist[sta2] > 100)
    {
        cout << 0;
    }
    else
    {
        string ans = "";
        int cur = sta2;
        while(cur != sta1)
        {
            ans += mv[cur];
            cur = par[cur];
        }
        reverse(all(ans));
        cout << ans;
    }
}

int main() 
{
    fixIO();
    File("OTOMAT");
    Read();
    Solve();
    return 0;
}

/**
 *  "Chua ngo, chua trao, chua gan bo,
 *   da hon, da nho, da dau thuong."
 *                              — Xuan Dieu
 *
 *  Code by   : Nguyen Minh Khoi (github/nmkdeveloper)
 *  Created   : 2026.08.02
 */