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
