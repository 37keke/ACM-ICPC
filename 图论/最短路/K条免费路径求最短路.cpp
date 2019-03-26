#include<bits/stdc++.h>
using namespace std ;
#define LL long long
#define INF 0x3f3f3f3f3f3f3f3f
 const int maxn = 1e6 + 10 ;

int vis[maxn][20] ;
int n , m , k ;
LL dis[maxn][20] ;
int head[maxn] ;
struct node{
  int to , next ;
  LL val ;
  node(){} ;
     node(int to, int nx, LL w) : to(to), next(nx), val(w) {}
 }st[maxn ] ;

 struct NODE{
   int xp , to ;
   LL w ;
   NODE(){} ;
   NODE(int t , int p , LL val){ to = t ; xp = p ; w = val ;  }
     bool operator < (const NODE &r) const
    {
        return w > r.w;
    }
 };
 int cnt ;

 void add(int u, int v, LL w)
{
    st[++cnt] = node(v, head[u], w); head[u] = cnt;
}
 void dijstra(){
  for(int i = 1 ; i <= n ; i++) for(int j = 0 ; j <= k ; j++) dis[i][j] = INF , vis[i][j] = 0 ;

  priority_queue<NODE> q ; q.push(NODE(1 ,0 , 0 )) ; dis[1][0] = 0 ;

   while(!q.empty()){
      int u = q.top().to ;
      int p = q.top().xp ;
      LL cost = q.top().w ;
      q.pop() ;
      if(vis[u][p] == 1) continue ;
      vis[u][p] = 1 ;
      dis[u][p] = cost ;
      for(int i = head[u] ; i != -1 ; i = st[i].next ){
           int v = st[i].to ;
           int c = st[i].val;
           if(dis[u][p] + c < dis[v][p] ) { dis[v][p] = dis[u][p] + c ; q.push(NODE(v, p ,dis[v][p] )) ; }
           if(p + 1 <= k && dis[u][p]< dis[v][p+1] ) { dis[v][p+1] = dis[u][p] ;  q.push(NODE(v  , p+1 , dis[v][p+1] ) ) ; }
      }
   }
 }

   void init(){
    memset(head , -1 , sizeof(head)) ;
    cnt = 0 ;
  }
int main(){
    int  t ;
    cin >> t ;
    while(t--){
             init() ;
        scanf("%d %d %d",&n,&m,&k) ;
         int u , v ;
         LL w ;
        for(int i = 0 ; i < m ; i++){
            scanf("%d%d%lld",&u,&v,&w) ;
            add(u , v , w ) ;
        }
        dijstra();
        LL ans = dis[n][k] ;
        printf("%lld\n",ans) ;
    }
  return 0 ;
}
