DFS：
求奇偶环
using namespace std;
const int N = 5000 + 10;
vector<int> g[N];
int st[N],instack[N],mark[N],top;
void dfs(int u)
{
    instack[u] = true;
    mark[u] = true;//因为可能不联通，所以需要没有mark过的点，需要再次调用dfs
    st[++top] = u;
    for(int i=0;i<g[u].size(); ++i)
    {
        int v = g[u][i];
        if(!instack[v])
            dfs(v);
        else
        {

            int t;
            for(t=top;st[t]!=v;--t);//在栈中找到环的起始点
            printf("%d:",top-t+1);//这这里就能判断是奇数环还是偶数环
            for(int j=t;j<=top;++j)
                printf("%d ",st[j]);
            puts("");
        }
    }
    instack[u] = false;   //dfs回溯
    top--;
}
void init(int n)
{
    for(int i=1;i<=n;++i)
    {
        g[i].clear();
        instack[i] = mark[i] = 0;
    }
    top = 0;
}
int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        init(n);
        int u,v;
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",&u,&v);
            g[u].push_back(v);
        }
        for(int i=1;i<=n;++i)
            if(!mark[i])
                dfs(i);
    }
    return 0;
}
树的直径：

#include<bits/stdc++.h>
using namespace std ;
vector<int> G[20000 + 5] ;
void add(int u , int v ){
   G[v].push_back(u) ;
   G[u].push_back(v) ;
}
int maxn = 0 ;
int flag = 0 ;
int vis[20000 + 5] ;
int dian = 0 ;
void dfs(int x  ,int distan , int ans ){ /// 点 ，j距离 ， 深度
    vis[x] = 1 ;
    if(maxn < ans ){
        maxn = ans ;
        dian  = x ;
        flag = distan ;
    }
    int len = G[x].size() ;
    for(int i = 0 ; i < len ; i++){
            if(vis[G[x][i]] == 0){
                dfs(G[x][i]  , distan + 1 , ans + 1) ;
            }
    }
 }
int main(){
    int n , m ;
    cin >> n >> m ;
     int x ;
     for(int i = 2 ; i <= n + m ; i++){
        cin >> x  ;
      add(i  , x ) ; // 构图部分
     }
     memset(vis , 0 , sizeof(vis)) ;
     dfs(1 , 0 , 0 ) ;
     memset(vis , 0 , sizeof(vis)) ;
     flag = 0 ; maxn = 0 ;
     dfs(dian , 0 , 0 ) ;
     cout << flag << endl ;
 return 0 ;
}
LCA算法模板：
#include<string>
#include<cstring>
#include<iostream>
#include<cstdio>
#define LL long long
using namespace std ;
/*
LAC算法模板
题目: POJ - how far way ?
复杂度（n + k ） k 次询问
双链式前向星 （一个建图 一个回答）
*/
int n , m ;

const int maxn = 100500;
int head[maxn] ; // 链式前向星
int dis[maxn] ; // 用于记录路径之和（用法; 有头节点一直往下累加 ， dis[v] 表示从节点1到v的距离）
int pre[maxn] ; // 并查集函数
int LAC[maxn] ; // 用于记录公共祖先是谁
int _head[maxn] ;
int ans[maxn] ,  ans1[maxn] ;
int vis[maxn] ; // vis标记 ，因为是双向边，不加vis标记会造成死循环
int par[maxn] ;
struct edge{
 int to , next ; int w ;
}edge[maxn ];
struct node{
  int to , next , num ;
}st[maxn];
int cnt = 0  , tot = 0;
 int find(int x)
{
    int r=x;
    while(pre[r]!=r)
    r=pre[r];//找到他的前导结点

    return r;
}

void init(){
  cnt = 0 ;
  tot = 0 ;
  memset(head , -1 , sizeof(head)) ;
  //memset(dis , 0 , sizeof(dis)) ;
 // memset(vis , 0 , sizeof(vis)) ;
  memset(_head , -1 , sizeof(_head)) ;
//  memset(LAC , -1 , sizeof(LAC) ) ;
  //memset(ans , 0 , sizeof(ans)) ;
  //memset(ans1 , 0 , sizeof(ans1)) ;

 for(int i = 1 ; i <= n ; i++){
    par[i] = pre[i] = i ;
    vis[i] = 0 ;
    LAC[i] = -1 ;
    dis[i] = 0 ;
 }
}
void add(int u , int v , int  w){
  edge[++cnt].to = v ;
  edge[cnt].w = w ;
  edge[cnt].next = head[u] ;
  head[u] = cnt ;
}
void add_pro(int u , int v , int num ) {
   st[++tot].to = v ;
   st[tot].num = num ;
   st[tot].next = _head[u] ;
   _head[u] = tot ;
}
void tarjin(int u){
    vis[u] = 1 ;
    pre[u] = u ; //

    for(int i = head[u] ; i != -1 ; i = edge[i].next ){
         int v = edge[i].to ;
         if(!vis[v]){
          dis[v] = edge[i].w + dis[u] ; // 求出1节点到 v节点的距离 (就是这里没注意顺序WA了好多次。。。)
          tarjin(v) ;
          pre[v] = u ; // Union函数 因为是树就不需要判断了
         }
    }
    for(int i = _head[u] ; i != -1 ; i = st[i].next){
         int v = st[i].to ;

         if(vis[v]){
            LAC[st[i].num] = find(v) ;

         }
    }
}

