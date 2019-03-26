#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
#define maxn 10005
int dfn[maxn];///代表最先遍历到这个点的时间
int low[maxn];///这个点所能到达之前最早的时间点
int Father[maxn];///保存这个节点的父亲节点
int n, m, Time, top;///Time 时间点，  top用于栈操作
vector<vector<int> > G;

void Init()
{
    G.clear();
    G.resize(n+1);
    memset(low, 0, sizeof(low));
    memset(dfn, 0, sizeof(dfn));
    memset(Father, 0, sizeof(Father));
    Time = 0;
}

void Tarjan(int u,int fa)
{
    low[u] = dfn[u] = ++Time;
    Father[u] = fa;
    int len = G[u].size(), v;

    for(int i=0; i<len; i++)
    {
        v = G[u][i];

        if(!dfn[v])
        {
            Tarjan(v, u);
            low[u] = min(low[u], low[v]);
        }
        else if(fa != v)///假如我们在这里写上了 low[u] = min(low[v], low[u]),那么就相当于我们由v回到了v之前的节点
            low[u] = min(dfn[v], low[u]);
    }
}
void solve()
{/**
求割点
一个顶点u是割点，当且仅当满足(1)或(2)
(1) u为树根，且u有多于一个子树。
(2) u不为树根，且满足存在(u,v)为树枝边(或称 父子边，即u为v在搜索树中的父亲)，使得 dfn(u)<=low(v)。
（也就是说 V 没办法绕过 u 点到达比 u dfn要小的点）
注：这里所说的树是指，DFS下的搜索树*/
    int RootSon = 0, ans = 0;///根节点儿子的数量
    bool Cut[maxn] = {false};///标记数组，判断这个点是否是割点

    Tarjan(1,0);

    for(int i=2; i<=n; i++)
    {
        int v = Father[i];
        if(v == 1)///也是就说 i的父亲是根节点
            RootSon ++;
        else if(dfn[v] <= low[i])
            Cut[v] = true;
    }

    for(int i=2; i<=n; i++)
    {
        if(Cut[i])
            ans ++;
    }
    if(RootSon > 1)
        ans++;

    printf("%d\n", ans);
}
int main()
{
    while(scanf("%d", &n), n)
    {
        int a, b;
        char ch;
        Init();
        while(scanf("%d", &a), a)
        {
            while(scanf("%d%c",&b,&ch))
            {
                G[a].push_back(b);
                G[b].push_back(a);
                if(ch == '\n')
                    break;
            }
        }
        solve();
        int ll = 0 ;
    }
    return 0;
}
