#include <bits/stdc++.h>
using namespace std;

int sudoku[9][9];
vector<pair<int,int>>f;

void read(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    if(fopen("57.INP","r")){
        freopen("57.INP","r",stdin);
        freopen("57.OUT","w",stdout);
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cin>>sudoku[i][j];
            if(sudoku[i][j]==0){
                f.emplace_back(i,j);
            }
        }
    }
}

void prints(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout<<sudoku[i][j]<<' ';
        }
        cout<<'\n';
    }
}

bool fo=false;
vector<vector<bool>>r(9,vector<bool>(10,false)),c(9,vector<bool>(10,false));
vector<vector<vector<bool>>>h(9,vector<vector<bool>>(9,vector<bool>(10,false)));

void tr(int cu){
    if(fo)return;
    if(cu==(int)f.size()){
        fo=true;
        prints();
        return;
    }
    int x=f[cu].first,y=f[cu].second;
    for(int i=1;i<=9;i++){
        if(!r[x][i]&&!c[y][i]&&!h[x/3][y/3][i]){
            r[x][i]=c[y][i]=h[x/3][y/3][i]=true;
            sudoku[x][y]=i;
            tr(cu+1);
            r[x][i]=c[y][i]=h[x/3][y/3][i]=false;
        }
    }
}

void solve(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(sudoku[i][j]!=0){
                r[i][sudoku[i][j]]=true;
                c[j][sudoku[i][j]]=true;
                h[i/3][j/3][sudoku[i][j]]=true;
            }
        }
    }
    tr(0);
}

int main(){
    read();
    solve();
    return 0;
}