int main(){
   int q;


  while(scanf("%d %d %d",&n,&m,&q ) != EOF){
            init() ;

  int u , v ; int  w ;

     for(int i = 0 ; i <m ; i++){
         scanf("%d %d %d",&u,&v,&w) ;
         add(u , v, w ) ;
         add(v , u, w ) ;
     }
     for(int i = 0 ; i < q ; i++){
         scanf("%d %d",&u,&v) ;

         add_pro(u , v, i) ;
         add_pro(v , u, i) ;
         ans[i] = u , ans1[i] = v ; // 这个用于记录问题的答案， 因为add_pro这个函数相当于构图
     }
   //  cout << kk[0] << endl ;
   for(int i = 1 ; i <= n ; i++){ if(vis[i] == 0 ) {memset(vis , 0, sizeof(vis)) ; tarjin(i) ;} }
      for(int i = 0 ; i < q ; i++){
        if(LAC[i] == -1) cout << "Not connected" <<endl ;
       else  printf("%d\n",dis[ans[i]] + dis[ans1[i]] - 2 * dis[LAC[i]]) ;
        // 有dis数组的意义来理解
      }
  }
 return 0 ;
}
二分匹配图：
KM算法模板：
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int MAXN = 305;
const int INF = 0x3f3f3f3f;

int love[MAXN][MAXN];   // 记录每个妹子和每个男生的好感度
int ex_girl[MAXN];      // 每个妹子的期望值
int ex_boy[MAXN];       // 每个男生的期望值
bool vis_girl[MAXN];    // 记录每一轮匹配匹配过的女生
bool vis_boy[MAXN];     // 记录每一轮匹配匹配过的男生
int match[MAXN];        // 记录每个男生匹配到的妹子 如果没有则为-1
int slack[MAXN];        // 记录每个汉子如果能被妹子倾心最少还需要多少期望值

int N;


bool dfs(int girl)
{
    vis_girl[girl] = true;

    for (int boy = 0; boy < N; ++boy) {

        if (vis_boy[boy]) continue; // 每一轮匹配 每个男生只尝试一次

        int gap = ex_girl[girl] + ex_boy[boy] - love[girl][boy];

        if (gap == 0) {  // 如果符合要求
            vis_boy[boy] = true;
            if (match[boy] == -1 || dfs( match[boy] )) {    // 找到一个没有匹配的男生 或者该男生的妹子可以找到其他人
                match[boy] = girl;
                return true;
            }
        } else {
            slack[boy] = min(slack[boy], gap);  // slack 可以理解为该男生要得到女生的倾心 还需多少期望值 取最小值 备胎的样子【捂脸
        }
    }

    return false;
}

int KM()
{
    memset(match, -1, sizeof match);    // 初始每个男生都没有匹配的女生
    memset(ex_boy, 0, sizeof ex_boy);   // 初始每个男生的期望值为0

    // 每个女生的初始期望值是与她相连的男生最大的好感度
    for (int i = 0; i < N; ++i) {
        ex_girl[i] = love[i][0];
        for (int j = 1; j < N; ++j) {
            ex_girl[i] = max(ex_girl[i], love[i][j]);
        }
    }

    // 尝试为每一个女生解决归宿问题
    for (int i = 0; i < N; ++i) {

        fill(slack, slack + N, INF);    // 因为要取最小值 初始化为无穷大

        while (1) {
            // 为每个女生解决归宿问题的方法是 ：如果找不到就降低期望值，直到找到为止

            // 记录每轮匹配中男生女生是否被尝试匹配过
            memset(vis_girl, false, sizeof vis_girl);
            memset(vis_boy, false, sizeof vis_boy);

            if (dfs(i)) break;  // 找到归宿 退出

            // 如果不能找到 就降低期望值
            // 最小可降低的期望值
            int d = INF;
            for (int j = 0; j < N; ++j)
                if (!vis_boy[j]) d = min(d, slack[j]);

            for (int j = 0; j < N; ++j) {
                // 所有访问过的女生降低期望值
                if (vis_girl[j]) ex_girl[j] -= d;

                // 所有访问过的男生增加期望值
                if (vis_boy[j]) ex_boy[j] += d;
                // 没有访问过的boy 因为girl们的期望值降低，距离得到女生倾心又进了一步！
                else slack[j] -= d;
            }
        }
    }

    // 匹配完成 求出所有配对的好感度的和
    int res = 0;
    for (int i = 0; i < N; ++i)
        res += love[ match[i] ][i];

    return res;
}

