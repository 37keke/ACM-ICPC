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
