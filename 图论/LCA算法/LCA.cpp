/*一个村子里有n个房子，这n个房子用n-1条路连接起来，接下来有m次询问，每次询问两个房子a,b之间的距离是多少。*/
/*链式前向星*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
#define MAXEDGE 100001
#define maxn 40001
#define maxm 410
struct EDGE{int to,v,next;};
struct QUESTION{int to,num,next;};
EDGE a[MAXEDGE];
QUESTION b[maxm];
int DATA,N,M,edge[maxn],question[maxn],tot1=0,tot2=0,ansf[maxm],anst[maxm];
int fa[maxn],LCA[maxm],dist[maxn];//dist[i]记录了i点到根节点的距离
bool vis[maxn];
void add_edge(int x,int y,int value)
{
      a[++tot1].to=y;//这条边的到达点
      a[tot1].v=value;//这条边的长度
      a[tot1].next=edge[x];//与这条边有相同初始点的上一条边编号
      edge[x]=tot1;//更新编号
}
void add_question(int x,int y,int number)
{
      b[++tot2].to=y;//这个询问的点标号
      b[tot2].num=number;//这个询问的对应编号
      b[tot2].next=question[x];
      question[x]=tot2;
}
int get(int x)
{
      if(fa[x]==x)  return x;
      return fa[x]=get(fa[x]);
}
void Tarjan(int x)
{
      fa[x]=x;//作为当前的根节点,将其父亲指向自己
      vis[x]=true;//标记该点已经走过
      for(int i=question[x];i;i=b[i].next)
      {
            int now_to=b[i].to;
            if(vis[now_to])//如果其子节点及子节点的子树全部访问完才会进入这一步,由vis判断
                  LCA[b[i].num]=get(now_to);//更新LCA值
      }
      for(int i=edge[x];i;i=a[i].next)
      {
            int now_to=a[i].to;
            if(!vis[now_to])
            {
                  dist[now_to]=dist[x]+a[i].v;//更新dist值
                  Tarjan(now_to);//相当于将now_to当成根节点递归下去
                  fa[now_to]=x;//更新子节点的父亲
            }
      }
}
int main()
{
	  scanf("%d",&DATA);
	  for(int now=1;now<=DATA;now++)
      {
            memset(vis,false,sizeof(vis));
            memset(edge,0,sizeof(edge));
            memset(question,0,sizeof(question));
            memset(a,0,sizeof(a));
            memset(b,0,sizeof(b));
            memset(dist,0,sizeof(dist));
            memset(fa,0,sizeof(fa));
            tot1=0,tot2=0;
            scanf("%d%d",&N,&M);
            for(int i=1;i<=N;i++)
                  fa[i]=i;//首先将所有节点的父亲节点指向自己
            for(int i=1;i<=N-1;i++)
            {
                  int A,B,C;
                  scanf("%d%d%d",&A,&B,&C);
                  add_edge(A,B,C);//建无向边,用临接链表存储
                  add_edge(B,A,C);
            }
            for(int i=1;i<=M;i++)
            {
                  int A,B;
                  scanf("%d%d",&A,&B);
                  add_question(A,B,i);//这里用进行两次记录,保证在更新LCA时能顾全这两个点
                  add_question(B,A,i);
                  ansf[i]=A,anst[i]=B;
            }
            Tarjan(1);
            for(int i=1;i<=M;i++)
                  printf("%d\n",dist[ansf[i]]+dist[anst[i]]-2*dist[LCA[i]]);
      }
      return 0;
}
