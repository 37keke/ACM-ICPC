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
