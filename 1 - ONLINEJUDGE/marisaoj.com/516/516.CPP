#include <bits/stdc++.h>
using namespace std;

int n,m;
string t[6],s;

void read(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    if(fopen("516.INP","r"))freopen("516.INP","r",stdin),freopen("516.OUT","w",stdout);
    cin>>n>>m;
    for(int i=0;i<n;i++)cin>>t[i];
    cin>>s;
}

bool f=0;
int dx[]={-1,1,0,0},dy[]={0,0,-1,1};
bool vi[6][6];

void BT(int x,int y, int c){
    if(f)return;
    if(t[x][y]!=s[c])return;
    if(c==(int)s.size()-1){
        f=1;
        return;
    }
    for(int i=0;i<4;i++){
        int u=x+dx[i],v=y+dy[i];
        if(u>=0&&u<n&&v>=0&&v<m&&!vi[u][v]){
            vi[u][v]=true;
            BT(u,v,c+1);
            vi[u][v]=false;
        }
    }
}

void solve(){
    for(int i=0;i<n;i++){
        if(f)break;
        for(int j=0;j<m;j++){
            if(f)break;
            if(t[i][j]==s[0])memset(vi, 0, sizeof(vi)),vi[i][j]=1,BT(i,j,0);
        }
    }
    cout<<(f?"YES":"NO");
}

int main(){
    read();
    solve();
    return 0;
}