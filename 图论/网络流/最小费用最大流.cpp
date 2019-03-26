/*
给定一个图，问从1到n，再从n回到1，要求边不重复地走，最短的路是多少。
分析：
每条边只能用一次，所以容量是1, 费用即原图的边权，添加源点ST=0, ST向1连一条边，容量为2（1到n，再n到1,相当于从1到n两次），费用为0,（汇点可以不添加，把n直接看作汇点是可以的）
　　每次在残余网络中找最小费用增广路（spfa找最短路）并增广、修改残余网络，直到不存在残余网络为止。
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define mpair make_pair
#define pii pair<int,int>
#define MM(a,b) memset(a,b,sizeof(a));
typedef long long lld;
typedef unsigned long long u64;
template<class T> bool up_max(T& a,const T& b){return b>a? a=b,1 : 0;}
template<class T> bool up_min(T& a,const T& b){return b<a? a=b,1 : 0;}
#define maxn 1010
const int inf= 2100000000;

int n,m;
int ST, ED;
int top, head[maxn];
struct Edge{
    int u, v, c, f, next; ///c: cost,  f: flow;
    Edge(){}
    Edge(int u, int v, int c, int f, int next): u(u),v(v),c(c),f(f),next(next){}
} edge[40080];
void Addedge(int u,int v,int c,int f){
    edge[top]= Edge( u, v, c, f, head[u] ); head[u]= top++;
    edge[top]= Edge( v, u, -c, 0, head[v] ); head[v]= top++;
}

bool vis[maxn];
int pre[maxn]; /// record the pre-edge's index, for modifying the remain-network;
int que[maxn+10];
int dis[maxn], cnt[maxn];
bool spfa(){
    for(int i=ST;i<=ED;++i) dis[i]= inf, cnt[i]=vis[i]= 0, pre[i]= -1;
    int h= 0, tail= 0;
    que[tail++]= ST;
    dis[ST]= 0;
    vis[ST]= 1, cnt[ST]= 1;
    while( h!=tail ){  /// h!=tail; because it it circle-queue;
        int u= que[h++];
        if( h==maxn ) h= 0;
        vis[u]= 0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v= edge[i].v;
            if( edge[i].f>0 && up_min( dis[v], dis[u]+edge[i].c ) ){
                pre[v]= i; ///
                if( !vis[v] ){
                    vis[v]= 1;
                    ++cnt[v];
                    que[tail++]= v;
                    if( tail==maxn ) tail= 0;
                    if( cnt[v]>ED ) return 0;
                }
            }
        }
    }
    if( pre[ED] == -1 ) return 0;
    return 1;
}

int solve(){
    int ret= 0, mf=0;
    while( spfa() ){
        int t= inf;
        for(int i=pre[ED];i!=-1;i= pre[ edge[i].u ] )
            up_min( t, edge[i].f );  /// t == 1 (must);
        for(int i=pre[ED];i!=-1;i= pre[ edge[i].u ] ){
            edge[ i ].f -= t;
            edge[ i^1 ].f += t; /// i^1;
        }
        ret+= dis[ED];
    }
    return ret;
}

void build_graph(){
    top= 0;
    fill( head, head+1+n, -1 );
    while(m--){
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        Addedge( u, v, c, 1 );
        Addedge( v, u, c, 1 );
    }
    ST= 0, ED= n;
    Addedge( ST, 1, 0, 2 );
}

int main(){
    //freopen("poj2135.in","r",stdin);
    while( cin>>n>>m ){
        build_graph();
        cout<< solve() <<endl;
    }
}
