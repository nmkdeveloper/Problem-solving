#include <bits/stdc++.h>
using namespace std;

int n,m,A[25][25],va[25][25],dx[]={-1,0,1,-1,1,-1,0,1},dy[]={-1,-1,-1,0,0,1,1,1};

void read(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    if(fopen("547.INP","r"))freopen("547.INP","r",stdin),freopen("547.OUT","w",stdout);
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>A[i][j];
        }
    }
}

int c(int x,int y){
    int r=0;
    for(int i=0;i<8;i++){
        int u=x+dx[i],v=y+dy[i];
        if(u>=0&&u<n&&v>=0&&v<m)r+=va[u][v];
    }
    return r;
}

bool np(int i,int j){
    if(i>1)for(int y=0;y<m;y++)if(c(i-2,y)!=A[i-2][y])return 1;
    if(i>0)for(int y=0;y+1<j;y++)if(c(i-1,y)!=A[i-1][y])return 1;
    return 0;
}

void p(){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<va[i][j]<<' ';
        }
        cout<<'\n';
    }
}

bool dfs(int i,int j){
    if(i==n){
        for(int x=0;x<n;x++)for(int y=0;y<m;y++)if(c(x,y)!=A[x][y])return 0;
        return 1;
    }
    if(np(i,j))return 0;
    int u=i+(j+1)/m,v=(j+1)%m;
    for(int k=1;k>=0;k--){
        va[i][j]=k;
        if(dfs(u,v))return 1;
    }
    return 0;
}

void solve(){
    if(dfs(0,0))p();
}

int main(){
    read();
    solve();
    return 0;
}