int main()
{
    while (~scanf("%d", &N)) {

        for (int i = 0; i < N; ++i) // 矩阵存图
            for (int j = 0; j < N; ++j)
                scanf("%d", &love[i][j]);

        printf("%d\n", KM());
    }
    return 0;
}
二分图染色：
#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std ;
const int maxn = 10500 ;
int head[maxn] ;
vector<int> G[maxn] ;
int line[maxn] ;
int key = 0 ;
int r = 0 , l = 0 ;
int cnt = 0 ;
int n , m ;
int vis[maxn] ;
struct node{
 int v , next ;
}a[maxn];
void add(int u, int v)
{
    a[cnt].v = v;
    a[cnt].next = head[u];
    head[u] = cnt++;

}
int _min(int a , int b){
   if(a > b ) return b ;
    return a ;
 }
void init(){
   cnt = 0 ;
   key = 0 ;
   r = 0 , l = 0 ;
   memset(head , -1 , sizeof(head)) ;
   for(int i = 0 ; i <= n ; i++) G[i].clear() ;
   memset(vis, 0 , sizeof(vis)) ;
}
int find(int x)
{     // 算法模板 凶奴力算法什么什么的。。。。
    int i;

    for(i = head[x]; i != -1; i = a[i].next)
    {
        int v = a[i].v;

        if(vis[v] == -1)
        {
            vis[v] = 1;
            if(line[v] == -1 || find(line[v]))
            {
                line[v] = x;
                return 1;
            }
        }
    }
    return 0;
}

void judge(int x , int colar){ /// DFS染色
    if(key == 1 ) return ;
    vis[x] = colar ;
    if(colar == 1 ) {r++ ; colar = 2 ; }
    else {l++  ; colar = 1 ; }
    int len = G[x].size() ;
    for(int i = 0 ; i < len ; i++){
            if(vis[G[x][i]] == 0)
           judge(G[x][i] , colar) ;
      else if(vis[G[x][i]] == vis[x] )  {key = 1 ; return ;}
    }

}
int main(){
  //  cout << _min( 3 , 1) <<endl ;
   while(cin >> n >> m ){

        init() ;
     int u , v  ;
    for(int i = 0 ; i < m ; i++){
         scanf("%d %d",&u,&v) ;
        add(u , v) ;
         G[u].push_back(v) ;
          G[v].push_back(u) ;
    }
     judge(1 , 1) ;
     int ans = 0 ;
     if(key == 1) cout << "No" << endl ;
     else {
        int len = _min(r , l) ;
        memset(line , -1 , sizeof(line)) ;
      for(int i = 1 ; i <= n ; i++){
        memset(vis , -1 , sizeof(vis)) ;
        if(find(i)) ans++ ;
     }
     cout << ans <<endl ;
    }
   }
return 0 ;
}
最大匹配的矩阵模型：
include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 +10 ;
#define INF 0x3f3f3f3f
struct node
{
    int v, next;
}a[maxn];
int head[maxn], vis[maxn], line[maxn], c[maxn][maxn], l[maxn][maxn];
int n, m, cnt;
char mpt[maxn][maxn];
void add(int u, int v)
{
    a[cnt].v = v;
    a[cnt].next = head[u];
    head[u] = cnt++;
}
int find(int x)
{     // 算法模板 凶奴力算法什么什么的。。。。
    int i;

    for(i = head[x]; i != -1; i = a[i].next)
    {
        int v = a[i].v;

        if(vis[v] == -1)
        {
            vis[v] = 1;
            if(line[v] == -1 || find(line[v]))
            {
                line[v] = x;
                return 1;
            }
        }
    }
    return 0;
}
int main(){
    while(scanf("%d", &n))
    {  if(n == 0) break ;
        cnt = 0 ;
    memset(head , -1 , sizeof(head)) ;
 for(int i = 0; i < n; i++)
            scanf("%s", mpt[i]);
     int coun = 0 ;

    for(int i = 0 ; i < n ; i++)
    {     coun++ ;
      for(int j = 0 ; j < n ; j++){
        if(mpt[i][j] == 'X') coun++ ;
        else c[i][j] = coun ;
      }
    }
    m = coun ;
    coun = 0 ;
        for(int j = 0 ; j < n ; j++)
    {     coun++ ;
      for(int i = 0 ; i < n ; i++){
        if(mpt[i][j] == 'X') coun++ ;
        else l[i][j] = coun ;
      }
    }

/*矩阵模型*/
   for(int i = 0 ; i < n ; i++)
    {
      for(int j = 0 ; j < n ; j++){
        if(mpt[i][j] == '.') add(c[i][j] , l[i][j] )  ;
      }
   }
    int ans = 0 ;
    memset(line , -1 , sizeof(line)) ;
      for(int i = 1 ; i <= m ; i++){
        memset(vis , -1 , sizeof(vis)) ;
        if(find(i)) ans++ ;
     }
         cout << ans << endl ;
    }
 return 0 ;
}
闭包传递：
for (int k=1;k<=n;k++)//传递闭包
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            M[i][j]=M[i][j] || ((M[i][k])&&(M[k][j]));
  最短路：
Dijstra链式前向星+打印路径

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
dijkstra优先队列形式
#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int maxm = 4010;  //±ß
const int maxn = 1010; //µã
const int inf = 0x3f3f3f3f;

