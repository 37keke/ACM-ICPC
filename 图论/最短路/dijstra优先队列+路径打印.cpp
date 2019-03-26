Dijstra链式前向星+打印路径
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
#define inf 0x3f3f3f3f
using namespace std;
const int maxn = 1005;
const int maxm = 100500;
int n = maxn, m, s, t;   //n为点数 s为源点
int head[maxn]; //head[from]表示以head为出发点的邻接表表头在数组es中的位置，开始时所有元素初始化为-1
int d[maxn]; //储存到源节点的距离，在init()中初始化
bool vis[maxn]; //是否访问过
int nodep;  //在邻接表和指向表头的head数组中定位用的记录指针，开始时初始化为0
int pre[maxn];
struct node {
    int num;
    int dis;
    node (int a = 0, int b = 0) : num(a), dis(b) {}
    friend bool operator <(node a, node b) {
        return a.dis > b.dis;
    }
};
struct edge {
    int v, next;
    int w;
}es[maxm];

void init() {
    for(int i = 0; i < maxn; i++) {
        d[i] = inf;
        vis[i] = false;
        head[i] = -1;
        pre[i] = -1;
    }
    nodep = 0;
}

void addedge(int from, int to, int weight)
{
    es[nodep].v = to;
    es[nodep].w = weight;
    es[nodep].next = head[from];
    head[from] = nodep++;
}
void dijkstra()
{
    priority_queue<node> pq;
    d[s] = 0;    //s为源点
    pq.push(node(s, 0));
    while(!pq.empty()) {
        node num = pq.top();
        pq.pop();
        int u = num.num;
        if(vis[u]) continue;
        vis[u] = 1;
        //遍历邻接表
        for(int i = head[u]; i != -1; i = es[i].next) {  //在es中，相同from出发指向的顶点为从head[from]开始的一项，逐项使用next寻找下去，直到找到第一个被输
                                                        //入的项，其next值为-1
            int v = es[i].v;
            if(!vis[v] && d[v] > d[u] + es[i].w) { //松弛(RELAX)操作
                d[v] = d[u] + es[i].w;
                pre[v] = u;
                pq.push(node(v, d[v]));
            }
        }
    }
}

void putpath() {
    stack<int> path;
    int now = t;
    while(1) {
        path.push(now);
        if(now == s) {
            break;
        }
        now = pre[now];
    }
    while(!path.empty()) {
        now = path.top();
        path.pop();
        printf("%d ", now);
    }
    cout << endl ;
}

int main()
{
    while(cin >> m >> n) {
        init();
        int a, b, c;
        while(m--) {
            cin >> a >> b >> c;
            addedge(a, b, c);
            addedge(b, a, c);
        }
        s = 1, t = n;
        dijkstra();
        cout << d[t] << endl;
        putpath();
    }
    return 0;
}

kruskal优先队列形式
#define MAX_V 100005
#define INF 0x3f3f3f3f

using namespace std;

const int inf = 0x3f3f3f3f;
const int maxn = 105;

int V;
int f[maxn];
int x[maxn], y[maxn];

struct edge {
    int u, v;
    int cost;
    friend bool operator < (edge e1, edge e2) {
        return e1.cost > e2.cost;
    }
};
priority_queue<edge> pq;
void init(int x)
{
    for(int i = 0; i <= x; i++) {
        f[i] = i;
    }
}

int getf(int x)
{
    if(x != f[x])
        f[x] = getf(f[x]);
    return f[x];
}

void unions(int x, int y)
{
    x = getf(x);
    y = getf(y);
    if(x != y)
        f[y] = x;
}

bool same(int x, int y) {
    return getf(x) == getf(y);
}

int kruskal() {
    int res = 0;
    while(!pq.empty()) {
        edge e = pq.top();
        pq.pop();
        if(!same(e.u, e.v)) {
            unions(e.u, e.v);
            res += e.cost;
        }
    }
    return res;
}

int main()
{
    int n, m;
       while( cin >> n && n) {
        int a, b, c, k;
        edge e;
        init(maxn);
        for(int i = 0; i < n * (n - 1) / 2; i++) {
            scanf("%d %d %d %d", &a, &b, &c, &k);
            if(k) {
                unions(a, b);
            }
            else {
                e.u = a, e.v = b, e.cost = c;
                pq.push(e);
            }
        }

        int ans = kruskal();
        cout << ans << endl;
        while(!pq.empty()) {
            pq.pop();
        }
    }
    return 0;
}
