#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
using namespace std;
#define INF 0x3FFFFFF
#define MAXN 2222
#define eps 1e-6
bool zero(double x) {return x>=-eps&&x<=eps;}
struct edge
{
	int  u,v;
	double w;
}e[10005];
int n,en,m;
int pre[MAXN],id[MAXN],vis[MAXN];
double in[MAXN];
void add(int u,int v,double w)
{
	e[en].u=u;
	e[en].v=v;
	e[en++].w=w;
}
int zl(int root ,int vn)
{
	double ans=0;
	int cnt;
	while(1)
	{
		for(int i=0;i<vn;i++)
			in[i]=INF,id[i]=-1,vis[i]=-1;
		for(int i=0;i<en;i++)
		{
			if(in[e[i].v]>e[i].w && e[i].u!=e[i].v)
			{
				pre[e[i].v]=e[i].u;
				in[e[i].v]=e[i].w;
			}
		}
		in[root]=0;
		pre[root]=root;
		for(int i=0;i<vn;i++)  // 发现如果找不到，就输出这个
		{
			ans+=in[i];
			if(zero(in[i]-INF)){puts("poor snoopy");
				return -1;
			}
		}
		cnt=0;
		for(int i=0;i<vn;i++)
		{
			if(vis[i]==-1)
			{
				int t=i;
				while(vis[t]==-1)
				{
					vis[t]=i;
					t=pre[t];
				}
				if(vis[t]!=i || t==root) continue;
				for(int j=pre[t];j!=t;j=pre[j])
					id[j]=cnt;
				id[t]=cnt++;
			}
		}
		if(cnt==0) break;
		for(int i=0;i<vn;i++)
			if(id[i]==-1)
				id[i]=cnt++;
		for(int i=0;i<en;i++)
		{
			int u,v;
			u=e[i].u;
			v=e[i].v;
			e[i].u=id[u];
			e[i].v=id[v];
			e[i].w-=in[v];
		}
		vn=cnt;
		root=id[root];
	}
	printf("%.2lf\n",ans); // ans 表示的是最小树形图的权值
	return ans;
}
double x[105],y[105];
int main()
{
    int a,b;
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=0;i<n;i++)
        {
            scanf("%lf%lf",&x[i],&y[i]);
        }
        en=0;
        for(int i=1;i<=m;i++)  // 给出的是坐标，但是构图方法差不多
        {
            scanf("%d%d",&a,&b);
            a--;
            b--;
            double d=sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]));
            add(a,b,d);
        }
        zl(0,n);
    }
    return 0;
}