struct Edge
{
    int to,v,next;
} edge[maxm];
struct node
{
    int num, val; //´æ±àºÅ ºÍ¾àÀë
    node(int _num=0, int _val=0):num(_num), val(_val) {}
    bool operator <(const node &tmp) const
    {
        return val > tmp.val;
    }
};
int head[maxn];
int top;
int n,m;
int dis[maxn];
bool vis[maxn];

void init()
{
    memset(head, -1, sizeof(head));
    top = 0;
}

void addedge(int from, int to, int v)
{
    edge[top].to = to;
    edge[top].v = v;
    edge[top].next = head[from];
    head[from] = top++;
}
void dijkstra(int st) //Æðµã
{
    priority_queue<node> q;
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[st] = 0;
    q.push(node(st, 0));
    while(!q.empty())
    {
        node p = q.top();
        q.pop();
        int nown = p.num;
        if(vis[nown])
            continue;
        vis[nown] = true;
        for(int i=head[nown]; i!=-1; i=edge[i].next)
        {
            Edge e = edge[i];
            if(dis[e.to] > dis[nown] + e.v && !vis[e.to])
            {
                dis[e.to] = dis[nown] + e.v;
                q.push(node(e.to,dis[e.to]));
            }
        }
    }
}
int main()
{

    return 0;
}
dijkstra矩阵形式
#include<algorithm>
#define INF 0x7fffffff
using namespace std;
int mpt[1005][1005] = {} ;
int vis[1005] ={};
int dis[1005] = {} ;
int ans[1005] ={} ;
void dijkstra(int n, int to) // dijkstra模板， 目的是求一个点到各个点的最短路，如果图存在负权值 ， 则求不出来。
{
    memset(vis, 0, sizeof(vis));
     for(int i = 1 ; i <= n ; i++)  // 该点到N点的初始化
     {
         dis[i] = mpt[to][i] ;
     }
     vis[to] = 1 ;   // 原点初始化
     dis[to] = 0 ;
     for(int i = 1 ; i <= n ; i++){
        int x = -2  ; int mx = 0x3f3f3f3f ; // 定义2个变量初始化
        for(int j = 1 ; j <= n ; j++){
            if(!vis[j] && mx > dis[j] ) mx = dis[x = j] ; // 找到这个点到所有点中的最大
        }
        if(x == -2) break ; // 如果break掉就说明这一个点没有到任何一个点的路
        vis[x] = 1 ;    // 最大权值的一个点做标记
        for(int j = 1 ; j <= n ; j++){
            if(!vis[j] && dis[j] > dis[x] + mpt[x][j])  // 松弛操作
                dis[j] = dis[x] + mpt[x][j] ;
        }
     }
     // 函数走到这里就说明一个点到所有点的最短路距离都求出来了。
     // dis[1,2,3,4,5,6,7,8,9,,,,,,n] ;

}
int main(){
 int n , m , x ;
 scanf("%d%d%d",&n,&m,&x) ;
   int u , v , w ;
     memset(mpt, 0x3f3f3f3f, sizeof(mpt));
 for(int i = 0 ; i < m ; i++)
 {
     scanf("%d %d %d",&u,&v,&w) ;
     mpt[u][v] = w ;
 }
     dijkstra(n , x ) ;
    for(int i=1; i<=n; i++)
        for(int j=i+1; j<=n; j++)
       swap(mpt[i][j] ,mpt[j][i]) ; // 矩阵倒置
     dijkstra(n , x) ;
     int anss = 0 ;
     for(int i = 1 ; i <= n ; i++)
    {
     anss = max(ans[i] , anss) ;
    }
        cout << anss << endl ;
}
佛洛依德
for(int k = 1 ; k <= n ; k++)
    for(int i = 1 ; i<= n ; i++)
    for(int j = 1 ; j <= n ; j++)
    mpt[i][j] = min(mpt[i][k] + mpt[k][j] , mpt[i][j]) ;
} }
K条免费路径求最短路：

#include<bits/stdc++.h>
using namespace std ;
#define LL long long
#define INF 0x3f3f3f3f3f3f3f3f
 const int maxn = 1e6 + 10 ;

