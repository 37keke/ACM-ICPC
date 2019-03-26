#include<string>
#include<cstring>
#include<iostream>
#include<cstdio>
#define LL long long
using namespace std ;
/*
LAC算法模板
题目: POJ - how far way ?
复杂度（n + k ） k 次询问
双链式前向星 （一个建图 一个回答）
*/
int n , m ;

const int maxn = 100500;
int head[maxn] ; // 链式前向星
int dis[maxn] ; // 用于记录路径之和（用法; 有头节点一直往下累加 ， dis[v] 表示从节点1到v的距离）
int pre[maxn] ; // 并查集函数
int LAC[maxn] ; // 用于记录公共祖先是谁
int _head[maxn] ;
int ans[maxn] ,  ans1[maxn] ;
int vis[maxn] ; // vis标记 ，因为是双向边，不加vis标记会造成死循环
int par[maxn] ;
struct edge{
 int to , next ; int w ;
}edge[maxn ];
struct node{
  int to , next , num ;
}st[maxn];
int cnt = 0  , tot = 0;
 int find(int x)
{
    int r=x;
    while(pre[r]!=r)
    r=pre[r];//找到他的前导结点

    return r;
}

void init(){
  cnt = 0 ;
  tot = 0 ;
  memset(head , -1 , sizeof(head)) ;
  //memset(dis , 0 , sizeof(dis)) ;
 // memset(vis , 0 , sizeof(vis)) ;
  memset(_head , -1 , sizeof(_head)) ;
//  memset(LAC , -1 , sizeof(LAC) ) ;
  //memset(ans , 0 , sizeof(ans)) ;
  //memset(ans1 , 0 , sizeof(ans1)) ;

 for(int i = 1 ; i <= n ; i++){
    par[i] = pre[i] = i ;
    vis[i] = 0 ;
    LAC[i] = -1 ;
    dis[i] = 0 ;
 }
}
void add(int u , int v , int  w){
  edge[++cnt].to = v ;
  edge[cnt].w = w ;
  edge[cnt].next = head[u] ;
  head[u] = cnt ;
}
void add_pro(int u , int v , int num ) {
   st[++tot].to = v ;
   st[tot].num = num ;
   st[tot].next = _head[u] ;
   _head[u] = tot ;
}
void tarjin(int u){
    vis[u] = 1 ;
    pre[u] = u ; //

    for(int i = head[u] ; i != -1 ; i = edge[i].next ){
         int v = edge[i].to ;
         if(!vis[v]){
          dis[v] = edge[i].w + dis[u] ; // 求出1节点到 v节点的距离 (就是这里没注意顺序WA了好多次。。。)
          tarjin(v) ;
          pre[v] = u ; // Union函数 因为是树就不需要判断了
         }
    }
    for(int i = _head[u] ; i != -1 ; i = st[i].next){
         int v = st[i].to ;

         if(vis[v]){
            LAC[st[i].num] = find(v) ;

         }
    }
}

int main(){
   int q;


  while(scanf("%d %d %d",&n,&m,&q ) != EOF){
            init() ;

  int u , v ; int  w ;

     for(int i = 0 ; i <m ; i++){
         scanf("%d %d %d",&u,&v,&w) ;
         add(u , v, w ) ;
         add(v , u, w ) ;
     }
     for(int i = 0 ; i < q ; i++){
         scanf("%d %d",&u,&v) ;

         add_pro(u , v, i) ;
         add_pro(v , u, i) ;
         ans[i] = u , ans1[i] = v ; // 这个用于记录问题的答案， 因为add_pro这个函数相当于构图
     }
   //  cout << kk[0] << endl ;
   for(int i = 1 ; i <= n ; i++){ if(vis[i] == 0 ) {memset(vis , 0, sizeof(vis)) ; tarjin(i) ;} }
      for(int i = 0 ; i < q ; i++){
        if(LAC[i] == -1) cout << "Not connected" <<endl ;
       else  printf("%d\n",dis[ans[i]] + dis[ans1[i]] - 2 * dis[LAC[i]]) ;
        // 有dis数组的意义来理解
      }
  }
 return 0 ;
}
