
#include<bits/stdc++.h>
using namespace std ;
vector<int> G[20000 + 5] ;
void add(int u , int v ){
   G[v].push_back(u) ;
   G[u].push_back(v) ;
}
int maxn = 0 ;
int flag = 0 ;
int vis[20000 + 5] ;
int dian = 0 ;
void dfs(int x  ,int distan , int ans ){ /// 点 ，j距离 ， 深度
    vis[x] = 1 ;
    if(maxn < ans ){
        maxn = ans ;
        dian  = x ;
        flag = distan ;
    }
    int len = G[x].size() ;
    for(int i = 0 ; i < len ; i++){
            if(vis[G[x][i]] == 0){
                dfs(G[x][i]  , distan + 1 , ans + 1) ;
            }
    }
 }
int main(){
    int n , m ;
    cin >> n >> m ;
     int x ;
     for(int i = 2 ; i <= n + m ; i++){
        cin >> x  ;
      add(i  , x ) ; // 构图部分
     }
     memset(vis , 0 , sizeof(vis)) ;
     dfs(1 , 0 , 0 ) ;
     memset(vis , 0 , sizeof(vis)) ;
     flag = 0 ; maxn = 0 ;
     dfs(dian , 0 , 0 ) ;
     cout << flag << endl ;
 return 0 ;
}
