#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
#include<iostream>
using namespace std;

int n;
int head[3010];

struct node{
    int to;
    int c;
    int next;
}edge[200000];

struct ver{
    int x;
    int dis;
    bool operator < (const ver& t) const{
        return dis>t.dis;
    }
};

priority_queue<ver> q;

int  prime()
{
    int res = 0;
    //init a collection
    int dis[3010];
    int v_j;
    int vis[3010];
    for(int i = 0; i<n; i++) {
        dis[i] = 0x3f3f3f;
    }
   // q.push(0);
    vis[1] = 1;
    for(int i = head[1]; i!= -1; i = edge[i].next) {
        v_j = edge[i].to;
        dis[v_j] = edge[i].c;
        q.push(ver{v_j,dis[v_j]});
    }
    dis[1] = 0x3f3f3f;
    for(int i = 1; i<n; i++) {
        int temp_j = 0;
        int min_c = 0x3f3f3f;
        //找出dis中的最小值的坐标，这里体现log n
        ver t_ver = q.top();
        q.pop();
        temp_j = t_ver.x;
        res += t_ver.dis;
        vis[temp_j] = 1;
        for(int j = head[temp_j]; j!=-1; j = edge[j].next) {
            v_j = edge[j].to;
            if(!vis[v_j] && dis[v_j] > edge[j].c) {
                dis[v_j] = edge[j].c;
                q.push(ver{v_j,dis[v_j]});
            }
        }
    }
    return res;
}

void init() {
    for(int i = 0;i<n;i++) {
        head[i] = -1 ;
    }
}

int main()
{
    int m;
    while(~scanf("%d%d",&n,&m)) {
        init();
        int u,v,c;
        int k = 0;
        for(int i = 0;i<m;i++) {
            scanf("%d%d%d",&u,&v,&c);
            edge[k].next = head[u];
            edge[k].to = v;
            edge[k].c = c;
            head[u] = k;
            k++;
            edge[k].next = head[v];
            edge[k].to = u;
            edge[k].c = c;
            head[v] = k;
            k++;
        }
        cout<<prime()<<endl;
    }
}
