#include<bits/stdc++.h>
using namespace std;
 const int maxn = 100 ;
 int arr[100][100] ;
  int vis[maxn][maxn] = {0};
     int r , l  ;
  int ans = 0 ;
  int dx[] = {0,0,1,-1} ;
  int dy[]=  {1,-1,0,0} ;
  struct node{
 int x , y ;
 int cost ;
  };
  void BFS(){
   queue<node> q ;
   vis[0][0] = 1 ;
   node s1 , s2 , s3 ;
   s1.cost = 0 ; s1.x = 0 ; s1.y = 0 ;
   q.push(s1) ;
   while(!q.empty()){
     s2 = q.front() ;
    q.pop() ;
    int n = s2.x ; int  m = s2.y ;
    for(int i = 0 ; i < 4 ; i++)
    {
        if(arr[n + dx[i]][m + dy[i]] == 1 && vis[n + dx[i]][m + dy[i]] == 0 && n + dx[i] < r && m + dy[i] < l && n + dx[i] >= 0 && m + dy[i] >= 0   )
        {
            vis[n + dx[i]][m+dy[i]] = 1 ; s3.cost = s2.cost + 1  ; s3.x = n + dx[i] ; s3.y = m + dy[i] ;
            q.push(s3) ;
            if(n + dx[i] == r - 1 && m + dy[i] == l - 1 ) {ans = s3.cost ; return ;  }
        }
    }
   }

  }
int main(){

   cin >> r >> l ;
   for(int i = 0 ; i < r ; i ++)
   {
       for(int j = 0; j < l ; j++)
       {
           cin >> arr[i][j] ;
       }
   }
    BFS();
   cout << ans << endl ;
   return  0 ;
}
