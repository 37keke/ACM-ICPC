#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <deque>
#include <sstream>
#define MAX_V 1005
#define INF 0x3f3f3f3f
using namespace std;

//最小费用最大流模版.求最大费用最大流建图时把费用取负即可。
//无向边转换成有向边时需要拆分成两条有向边。即两次加边。
const int maxn = 1010;
const int maxm = 1000200;a
const int inf = 0x3f3f3f3f;

struct Edge {
    int v, cap, cost, next;
}p[maxm << 1];

int e, sumFlow, n, m, st, en;
int head[maxn], dis[maxn], pre[maxn];
bool vis[maxn];
void init() {
    e = 0;
    memset(head, -1, sizeof(head));
}

void addEdge(int u, int v, int cap, int cost) {
    p[e].v = v; p[e].cap = cap; p[e].cost = cost;
    p[e].next = head[u]; head[u] = e++;
    p[e].v = u; p[e].cap = 0; p[e].cost = -cost;
    p[e].next = head[v]; head[v] = e++;
}

bool spfa(int s,int t, int n) {
    int u, v;
    queue<int>q;
    memset(vis, false, sizeof(vis));
    memset(pre, -1, sizeof(pre));
    for(int i = 0; i <= n; i++)
        dis[i] = inf;
    vis[s] = true;
    dis[s] = 0;
    q.push(s);
    while(!q.empty()) {
        u = q.front();
        q.pop();
        vis[u] = false;
        for(int i = head[u]; i != -1; i = p[i].next) {
            v = p[i].v;
            if(p[i].cap && dis[v] > dis[u] + p[i].cost) {
                dis[v] = dis[u] + p[i].cost;
                pre[v] = i;
                if(!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
     }
     if(dis[t] == inf)
         return false;
     return true;
}

int MCMF(int s, int t, int n) {
    int flow = 0; // 总流量
    int minflow, mincost;
    mincost = 0;
    while(spfa(s, t, n)) {
        minflow = inf + 1;
        for(int i = pre[t]; i != -1; i = pre[p[i^1].v]) {
            if(p[i].cap < minflow) {
                minflow = p[i].cap;
            }
        }
        flow += minflow;
        for(int i = pre[t]; i != -1; i = pre[p[i^1].v]) {
            p[i].cap -= minflow;
            p[i^1].cap += minflow;
        }
        mincost += dis[t] * minflow;
    }
    sumFlow = flow; // 最大流
    return mincost;
}

int x1[105], x2[105], yy[105], y2[105];

int main ()
{
    int t, kcase = 0;
    int N, M;
    while(~scanf("%d %d", &N, &M) && N && M) {
        int k1 = 0, k2 = 0;
        char str[105];
        for(int i = 0; i < N; i++) {
            scanf("%s", str);
            for(int j = 0; j < M; j++) {
                if(str[j] == 'm') {
                    x1[++k1] = i;
                    yy[k1] = j;
                }
                if(str[j] == 'H') {
                    x2[++k2] = i;
                    y2[k2] = j;
                }
            }
        }
        init();
        n = k1;
        //cout << k1;
        for(int i = 1; i <= n; i++) {
            addEdge(0, i, 1, 0);
            addEdge(n + i, n * 2 + 1, 1, 0);
            for(int j = 1; j <= n; j++) {
                int k = (abs(x1[i] - x2[j]) + abs(yy[i] - y2[j]));
                //cout << " " << w[i][j] ;
                addEdge(i, j + n, 1, k);
            }
            //cout <<endl;
        }
        int ans = MCMF(0, 2 * n + 1, 2 * n + 1);
        printf("%d\n", ans);
    }
    return 0;
}