int vis[maxn][20] ;
int n , m , k ;
LL dis[maxn][20] ;
int head[maxn] ;
struct node{
  int to , next ;
  LL val ;
  node(){} ;
     node(int to, int nx, LL w) : to(to), next(nx), val(w) {}
 }st[maxn ] ;

 struct NODE{
   int xp , to ;
   LL w ;
   NODE(){} ;
   NODE(int t , int p , LL val){ to = t ; xp = p ; w = val ;  }
     bool operator < (const NODE &r) const
    {
        return w > r.w;
    }
 };
 int cnt ;

 void add(int u, int v, LL w)
{
    st[++cnt] = node(v, head[u], w); head[u] = cnt;
}
 void dijstra(){
  for(int i = 1 ; i <= n ; i++) for(int j = 0 ; j <= k ; j++) dis[i][j] = INF , vis[i][j] = 0 ;

  priority_queue<NODE> q ; q.push(NODE(1 ,0 , 0 )) ; dis[1][0] = 0 ;

   while(!q.empty()){
      int u = q.top().to ;
      int p = q.top().xp ;
      LL cost = q.top().w ;
      q.pop() ;
      if(vis[u][p] == 1) continue ;
      vis[u][p] = 1 ;
      dis[u][p] = cost ;
      for(int i = head[u] ; i != -1 ; i = st[i].next ){
           int v = st[i].to ;
           int c = st[i].val;
           if(dis[u][p] + c < dis[v][p] ) { dis[v][p] = dis[u][p] + c ; q.push(NODE(v, p ,dis[v][p] )) ; }
           if(p + 1 <= k && dis[u][p]< dis[v][p+1] ) { dis[v][p+1] = dis[u][p] ;  q.push(NODE(v  , p+1 , dis[v][p+1] ) ) ; }
      }
   }
 }

   void init(){
    memset(head , -1 , sizeof(head)) ;
    cnt = 0 ;
  }
int main(){
    int  t ;
    cin >> t ;
    while(t--){
             init() ;
        scanf("%d %d %d",&n,&m,&k) ;
         int u , v ;
         LL w ;
        for(int i = 0 ; i < m ; i++){
            scanf("%d%d%lld",&u,&v,&w) ;
            add(u , v , w ) ;
        }
        dijstra();
        LL ans = dis[n][k] ;
        printf("%lld\n",ans) ;
    }
  return 0 ;
}
K短路算法模板：
#include<bits/stdc++.h>
using namespace std ;
#define LL long long
#define INF 0x3f3f3f3f3f3f3f3f
 const int maxn = 1e6 + 10 ;

int vis[maxn][20] ;
int n , m , k ;
LL dis[maxn][20] ;
int head[maxn] ;
struct node{
  int to , next ;
  LL val ;
  node(){} ;
     node(int to, int nx, LL w) : to(to), next(nx), val(w) {}
 }st[maxn ] ;

 struct NODE{
   int xp , to ;
   LL w ;
   NODE(){} ;
   NODE(int t , int p , LL val){ to = t ; xp = p ; w = val ;  }
     bool operator < (const NODE &r) const
    {
        return w > r.w;
    }
 };
 int cnt ;

 void add(int u, int v, LL w)
{
    st[++cnt] = node(v, head[u], w); head[u] = cnt;
}
 void dijstra(){
  for(int i = 1 ; i <= n ; i++) for(int j = 0 ; j <= k ; j++) dis[i][j] = INF , vis[i][j] = 0 ;

  priority_queue<NODE> q ; q.push(NODE(1 ,0 , 0 )) ; dis[1][0] = 0 ;

   while(!q.empty()){
      int u = q.top().to ;
      int p = q.top().xp ;
      LL cost = q.top().w ;
      q.pop() ;
      if(vis[u][p] == 1) continue ;
      vis[u][p] = 1 ;
      dis[u][p] = cost ;
      for(int i = head[u] ; i != -1 ; i = st[i].next ){
           int v = st[i].to ;
           int c = st[i].val;
           if(dis[u][p] + c < dis[v][p] ) { dis[v][p] = dis[u][p] + c ; q.push(NODE(v, p ,dis[v][p] )) ; }
           if(p + 1 <= k && dis[u][p]< dis[v][p+1] ) { dis[v][p+1] = dis[u][p] ;  q.push(NODE(v  , p+1 , dis[v][p+1] ) ) ; }
      }
   }
 }

   void init(){
    memset(head , -1 , sizeof(head)) ;
    cnt = 0 ;
  }
int main(){
    int  t ;
    cin >> t ;
    while(t--){
             init() ;
        scanf("%d %d %d",&n,&m,&k) ;
         int u , v ;
         LL w ;
        for(int i = 0 ; i < m ; i++){
            scanf("%d%d%lld",&u,&v,&w) ;
            add(u , v , w ) ;
        }
        dijstra();
        LL ans = dis[n][k] ;
        printf("%lld\n",ans) ;
    }
  return 0 ;
}
SPFA链式前向星
/* 链式前向星SPFA最短路算法*/
#include<iostream>
#include<queue>
#include <algorithm>
#include <stdio.h>
#include<cstring>
using namespace std ;
#define INF 9999999
const int maxn = 1005000 ;
int N, M, head[maxn] ;
int dis[maxn], cnt;
int vis[maxn] ;
//int coun[maxn] ; coun数组用于判断负环
 int n , m , k ;
struct Edge
{  int cap ;
    int v,  next; // v 是去向 ， cap 是流量（权值） next就不解释了
}e[maxn];

void init()
{

    cnt = 0;
    memset(head, -1, sizeof (head));
   // memset(coun , 0 , sizeof(coun)) ; // 作用：判断负环
    memset(vis , 0 , sizeof(vis)) ;
}

