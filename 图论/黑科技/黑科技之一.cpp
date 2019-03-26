黑科技： （因为我不会）
给你N 个点 M条边 N <= 10000 , M - N <= 100 ,
下面Q次询问，每行U ， V 表示 U到V的最短路
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 200;
const int INF = 0x3f3f3f3f;
struct edge {
    int from, to, nxt;
}edge[N*2];
int head[N], vis[N*2], vs[N], anc[N][20], deep[N], a[N], b[N], d[N], ans[N], Q, n, cnt = 0;
void add_edge(int u, int v) {
    edge[cnt].from = u;
    edge[cnt].to = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt++;
}
void dfs(int o, int u) {
    vs[u] = true;
    deep[u] = deep[o] + 1;
    for (int i = head[u]; ~i; i = edge[i].nxt) {
        int v = edge[i].to;
        if(v != o) {
            if(!vis[i] && !vs[v]) {
                vis[i] = vis[i^1] = true;
                anc[v][0] = u;
                for (int i = 1; i < 20; i++) anc[v][i] = anc[anc[v][i-1]][i-1];
                dfs(u, v);
            }
        }
    }
}
void init() {
    for (int i = 1; i <= n; i++) head[i] = -1;
    for (int i = 0; i < 20; i++) anc[1][i] = 1;
}
int lca(int u, int v) {
    if(deep[u] < deep[v]) swap(u, v);
    for (int i = 19; i >= 0; i--) if(deep[anc[u][i]] >= deep[v]) u = anc[u][i];
    if(u == v) return u;
    for (int i = 19; i >= 0; i--) if(anc[u][i] != anc[v][i]) u = anc[u][i], v = anc[v][i];
    return anc[u][0];
}
int dis(int u, int v) {
    return deep[u] + deep[v] - 2*deep[lca(u, v)];
}
void bfs(int s) {
    for (int i = 1; i <= n; i++) vs[i] = false;
    d[s] = 0;
    vs[s] = true;
    queue<int> q;
    q.push(s);
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            int v = edge[i].to;
            if(!vs[v]) {
                vs[v] = true;
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    for (int i = 1; i <= Q; i++) {
        ans[i] = min(ans[i], d[a[i]] + d[b[i]]);
    }
}
int main() {
    int m, u, v;
    scanf("%d %d", &n, &m);
    init();
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, 1);
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++) {
        scanf("%d %d", &a[i], &b[i]);
        ans[i] = dis(a[i], b[i]);
    }
    for (int i = 0; i < cnt; i += 2) {
        if(!vis[i]) {
            bfs(edge[i].from);
        }
    }
    for (int i = 1; i <= Q; i++) printf("%d\n", ans[i]);
    return 0;
}
