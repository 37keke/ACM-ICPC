#include<bits/stdc++.h>
using namespace std ;
int inf = 0x3f ;
const int maxn = 1e5 +10 ;
int pre[maxn] ;
struct node{
  int a , b, c ;
}st[maxn];
int find(int x)
{
    int r=x;
    while(pre[r]!=r)
    r=pre[r];//找到他的前导结点
   int i=x,j;
    while(i!=r)//路径压缩算法
    {
        j=pre[i];//记录x的前导结点
        pre[i]=r;//将i的前导结点设置为r根节点
        i=j;
    }

    return r;
}

bool cmp(node a , node b ) {
 return a.c < b.c ;
}
int cnt = 0 ;
void init(int n){
    cnt = 0 ;
 for(int i = 1 ; i <= n ; i++){
    pre[i] = i ;
 }
}
void add(int u , int v , int w){
  st[cnt].a = u , st[cnt].b = v ;
  st[cnt++].c = w ;
}

int main(){

  int n , m ;
  cin >> n >> m ;
  init(n) ;
  int u , v , w;
  for(int i = 0 ; i < m ; i++){
    cin >> u >> v >> w ;
    add(u , v,  w) ;
  }
  sort(st , st + m , cmp) ;
  int ans = inf ;
  for(int i = 0 ; i < m ; i++){
      int r = st[i].a ;
      int l = st[i].b ;
      if(find(r) != find(l) ) pre[r] = l , ans = max(ans , st[i].c);
  }
  if(ans != inf)
  cout << ans << endl ;
  else cout << "0" << endl;
  return 0 ;
}
