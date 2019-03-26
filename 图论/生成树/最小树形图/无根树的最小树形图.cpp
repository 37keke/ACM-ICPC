最小树形图：  无根最小树形图模板：
1.	题目大意：给你N个城市，选择一个城市建首都，城市编号为0~N-1，给你M条路，每条路包括u，v，w，即从u到v的花费为w，现在问你那个城市建首都的话，从这个城市到其余城市的花费最小，最小花费是多少，如果有多个适合的城市，输出编号小的城市。无法到达输出impossible。
2.	解题思路：这是无根最小树形图的题，我们可以先假定一个虚根，即源点，并设源点到每个城市的权值为   全图所有权值之和大一点，然后就是树形图模板，细节在代码中。
3.	//本题边长都为__int64,其实int型也可以过，但长整型应该更广，所以本题都为__int64
4.	#include <cstdio>
5.	#include<iostream>
6.	#include <cstring>
7.	#include <cstdlib>
8.	#include<cmath>
9.	using namespace std;
10.	typedef double type;
11.	#define INF 2000000000
12.	#define N 1005
13.
14.	struct edge //图的结构体
15.	{
16.	    int u,v;__int64 w;
17.	}e[10005];
18.
19.	int m,n,pre[N],id[N],visit[N],xroot;
20.	__int64 in[N],sum;
21.	//eCnt为图中的边数
22.	//n为图中的顶点数
23.	//pre[i]为顶点i的前驱节点
24.	//id[i]为缩环，形成新图的中间量
25.	//in[i]为点i的最小入边
26.	//visit[i]遍历图时记录顶点是否被访问过
27.	__int64 directedMST(int root,int nv,int ne)
28.	{
29.	    __int64 ans=0;
30.	    while(1)
31.	    {
32.	        //1.找最小入边
33.	        for(int i=0;i<nv;i++) in[i]=INF;
34.	        for(int i=0;i<ne;i++)
35.	        {
36.	            int u=e[i].u;
37.	            int v=e[i].v;
38.	            if(u!=v&&e[i].w<in[v])
39.	            {
40.	                if(u==root)  //此处标记与源点相连的最小边
41.	                    xroot=i;
42.	                in[v]=e[i].w;
43.	                pre[v]=u;
44.	            }
45.	        }
46.	        for(int i=0;i<nv;i++)                          //判断图是否连通
47.	            if(i!=root&&in[i]==INF) return -1;  //除了跟以外有点没有入边,则根无法到达它
48.	         //2.找环
49.	        int nodeCnt=0;          //图中环的数目
50.	        memset(id, -1, sizeof(id));
51.	        memset(visit, -1, sizeof(visit));
52.	        in[root]=0;
53.	        for(int i=0;i<nv;i++)
54.	        {
55.	            ans+=in[i];
56.	            int v=i;
57.	            while(visit[v]!=i&&id[v]==-1&&v!=root)//每个点寻找其前序点，要么最终寻找至根部，要么找到一个环
58.	            {
59.	                visit[v]=i;
60.	                v=pre[v];
61.	            }
62.	            if(v!=root&&id[v]==-1)//缩点
63.	            {
64.	                for(int u=pre[v];u!=v;u=pre[u])
65.	                    id[u]=nodeCnt;
66.	                id[v]=nodeCnt++;
67.	            }
68.	        }
69.	        if(nodeCnt==0) break;//如果无环，跳出循环
70.	        for(int i=0; i<nv; i++)
71.	            if(id[i]==-1)
72.	                id[i]=nodeCnt++;
73.	        //3.缩点，重新标记
74.	        for(int i=0;i<ne;i++)
75.	        {
76.	            int v=e[i].v;
77.	            e[i].u=id[e[i].u];
78.	            e[i].v=id[e[i].v];
79.	            if(e[i].u!=e[i].v)
80.	                e[i].w-=in[v];
81.	        }
82.	        nv=nodeCnt;
83.	        root=id[root];
84.	    }
85.	    return ans;
86.	}
87.
88.	int main()
89.	{
90.	    int m;
91.	    while(scanf(“%d%d”,&n,&m)!=EOF)
92.	    {
93.	        sum=0;
94.	        for(int i=0;i<m;i++)
95.	        {
96.	            scanf(”%d%d%I64d”,&e[i].u,&e[i].v,&e[i].w);
97.	            e[i].u++;e[i].v++;     //都++之后，把0设为超级源点，联通各点
98.	            sum+=e[i].w;
99.	            if(e[i].u==e[i].v)
100.	                e[i].w=INF;//消除自环
101.	        }
102.	        sum++;      //此处必须++，因为需要权值比总权值大，因为这个w几次，，，
103.	        for(int i=m;i<n+m;i++)
104.	        {
105.	            e[i].u=0;
106.	            e[i].v=i-m+1;
107.	            e[i].w=sum;
108.	        }
109.	        __int64 ans=directedMST(0,n+1,m+n);
110.	        if(ans==-1 || ans-sum>=sum) printf(“impossible\n”);//ans-sum是除去虚根的最小树形图的最短路径，如果这个距离比所有的边权值和sum还大，说明还有另外的边由虚点发出，故说明此图不连通
111.	        else printf(“%I64d %d\n”, ans-sum, xroot-m);
112.	        printf(”\n”);
113.	    }
114.	    return 0;
115.	}
