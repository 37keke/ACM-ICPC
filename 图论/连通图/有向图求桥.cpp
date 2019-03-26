#define MAXN //点数
#define MAXM //边数
#define INF //无穷大
using namespace std;
struct Edge
{
    int from, to, next;
    bool cut;//是否为桥
}edge[MAXM];
int head[MAXN], edgenum;
int low[MAXN], dfn[MAXN];
int dfs_clock;
int sccno[MAXN], scc_cnt;//记录某个点属于哪个SCC  scc_cnt是SCC计数器
vector<int> scc[MAXN];//存储SCC里面所有点
stack<int> S;//存储点
bool Instack[MAXN];//标记是否在栈里面
vector<int> G[MAXN];//存储缩点后新图
int n, m;//n个点 m条单向边
void init()
{
    edgenum = 0;
    memset(head, -1, sizeof(head));
}
void addEdge(int u, int v)
{
    Edge E = {u, v, head[u], 0};
    edge[edgenum] = E;
    head[u] = edgenum++;
}
void getMap()
{
    int s, t;
    while(m--)
    {
        scanf("%d%d", &s, &t);
        addEdge(s, t);
    }
}
void tarjan(int u, int fa)
{
    int v;
    low[u] = dfn[u] = ++dfs_clock;
    S.push(u);
    Instack[u] = true;
    for(int i = head[u]; i != -1; i = edge[i].next)
    {
        v = edge[i].to;
        if(!dfn[v])
        {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] > dfn[u])//桥
            edge[i].cut = true;
        }
        else if(Instack[v])
        low[u] = min(low[u], dfn[v]);
    }
    if(low[u] == dfn[u])
    {
        scc_cnt++;//SCC数目加一
        scc[scc_cnt].clear();
        for(;;)
        {
            v = S.top(); S.pop();
            Instack[v] = false;//出栈
            sccno[v] = scc_cnt;//v属于第scc_cnt个SCC
            scc[scc_cnt].push_back(v);//存储属于它的所有点
            if(v == u) break;
        }
    }
}
void find_cut(int l, int r)
{
    memset(low, 0, sizeof(low));
    memset(dfn, 0, sizeof(dfn));
    memset(sccno, 0, sizeof(sccno));
    memset(Instack, false, sizeof(Instack));
    dfs_clock = scc_cnt = 0;
    for(int i = l; i <= r; i++)
    if(!dfn[i]) tarjan(i, -1);
}
int in[MAXN], out[MAXN];//记录SCC的入度与出度
void suodian()//缩点
{
    for(int i = 1; i <= scc_cnt; i++) G[i].clear(), in[i] = out[i] = 0;
    for(int i = 0; i < edgenum; i++)
    {
        int u = sccno[edge[i].from];
        int v = sccno[edge[i].to];
        if(u != v)
        G[u].push_back(v), out[u]++, in[v]++;//构建新图 统计入度 出度
    }
}
int main()
{
    while(scanf("%d%d", &n, &m), n||m)
    {
        init();
        getMap();
        find_cut(1, n);//找桥
        suodian();
        /*到此已找出所有桥和SCC以及SCC里面的点和入度*/
    }
    return 0;
}
