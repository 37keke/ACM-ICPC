#include<algorithm>
#define INF 0x7fffffff
using namespace std;
int mpt[1005][1005] = {} ;
int vis[1005] ={};
int dis[1005] = {} ;
int ans[1005] ={} ;
void dijkstra(int n, int to) // dijkstra模板， 目的是求一个点到各个点的最短路，如果图存在负权值 ， 则求不出来。
{
    memset(vis, 0, sizeof(vis));
     for(int i = 1 ; i <= n ; i++)  // 该点到N点的初始化
     {
         dis[i] = mpt[to][i] ;
     }
     vis[to] = 1 ;   // 原点初始化
     dis[to] = 0 ;
     for(int i = 1 ; i <= n ; i++){
        int x = -2  ; int mx = 0x3f3f3f3f ; // 定义2个变量初始化
        for(int j = 1 ; j <= n ; j++){
            if(!vis[j] && mx > dis[j] ) mx = dis[x = j] ; // 找到这个点到所有点中的最大
        }
        if(x == -2) break ; // 如果break掉就说明这一个点没有到任何一个点的路
        vis[x] = 1 ;    // 最大权值的一个点做标记
        for(int j = 1 ; j <= n ; j++){
            if(!vis[j] && dis[j] > dis[x] + mpt[x][j])  // 松弛操作
                dis[j] = dis[x] + mpt[x][j] ;
        }
     }
     // 函数走到这里就说明一个点到所有点的最短路距离都求出来了。
     // dis[1,2,3,4,5,6,7,8,9,,,,,,n] ;

}
int main(){
 int n , m , x ;
 scanf("%d%d%d",&n,&m,&x) ;
   int u , v , w ;
     memset(mpt, 0x3f3f3f3f, sizeof(mpt));
 for(int i = 0 ; i < m ; i++)
 {
     scanf("%d %d %d",&u,&v,&w) ;
     mpt[u][v] = w ;
 }
     dijkstra(n , x ) ;
    for(int i=1; i<=n; i++)
        for(int j=i+1; j<=n; j++)
       swap(mpt[i][j] ,mpt[j][i]) ; // 矩阵倒置
     dijkstra(n , x) ;
     int anss = 0 ;
     for(int i = 1 ; i <= n ; i++)
    {
     anss = max(ans[i] , anss) ;
    }
        cout << anss << endl ;
}
