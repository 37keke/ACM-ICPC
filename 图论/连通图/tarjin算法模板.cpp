#include <string.h>
#include <iostream>
#include <algorithm>
#include<cstdio>
using namespace std;
/*
Tarjan算法
复杂度O(N+M)
*/
/// 除了solve和主函数外才是该算法模板
const int maxn = 2e5 + 10; // 点数
const int maxm = 2e5 + 10; // 边数

int head[maxn], tot;
int Low[maxn], DFN[maxn],Stack[maxn],Belong[maxn];//Belong数组的值是1~scc
int Index, top;
int scc;//强连通分量的个数
bool Instack[maxn];
int num[maxn];//各个强连通分量包含点的个数，数组编号1~scc
//num数组不一定需要，结合实际情况
int n ;
struct Edge
{
    int to,next;
}edge[maxn];

void addedge(int u,int v)
{
    edge[tot].to = v;edge[tot].next = head[u];head[u] = tot++;
}
void Tarjan(int u)
{
    int v;
    Low[u] = DFN[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    for(int i = head[u];i != -1;i = edge[i].next)
    {
        v = edge[i].to;      // 去向
        if(!DFN[v])
        {
            Tarjan(v);
            if(Low[u] > Low[v])
                  Low[u] = Low[v];
        }
        else if(Instack[v] && Low[u] > DFN[v])
            Low[u] = DFN[v];
    }
    if(Low[u] == DFN[u]) // 在这里可以使用num数组，记录路径
    {
        scc++;
        do
        {
            v = Stack[--top];
            Belong[v] = scc;  // 这就是为什么belong【】数组里面的值为 1 - scc 的原因
            Instack[v] = false;
        }
        while( v!= u);
    }
}
int in[maxn],out[maxn];
int finda[100000] ;
void solve(int N)
{
    memset(DFN,0,sizeof(DFN));
    memset(Instack,false,sizeof(Instack));
    Index = scc = top = 0;
    for(int i = 1;i <= N;i++)
        if(!DFN[i]) // 如果图有2个， 就会一把2个图遍历完，但通常情况下就只需要一遍
           Tarjan(i);
       //     cout << "LOW = " ;
        for(int i = 1 ; i <= N ; i++){
                finda[Belong[i]] ++ ;
        }  //   cout << endl ;
    //    cout << "BElong = " ;

        int ans = 0 ;
        for(int i = 0 ; i <= scc ; i++){
           if(finda[i]  > 1  ) ans += finda[i] * (finda[i] - 1 ) / 2 ;
        }
        cout << ans << endl ;


               return  ;
}
void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
}
int main()
{   int n , m ;
cin >> n >> m  ;
int u , v   ;
init() ;
for(int i = 0 ; i < m ; i++){
    scanf("%d%d",&u , &v) ;
    addedge(u , v) ;
}

        solve(n);

    return 0;
}
