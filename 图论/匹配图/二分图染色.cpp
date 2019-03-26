#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std ;
const int maxn = 10500 ;
int head[maxn] ;
vector<int> G[maxn] ;
int line[maxn] ;
int key = 0 ;
int r = 0 , l = 0 ;
int cnt = 0 ;
int n , m ;
int vis[maxn] ;
struct node{
 int v , next ;
}a[maxn];
void add(int u, int v)
{
    a[cnt].v = v;
    a[cnt].next = head[u];
    head[u] = cnt++;

}
int _min(int a , int b){
   if(a > b ) return b ;
    return a ;
 }
void init(){
   cnt = 0 ;
   key = 0 ;
   r = 0 , l = 0 ;
   memset(head , -1 , sizeof(head)) ;
   for(int i = 0 ; i <= n ; i++) G[i].clear() ;
   memset(vis, 0 , sizeof(vis)) ;
}
int find(int x)
{     // 算法模板 凶奴力算法什么什么的。。。。
    int i;

    for(i = head[x]; i != -1; i = a[i].next)
    {
        int v = a[i].v;

        if(vis[v] == -1)
        {
            vis[v] = 1;
            if(line[v] == -1 || find(line[v]))
            {
                line[v] = x;
                return 1;
            }
        }
    }
    return 0;
}

void judge(int x , int colar){ /// DFS染色
    if(key == 1 ) return ;
    vis[x] = colar ;
    if(colar == 1 ) {r++ ; colar = 2 ; }
    else {l++  ; colar = 1 ; }
    int len = G[x].size() ;
    for(int i = 0 ; i < len ; i++){
            if(vis[G[x][i]] == 0)
           judge(G[x][i] , colar) ;
      else if(vis[G[x][i]] == vis[x] )  {key = 1 ; return ;}
    }

}
int main(){
  //  cout << _min( 3 , 1) <<endl ;
   while(cin >> n >> m ){

        init() ;
     int u , v  ;
    for(int i = 0 ; i < m ; i++){
         scanf("%d %d",&u,&v) ;
        add(u , v) ;
         G[u].push_back(v) ;
          G[v].push_back(u) ;
    }
     judge(1 , 1) ;
     int ans = 0 ;
     if(key == 1) cout << "No" << endl ;
     else {
        int len = _min(r , l) ;
        memset(line , -1 , sizeof(line)) ;
      for(int i = 1 ; i <= n ; i++){
        memset(vis , -1 , sizeof(vis)) ;
        if(find(i)) ans++ ;
     }
     cout << ans <<endl ;
    }
   }
return 0 ;
}