void  Addedge(int x, int y, int z)
{

    e[cnt].v = y;
    e[cnt].cap = z;
    e[cnt].next = head[x];
    head[x] = cnt++;
}
 void spfa(int s){
   //  for(int i = 1 ; i <= n ; i++) dis[i] = INF , vis[i] = 0 ; 看数据范围
   queue<int>q ;
   dis[s] = 0 ;
 //  coun[s]++ ;
   q.push(s) ;
   while(!q.empty()){
      int now = q.front() ;
      q.pop() ;
      vis[now] = 0 ;
      for(int i = head[now] ; i != -1 ; i = e[i].next){
         int v = e[i].v ;
         int cost = e[i].cap ;
         if(dis[v] > dis[now] + cost){
             dis[v] = dis[now] + cost ;
             if(vis[v] == 0 ){ vis[v] = 1 ;/*coun[v]++ ; */q.push(v) ;}

         }
      }
   }
 }

 int main(){

  return 0 ;
 }
次短路算法：
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
欧拉图：
输出欧拉回路：
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;
stack<int>que;
int a[1000][1000];
int n,m;
void dfs(int x)
{
    int i;
    que.push(x);
    for(i=1;i<=n;i++)
    {
        if(a[x][i]>0)
        {
            a[x][i]=0;
            a[i][x]=0;
            dfs(i);
            break;
        }
    }
}
void fleury(int x)
{
    int i,j;
    int b;
    que.push(x);
    while(!que.empty())
    {
        b=0;
        for(i=1;i<=n;i++)
        {
            if(a[que.top()][i]>0)
            {
                b=1;
                break;
            }
        }
        if(b==0)
        {
            printf("%d ",que.top());
            que.pop();
        }
        else
        {
            int y=que.top();
            que.pop();
            dfs(y);
        }
    }
    printf("\n");
    return ;
}
int main()
{
    int i,j,p,q;
    while(scanf("%d %d",&n,&m)!=EOF)
    {
        memset(a,0,sizeof(a));
            for(j=1;j<=m;j++)
            {
                scanf("%d %d",&p,&q);
                a[p][q]=a[q][p]=1;
            }
        int num=0;
        int start=1;
        int degree=0;
        for(i=1;i<=n;i++)
        {
            degree=0;
            for(j=1;j<=n;j++)
            {
                degree+=a[i][j];
            }
            if(degree%2==1)
            {
                start=i;
                num++;
            }
        }
        if(num==0||num==2)
        {
            fleury(start);
        }
        else
        {
            printf("NO Eular path\n");
        }
        while(!que.empty())
        {
            que.pop();
        }
    }
    return 0;
}
生成树：
最小生成树：
kruskal算法：
using namespace std ;
int par[100000 + 10] ;
int find(int x)
{
    int r=x;
    while(pre[r]!=r)
    r=pre[r];//找到他的前导结点
   int i=x,j;
    while(i!=r)//路径压缩算法
    {
        j=pre[i];//记录x的前导结点
        pre[i]=r;//将i的前导结点设置为r根节点
        i=j;
    }

    return r;
}
int a , b ,c ;
}arr[1000000];
bool cmp(node a , node b ) {
 return a.c < b.c ;
}
int cnt = 0 ;
void init(int n){
    cnt = 0 ;
 for(int i = 1 ; i <= n ; i++){
    par[i] = i ;
 }
}
void add(int u , int v , int w){
  arr[cnt].a = u , arr[cnt].b = v ;
  arr[cnt++].c = w ;
}
prime算法：
#define INF 999999999
using namespace std ;
 int pre[100000] ;
 int mpt[1000][1000] ;
 int cost[10000]  ;
  int n ;
 int prime(){
 for(int i = 1; i <= n; i++)
    cost[i] = mpt[1][i];
  int min;
  bool visited[n + 1];// index begin from 1 not 0
  int ans = 0;
  memset(visited, false, sizeof(visited));
  cost[1] = 0;
  visited[1] = true;
  for(int i = 1; i < n; ++i)//loop N - 1 times
  {
    min = INF;
    int k;
    for(int j = 1; j <= n; ++j)// find the minimun edge between two edge set
    {
      if(!visited[j] && min > cost[j])
      {
        min = cost[j];
        k = j;
      }
    }
    visited[k] = true;
    ans = ans + min ;
    for(int j = 1; j <= n; ++j)// update the array of lowcost
    {
      if(!visited[j] && cost[j] > mpt[k][j])
        cost[j] = mpt[k][j];
    }
  }
  cout <<ans << endl ;

}
次小生成树之kruskal：
#include<bits/stdc++.h>
using namespace std ;
const int maxn = 10500;
const int INF = 0x3f3f3f3f;
const double Exp = 1e-10;
struct node
{
    int x, y, w;

};
bool cmp (node a, node b)
{
    return a.w < b.w;
}
node stu[maxn];
int v, e, father[maxn], path[maxn];

void init ()
{
    for (int i=0; i<=v; i++)
        father[i] = i;
}

