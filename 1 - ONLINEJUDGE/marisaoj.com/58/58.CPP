#include <bits/stdc++.h>
using namespace std;

int n,A[10][10];

void read(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    if(fopen("58.INP","r"))freopen("58.INP","r",stdin),freopen("58.OUT","w",stdout);
    cin>>n;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)cin>>A[i][j];
}

bool v[10];
int r=(int)1e9+5;

void BT(int po,int c,int p){
    if(c==n){
        int t=p+A[po][0];
        r=min(r,t);
        return;
    }
    for(int j=0;j<n;j++){
        if(v[j])continue;
        if(p+A[po][j]>=r)continue;
        v[j]=1;
        BT(j,c+1,p+A[po][j]);
        v[j]=0;
    }
}

void solve(){
    v[0]=1;
    BT(0,1,0);
    cout<<r;
}

int main(){
    read();
    solve();
    return 0;
}