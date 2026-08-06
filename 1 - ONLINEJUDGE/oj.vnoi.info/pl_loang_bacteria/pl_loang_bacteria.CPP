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

int n, m, C;

void Read()
{
    cin >> n >> m >> C;
}

const int MAXPRIME = (int) 1e6 + 15;
bool isPrime[MAXPRIME];

void Sieve()
{
    fill(isPrime, isPrime + MAXPRIME, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 4; i < MAXPRIME; i += 2)
    {
		isPrime[i] = false;
    }
	for (int i = 3; i * i < MAXPRIME; i  += 2)
	{
		if (isPrime[i])
		{
			for (int j = i * i; j < MAXPRIME; j += i * 2)
			{
				isPrime[j] = false;
			}
		}
	}
}

vi getPF(int x)
{
	vi fac;
	int tmp = x;
	for (int i = 2; i * i <= tmp; i++)
	{
		if (tmp % i == 0)
		{
			if (isPrime[i])
			{
				fac.pb(i);
			}
			while(tmp % i == 0)
			{
				tmp /= i;
			}
		}
	}
	if (tmp > 1 && isPrime[tmp])
	{
		fac.pb(tmp);
	}
	return fac;
}

void Solve()
{
    Sieve();
	vi dist(C + 1, -1);
	vi traVal(C + 1, -1);
	vi traOpe(C + 1, -1);
	queue<int> q;
	q.push(n);
	dist[n] = 0;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		if (u == m)
		{
			break;
		}
		if (1LL * u * u <= C)
		{
			int v = u * u;
			if (dist[v] == -1)
			{
				dist[v] = dist[u] + 1;
				traVal[v] = u;
				traOpe[v] = 0;
				q.push(v);
			}
		}
		vi Primes = getPF(u);
		for (auto i : Primes)
		{
			int v = u / i;
			if (dist[v] == -1)
			{
				dist[v] = dist[u] + 1;
				traVal[v] = u;
				traOpe[v] = i;
				q.push(v);
			}
		}
	}
	if (dist[m] == -1)
	{
		cout << "Impossible";
	}
	else
	{
		cout << dist[m] << endl;
		vi Ops;
		int cur = m;
		while (cur != n)
		{
			Ops.pb(traOpe[cur]);
			cur = traVal[cur];
		}
		reverse(all(Ops));
		for (auto i : Ops)
		{
			cout << i << ' ';
		}
	}
}

int main() 
{
    fixIO();
    File("BACTERIA");
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