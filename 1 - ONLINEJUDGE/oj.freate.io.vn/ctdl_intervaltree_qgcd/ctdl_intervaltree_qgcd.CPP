#include <bits/stdc++.h>
#define N (int) 1e5+2
using namespace std;
int n,q;
int a[N], t[4*N];
void build(int id, int l, int r){
    if (l>r) return;
    if (l==r) {
        t[id]=a[l];
        return;
    }
    int m=(l+r)/2;
    build(id*2,l,m);
    build(id*2+1,m+1,r);
    t[id]=__gcd(t[id*2],t[id*2+1]);
}
void update(int id, int l, int r, int pos, int val) {
    if (pos<l||r<pos) return;
    if (l==r) {
        t[id]=val;
        return;
    }
    int m=(l+r)/2;
    update(id*2,l,m,pos,val);
    update(id*2+1,m+1,r,pos,val);
    t[id]=__gcd(t[id*2],t[id*2+1]);
}
int get(int id, int l, int r, int u, int v){
    if (v<l||r<u) return 0;
    if (u<=l && r<=v){
        return t[id];
    }
    int m=(l+r)/2;
    return __gcd(get(id*2,l,m,u,v), get(id*2+1,m+1,r,u,v));
}
int main()
{
    freopen("segtre.inp","r",stdin);
    freopen("segtre.out","w",stdout);
    cin>>n;
    for (int i=1; i<=n; i++)
        cin>>a[i];
    build(1,1,n);
    for (int i=1;i<=4*n; i++)
        cout<<t[i]<<" ";
    cout<<'\n';

    cin>>q;
    while (q--){
        int type;
        cin>>type;
        if (type==1){
            int i, x;
            cin>>i>>x;
            update(1,1,n,i,x);
        }
        else if (type==2) {
            int u,v;
            cin>>u>>v;
            cout<<get(1,1,n,u,v)<<'\n';
        }
    }

    /*
    for (int i=1;i<=4*n; i++)
        cout<<t[i]<<" ";\
    */
    return 0;
}