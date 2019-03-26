#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <queue>
#define INF 0x3fffffff
#define RE(x) (x)^1
#define S 1
#define MAXN 2050
using namespace std;
/*
dinic算法
题目: POJ P - Flow Problem
链接矩阵的优化
减低时间复杂度
时间: 156ms
*/
int N, M, head[MAXN], dis[MAXN], idx;

struct Edge
{
    int No, cap, next; // NO 是去向 ， cap 是流量（权值） next就不解释了
}e[100000];

void init()
{
    idx = -1;
    memset(head, 0xff, sizeof (head));
}

void  Addedge(int x, int y, int z)
{
    ++idx;
    e[idx].No = y;
    e[idx].cap = z;
    e[idx].next = head[x];
    head[x] = idx;
    ++idx;
    e[idx].No = x;
    e[idx].cap = 0;
    e[idx].next = head[y];
    head[y] = idx;
}

bool bfs(int s , int t)  ///构建分层图
{
    int pos;
    queue<int>q;
    memset(dis, -1, sizeof (dis)); /// dis 表示 层次
    dis[s] = 0;
    q.push(s);
    while (!q.empty()) {
        pos = q.front();
        q.pop();
        for (int i = head[pos]; i!=-1; i = e[i].next) {
            if (e[i].cap > 0 && dis[e[i].No]==-1) {  // 如果有流量 && 没有走过
                dis[e[i].No] = dis[pos]+1;
                q.push(e[i].No);  // 注意不要直接把“i”push进去了
            }
        }
    }
    return dis[t] != -1;
}

int dfs(int u, int flow)
{
    if (u == N) {
        return flow;
        // 结束条件，把流推到了T节点（汇点）
    }
    int tf = 0, f;
    for (int i = head[u]; i != -1; i = e[i].next) {
        if (dis[u]+1 == dis[e[i].No] && e[i].cap > 0 && (f = dfs(e[i].No, min(e[i].cap, flow - tf)))) { /// 如果是下一次的点 && 有流量 &&
            e[i].cap -= f;
            e[RE(i)].cap += f;
            tf += f;
        }
    }
    if (tf == 0) {
        dis[u] = -1;
        // tf等于零表示该点没有进行增广的能力，应及时将其高度赋值为-1，防止第二次被搜索到
    }
    return tf;
}

int main()
{
    int T, ans, ca = 0, a, b, c;
    scanf("%d", &T);
    while (T--) {
        init();
        ans = 0;
        scanf("%d %d", &N, &M);
        for (int i = 0; i < M; ++i) {
            scanf("%d %d %d", &a, &b, &c);
            Addedge(a, b, c);
        }
        while (bfs(1 , N)) {    /// dinic算法
            ans += dfs(S, INF);
        }
        printf("Case %d: %d\n", ++ca, ans);
    }
    return 0;
}
