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
