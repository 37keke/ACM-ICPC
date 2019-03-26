#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
#include<cstring>
#include<string>
/* 最大流 Ek算法
复杂度： O（n*m^2）
适合稀疏图， 不适合稠密图
*/
using namespace std;
 const int maxn = 220 ;
 const int INF = 0x7f7f7f7f;
int G[maxn][maxn] , flow[maxn] , pre[maxn] ; /// G 存图 ，flow描述从原点到当前点的容量 ， pre标记上一步的曾广路是哪一条链
int n , m ;  /// 这道题 m 为点 ， n 为边
queue<int> q;
 int BFS(int s , int t){  /// 作用是找曾广路
       while(!q.empty()) q.pop() ;
       memset(pre , -1 , sizeof(pre)) ;
       pre[s] = 0 ; flow[s] = INF ;
       q.push(s) ;
       while(!q.empty()){
        int  p = q.front() ;
        q.pop() ;
        if(p == t) break ; //走到了汇点

        for(int u = 1 ; u <= n ; u++){
            if(u!= s && G[p][u] >0 && pre[u] == -1) {
                pre[u] = p ;
                flow[u] = min(flow[p] , G[p][u]) ; ///当前节点上一段的流量和下一段的流量的最小值
                q.push(u)  ;
            }
        }
       }
       if(pre[t] == -1 ) return -1 ;
       return flow[t] ;  /// 返回曾广路径中的流量最小值
 }
 int EK(int s , int t){  /// 传入源点和汇点
   int delta = 0 , tot = 0 ;///tot记录最大流的值是多少 ， delta记录这个图的曾广路的流量
   while(1){
    delta = BFS(s , t) ;/// 这里就是反复的对这个图BFS找曾广路，直到找不到为止
    if(delta == -1) break ;
    int p = t ;   /// 从曾广路开始往后退
    while(p != s){
        G[pre[p]][p] -= delta ;  ///正向边减去流量
        G[p][pre[p]] += delta ;  ///反向边加上
        p = pre[p] ;
    }
    tot += delta ;
   }
   return tot ;
 }

int main(){
int u , v ,w  ;
 while(scanf("%d%d",&m,&n) != EOF){
     memset(G , 0 , sizeof(G)) ;
     memset(flow , 0 , sizeof(flow)) ;
    for(int i = 0 ; i <m ; i++){
        scanf("%d%d%d",&u,&v,&w) ;
        G[u][v] += w ;  /// 这里是构图，如果有重边的话就相当于累加它的容量
    }
    printf("%d\n",EK(1 , n ) ) ;
 }
}
/*
自测样例：
6 5
1 2 6
1 3 7
1 4 8
2 5 10
3 5 10
4 5 10
21
5 4
1 2 8
2 4 10
2 3 100
3 4 2
1 3 7
10
*/
