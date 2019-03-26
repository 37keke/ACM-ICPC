/*给一张无向图，你需要将边定向，使得定向后的有向图强连通。
0代表x到y 1代表y到x
*/
#define ll long long
#define inf 0x3f3f3f3f
#define N 1500005
#define M 1500005
using namespace std;
void read(int &x){scanf("%d",&x);}
int fg;
int n,m;//n个点 m条边
struct node
{
    int from,to,nex;
    int cut;//记录这条边是否为割边(桥）
}edge[2*M];  //双向边则 edge[i]与edge[i^1]是2条反向边
int head[N] ,num;//在一开始就要 memset(head,-1,sizeof(head)); num=0;
int low[N],dfn[N],Index;
void add(int u,int v)
{
    node E={u,v,head[u],0};
    edge[num]=E;
    head[u]=num++;
}
void tarjin(int u,int pre)
{
    low[u]=dfn[u]= ++Index;
    int flag=1;//flag是阻止双向边的反向边 i和i^1
    for(int i=head[u];i!=-1;i=edge[i].nex)
    {
        int v=edge[i].to;
        if(flag&&v==pre)
        {
            flag=0;
            continue;
        }
        if(!dfn[v])
        {
            tarjin(v,u);
            if(low[u]>low[v])low[u]=low[v];
            if(low[v]>dfn[u])//是桥low[v]表示v能走到的最早祖先
            //有重边且u是v的最早祖先 则low[v]==dfn[u],所以不会当作桥
            //这个位置是桥
                {fg=1;edge[i].cut=edge[i^1].cut=1;}
        }
        else if(low[u]>dfn[v])low[u]=dfn[v];
    }
}
bool liantong;//是否连通
void find_edgecut()
{
    memset(dfn,0,sizeof(dfn));
    Index=0;
    tarjin(1,1);
    liantong=true;
    for(int i=1;i<=n;i++)if(!dfn[i]){liantong=false;return;}
}
bool vis[N];
void init(){
    for(int i = 0;i<=n;i++)head[i] = -1;
    num = 0;
    memset(vis, 0, sizeof(vis));
    fg = 0;
}

void dfs(int u){
    vis[u] = true;
    for(int i = head[u]; i!=-1; i = edge[i].nex){
        int v = edge[i].to;
        if(edge[i].cut==1) continue;
        if(edge[i].cut==0)
        {
            edge[i].cut=1;
            edge[i^1].cut=-1;
        }
        if(!vis[v]) dfs(v);
    }
}
int main(){
    int u, v;
    read(n);read(m);{
        init();
        //
        while(m--){
            read(u);read(v);
            add(u, v);
            add(v, u);
        }
        find_edgecut();
        if(fg){puts("impossible");return 0;}
        dfs(1);
        for(int i = 0; i < num; i+=2)
        if(edge[i].cut==1)printf("1");
        else printf("0");
        puts("");
    }
    return 0;
}
/*求所有桥中最小的桥的权值
int main()
{
	int i,j,k;
	while(~scanf("%d%d",&n,&m),n)
	{
		memset(head,-1,sizeof(head));
		edgenum=0;
		while(m--)
		{
			scanf("%d%d%d",&i,&j,&k);
			add(i,j,k);
			add(j,i,k);
		}
		find_edgecut();
		int ans=inf;
		if(liantong==false){puts("0");continue;}
		for(int i=0;i<num;i++)if(edge[i].cut)
		{
			if(edge[i].val<ans)ans=edge[i].val;
		}

		if(ans==inf)ans=-1;
		if(ans==0)ans=1;
		printf("%d\n",ans);

	}
	return 0;
}
