#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef pair<int, int> pii;
typedef map<int, int> mii;

#define FOR(a, b, c) for (int a = (b); a <= (c); a++)
#define REV(a, b, c) for (int a = (b); a >= (c); a--)
#define endl '\n'
#define fi first
#define se second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

#define debug(x) clog << x << endl

void fixIO() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}

void File(const string &fileName = "") {
  if (fopen((fileName + ".INP").c_str(), "r")) {
    freopen((fileName + ".INP").c_str(), "r", stdin);
    freopen((fileName + ".OUT").c_str(), "w", stdout);
  }
}

vector<string> s1, s2;

void Read() {
  s1.resize(4);
  s2.resize(4);
  FOR(i, 0, 3) { cin >> s1[i]; }
  FOR(i, 0, 3) { cin >> s2[i]; }
}

int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};

int BFS() {
  if (s1 == s2) {
    return 0;
  }
  map<vector<string>, int> dist;
  queue<vector<string>> q;
  q.push(s1);
  dist[s1] = 0;
  while (q.size()) {
    vector<string> cur = q.front();
    q.pop();
    int d = dist[cur];
    FOR(r, 0, 3) {
      FOR(c, 0, 3) {
        if (cur[r][c] == '1') {
          FOR(i, 0, 3) {
            int nr = r + dx[i];
            int nc = c + dy[i];
            if (nr >= 0 && nr < 4 && nc >= 0 && nc < 4 && cur[nr][nc] == '0') {
              vector<string> nb = cur;
              swap(nb[r][c], nb[nr][nc]);
              if (nb == s2) {
                return d + 1;
              }
              if (dist.find(nb) == dist.end()) {
                dist[nb] = d + 1;
                q.push(nb);
              }
            }
          }
        }
      }
    }
  }
  return -1;
}

void Solve() { cout << BFS(); }

int main() {
  fixIO();
  File("CHESS");
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