int find (int x)
{
    if (father[x] != x)
        father[x] = find(father[x]);
    return father[x];
}
int kruskal ()
{
    int i, j, num = 0;
    for (i=0,j=1; i<e; i++)
    {
        int px = find (stu[i].x);
        int py = find (stu[i].y);
        if (px != py)
        {
            num += stu[i].w;
            path[j++] = i;
            father[px] = py;
        }
    }
    int ans = 0;
    for (i=1; i<=v; i++)
        if (father[i] == i)
            ans ++;
    if (ans == 1)
        return num;
    return INF;
}
int smst (int x)
{
    int i, num = 0;
    for (i=0; i<e; i++)
    {
        int px = find(stu[i].x);
        int py = find(stu[i].y);
        if (px != py && i != x)
        {
            num += stu[i].w;
            father[px] = py;
        }
    }
    int ans = 0;
    for (i=1; i<=v; i++)
        if (father[i] == i)
            ans ++;
    if (ans == 1)
        return num;
    return INF;
}
int main ()
{
    int t, l = 1;
    scanf ("%d", &t);
    while (t --)
    {
        scanf ("%d %d", &v, &e);
        for (int i=0; i<e; i++)
            scanf ("%d %d %d", &stu[i].x, &stu[i].y, &stu[i].w);
        sort (stu, stu+e, cmp);
        int num1 , num2;
        num1 = num2 = INF;
        init ();
        num1 = kruskal();  ///最小生成树
        for (int i=1; i<v; i++)
        {
            init ();
            num2 = min (num2, smst(path[i]));
        }
        if (num1 == INF)
            printf ("Case #%d : No way\n", l++);
        else if (num2 == INF)
            printf ("Case #%d : No second way\n", l++);
        else
           printf ("Case #%d : %d\n", l++ , num2);

         /*   if(num1 == num2) cout << "Not Unique!" <<endl ;
            else cout << num1 << endl ;
          */
    }
    return 0;
}.
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
最小树形图：
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
二：
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
网络流：
EK算法模板：
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
#include<cstring>
#include<string>
/* 最大流 Ek算法
复杂度： O（n*m^2）
适合稀疏图， 不适合稠密图
*/
using namespace std;
 const int maxn = 220 ;
 const int INF = 0x7f7f7f7f;
int G[maxn][maxn] , flow[maxn] , pre[maxn] ; /// G 存图 ，flow描述从原点到当前点的容量 ， pre标记上一步的曾广路是哪一条链
int n , m ;  /// 这道题 m 为点 ， n 为边
queue<int> q;
 int BFS(int s , int t){  /// 作用是找曾广路
       while(!q.empty()) q.pop() ;
       memset(pre , -1 , sizeof(pre)) ;
       pre[s] = 0 ; flow[s] = INF ;
       q.push(s) ;
       while(!q.empty()){
        int  p = q.front() ;
        q.pop() ;
        if(p == t) break ; //走到了汇点

        for(int u = 1 ; u <= n ; u++){
            if(u!= s && G[p][u] >0 && pre[u] == -1) {
                pre[u] = p ;
                flow[u] = min(flow[p] , G[p][u]) ; ///当前节点上一段的流量和下一段的流量的最小值
                q.push(u)  ;
            }
        }
       }
       if(pre[t] == -1 ) return -1 ;
       return flow[t] ;  /// 返回曾广路径中的流量最小值
 }
 int EK(int s , int t){  /// 传入源点和汇点
   int delta = 0 , tot = 0 ;///tot记录最大流的值是多少 ， delta记录这个图的曾广路的流量
   while(1){
    delta = BFS(s , t) ;/// 这里就是反复的对这个图BFS找曾广路，直到找不到为止
    if(delta == -1) break ;
    int p = t ;   /// 从曾广路开始往后退
    while(p != s){
        G[pre[p]][p] -= delta ;  ///正向边减去流量
        G[p][pre[p]] += delta ;  ///反向边加上
        p = pre[p] ;
    }
    tot += delta ;
   }
   return tot ;
 }

int main(){
int u , v ,w  ;
 while(scanf("%d%d",&m,&n) != EOF){
     memset(G , 0 , sizeof(G)) ;
     memset(flow , 0 , sizeof(flow)) ;
    for(int i = 0 ; i <m ; i++){
        scanf("%d%d%d",&u,&v,&w) ;
        G[u][v] += w ;  /// 这里是构图，如果有重边的话就相当于累加它的容量
    }
    printf("%d\n",EK(1 , n ) ) ;
 }
}
/*
自测样例：
6 5
1 2 6
1 3 7
1 4 8
2 5 10
3 5 10
4 5 10
21
5 4
1 2 8
2 4 10
2 3 100
3 4 2
1 3 7
10
*/
最大流dinic：
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
最小费用最大流之一：
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
之二：
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
const int maxm = 1000200;
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
连通图：
#include <string.h>
#include <iostream>
#include <algorithm>
#include<cstdio>
using namespace std;
/*
Tarjan算法
复杂度O(N+M)
*/
/// 除了solve和主函数外才是该算法模板
const int maxn = 2e5 + 10; // 点数
const int maxm = 2e5 + 10; // 边数

