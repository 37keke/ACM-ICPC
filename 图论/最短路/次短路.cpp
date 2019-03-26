const int maxn = 5e3+5;
const int maxm = 1e5+5;
int cas=1;
struct node {
    int to, next, w;
    int type; // 在次短路中要多一个标记表示它的状态是最短还是次短.这个要注意下.
    bool operator < (const node & a) const {
        return w > a.w;
    }
}e[maxm<<1];
int cnt, head[maxn];
void add(int u, int v, int w) {
    e[cnt] = node{v, head[u], w};
    head[u] = cnt++;
}
int n, m;
void init() {
    cnt = 0;
    Fill(head, -1);
}
int dis1[maxn], dis2[maxn];
int vis[maxn][2];
void dij(int st, int ed) {
    priority_queue<node> q; Fill(vis, 0);
    Fill(dis1, inf); Fill(dis2, inf);
    dis1[st] = 0 ; q.push(node{st, 0, 0, 0});
     //次短路的初值就保持为无穷大. 因为st 到 st的次短路不是0.
    while(!q.empty()) {
        node u = q.top();
        q.pop();
        if (vis[u.to][u.type]) continue;
        vis[u.to][u.type] = 1;   // 这里和原先的板子很像,但是要变成二维的,因为当前这个点从最短路和次短路
        // 是两个不同的状态, 要分开标记!

        for (int i = head[u.to] ; ~i ; i = e[i].next) {
            int to = e[i].to;
            int d = u.w + e[i].w;
            // 唯一和最短路不同的就是这写的u.w即当前到这个u.to的路径而不是dis1[u.to].(好好想一想,一步一步打出来)
            // 因为下次再更新回来时此时的边长应该是下次更新回来的边长, 不再是到u.to的最短路了, 那样会导致错误答案.
            if (d < dis1[to]) {
                swap(d, dis1[to]);
                //不能直接赋值,而是要交换,因为原先的最短路值是要留着来更新次短路值的.
                    //随便举一举例子就知道了.当然在这里判一下也是可以的,就可以直接赋值了.
                q.push(node{to, 0, dis1[to], 0});
            }
            if (d < dis2[to]) {
                dis2[to] = d;
                q.push(node{to, 0, dis2[to], 1});
            }
        }
    }
    /*for (int i = 1 ; i <= n ; i ++) {
        printf("%d%c", dis1[i], i == n ?'\n':' ');
    }
    for (int i = 1 ; i <= n ; i ++)  {
        printf("%d%c", dis2[i], i == n ?'\n':' ');
    }*/
    printf("%d\n", dis2[ed]);
}
void solve()
{
    init();
    scanf("%d%d",&n, &m);
    for (int i = 1 ; i <= m ;i ++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w); add(v, u, w);
    }
    dij(1, n);
}
