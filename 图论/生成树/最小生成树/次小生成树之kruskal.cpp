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