int head[maxn], tot;
int Low[maxn], DFN[maxn],Stack[maxn],Belong[maxn];//Belong数组的值是1~scc
int Index, top;
int scc;//强连通分量的个数
bool Instack[maxn];
int num[maxn];//各个强连通分量包含点的个数，数组编号1~scc
//num数组不一定需要，结合实际情况
int n ;
struct Edge
{
    int to,next;
}edge[maxn];

void addedge(int u,int v)
{
    edge[tot].to = v;edge[tot].next = head[u];head[u] = tot++;
}
void Tarjan(int u)
{
    int v;
    Low[u] = DFN[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    for(int i = head[u];i != -1;i = edge[i].next)
    {
        v = edge[i].to;      // 去向
        if(!DFN[v])
        {
            Tarjan(v);
            if(Low[u] > Low[v])
                  Low[u] = Low[v];
        }
        else if(Instack[v] && Low[u] > DFN[v])
            Low[u] = DFN[v];
    }
    if(Low[u] == DFN[u]) // 在这里可以使用num数组，记录路径
    {
        scc++;
        do
        {
            v = Stack[--top];
            Belong[v] = scc;  // 这就是为什么belong【】数组里面的值为 1 - scc 的原因
            Instack[v] = false;
        }
        while( v!= u);
    }
}
int in[maxn],out[maxn];
int finda[100000] ;
void solve(int N)
{
    memset(DFN,0,sizeof(DFN));
    memset(Instack,false,sizeof(Instack));
    Index = scc = top = 0;
    for(int i = 1;i <= N;i++)
        if(!DFN[i]) // 如果图有2个， 就会一把2个图遍历完，但通常情况下就只需要一遍
           Tarjan(i);
       //     cout << "LOW = " ;
        for(int i = 1 ; i <= N ; i++){
                finda[Belong[i]] ++ ;
        }  //   cout << endl ;
    //    cout << "BElong = " ;

        int ans = 0 ;
        for(int i = 0 ; i <= scc ; i++){
           if(finda[i]  > 1  ) ans += finda[i] * (finda[i] - 1 ) / 2 ;
        }
        cout << ans << endl ;


               return  ;
}
void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
}
int main()
{   int n , m ;
cin >> n >> m  ;
int u , v   ;
init() ;
for(int i = 0 ; i < m ; i++){
    scanf("%d%d",&u , &v) ;
    addedge(u , v) ;
}

        solve(n);

    return 0;
}
无向图求桥：
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
}*/

有向图求桥：
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
黑科技：
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

搜索：
极大极小值搜索：
题意：
Alice和Bob玩游戏，在一个4x4 的方格上
每个人每次选择2x2的区域将里面的四个值求和加到最后的分数当中(两个人共用一个分数)，
然后逆时针翻转它们，
Alice想要分数尽量大Bob想要分数尽量小
两个人每次的选择都是最优的，求最后的分数
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 1000000007;
const int inf = unsigned(-1) >> 2;
const int maxn = 1e5 + 5;

using namespace std;

int sum, winx, winy;
int k;
int Map[5][5];

int rote(int x, int y) {
    swap(Map[x][y], Map[x + 1][y]);
    swap(Map[x][y + 1], Map[x + 1][y + 1]);
    swap(Map[x][y], Map[x + 1][y + 1]);
    return Map[x][y] + Map[x + 1][y] + Map[x][y + 1] + Map[x + 1][y + 1];
}

void rerote(int x, int y) {
    swap(Map[x][y], Map[x + 1][y + 1]);
    swap(Map[x][y + 1], Map[x + 1][y + 1]);
    swap(Map[x][y], Map[x + 1][y]);
}

int DFS(int sum, int dep, int alpha, int beta) {
    if(dep == 2 * k) return sum;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            int tmp = DFS(sum + rote(i, j), dep + 1, alpha, beta);
            rerote(i, j);
            if(dep & 1)
                beta = min(beta, tmp);
            else
                alpha = max(alpha, tmp);
            if(beta <= alpha)
                return dep & 1 ? beta : alpha;
        }
    }
    return dep & 1 ? beta : alpha;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while(t--) {
        cin >> k;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                cin >> Map[i][j];
            }
        }
        cout << DFS(sum, 0, -inf, inf) << endl;
    }
    return 0;
}
数位dp不要62：
#include<bits/stdc++.h>
using namespace std ;
int a, b,shu[20],dp[20][2];
int dfs(int len, bool if6, bool shangxian)
{
    if (len == 0)
        return 1;
    if (!shangxian && dp[len][if6])
        return dp[len][if6];
    int cnt = 0, maxx = (shangxian ? shu[len] : 9);
    for (int i = 0; i <= maxx; i++)
    {
        if (i == 4 || if6 && i == 2)
            continue;
        cnt += dfs(len - 1, i == 6, shangxian && i == maxx);
    }
    return shangxian ? cnt : dp[len][if6] = cnt;
}

int solve(int x)
{
    memset(shu, 0, sizeof(shu));
    int k = 0;
    while (x)
    {
        shu[++k] = x % 10;
        x /= 10;
    }
    return dfs(k, false, true);
}

int main()
{
    scanf("%d%d", &a, &b);
    printf("%d\n", solve(b) - solve(a - 1));


    return 0;
}
