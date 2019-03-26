/* 链式前向星SPFA最短路算法*/
#include<iostream>
#include<queue>
#include <algorithm>
#include <stdio.h>
#include<cstring>
using namespace std ;
#define INF 9999999
const int maxn = 1005000 ;
int N, M, head[maxn] ;
int dis[maxn], cnt;
int vis[maxn] ;
//int coun[maxn] ; coun数组用于判断负环
 int n , m , k ;
struct Edge
{  int cap ;
    int v,  next; // v 是去向 ， cap 是流量（权值） next就不解释了
}e[maxn];

void init()
{

    cnt = 0;
    memset(head, -1, sizeof (head));
   // memset(coun , 0 , sizeof(coun)) ; // 作用：判断负环
    memset(vis , 0 , sizeof(vis)) ;
}

void  Addedge(int x, int y, int z)
{

    e[cnt].v = y;
    e[cnt].cap = z;
    e[cnt].next = head[x];
    head[x] = cnt++;
}
 void spfa(int s){
   //  for(int i = 1 ; i <= n ; i++) dis[i] = INF , vis[i] = 0 ; 看数据范围
   queue<int>q ;
   dis[s] = 0 ;
 //  coun[s]++ ;
   q.push(s) ;
   while(!q.empty()){
      int now = q.front() ;
      q.pop() ;
      vis[now] = 0 ;
      for(int i = head[now] ; i != -1 ; i = e[i].next){
         int v = e[i].v ;
         int cost = e[i].cap ;
         if(dis[v] > dis[now] + cost){
             dis[v] = dis[now] + cost ;
             if(vis[v] == 0 ){ vis[v] = 1 ;/*coun[v]++ ; */q.push(v) ;}

         }
      }
   }
 }

 int main(){

  return 0 ;
 }
