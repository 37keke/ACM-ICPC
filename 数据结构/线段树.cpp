#include<bits/stdc++.h>
using namespace std ;
 const int maxn = 100000 ;
 struct node{
  int r , l , v , add ;
 }s[maxn + 5 ] ;
 int arr[maxn] ;
void build(int r , int l , int rt){
    s[rt].add = 0 ;
 if(r == l ) {
    s[rt].v = arr[l] ;
 }
 else {
    int mid = (r + l ) / 2 ;
    build(r , mid , rt*2) ;
    build(mid+1 , l , rt*2 + 1) ;
    s[rt].v = max(s[rt*2].v , s[rt*2+1].v ) ;
  }
}

void pushdowm(int rt){
 if(s[rt].add != 0)
 {
     s[rt*2].add += s[rt].add ;
     s[rt*2+1].add += s[rt].add ;
     s[rt*2].v += s[rt].add ;
     s[rt*2+1].v += s[rt].add ;
     s[rt].add = 0  ;
 }
}
  // [nstart, nend]: 当前节点所表示的区间
 // [qstart, qend]: 此次查询的区间
int query(int root, int nstart, int nend, int qstart, int qend)
{
      //查询区间和当前节点区间没有交集
      if(qstart > nend || qend < nstart)
          return 0;
      //当前节点区间包含在查询区间内
      if(qstart <= nstart && qend >= nend)
          return s[root].v;
      //分别从左右子树查询，返回两者查询结果的较小值
     pushdowm(root); //----延迟标志域向下传递
      int mid = (nstart + nend) / 2;
      return max(query(root*2, nstart, mid, qstart, qend), query(root*2+1, mid + 1, nend, qstart, qend));

  }

 void update(int root, int nstart, int nend, int ustart, int uend, int addVal)  // 区间更新
  {
      //更新区间和当前节点区间没有交集
      if(ustart > nend || uend < nstart)
          return ;
      //当前节点区间包含在更新区间内
      if(ustart <= nstart && uend >= nend)
      {
         s[root].add += addVal ;
          s[root].v += addVal  ;
         return ;
     }
     pushdowm(root); //延迟标记向下传递
     //更新左右孩子节点
    int mid = (nstart + nend) / 2;
     update(root*2, nstart, mid, ustart, uend, addVal);
     update(root*2+1, mid+1, nend, ustart, uend, addVal);
     //根据左右子树的值回溯更新当前节点的值
    s[root].v = max(s[root*2].v , s[root*2+1].v);
  }
  int main(){
     int n ;
     cin >> n ;
     for(int i = 1 ; i<= n ; i++)
        cin >> arr[i] ;
     build(1 , n , 1) ;
     int x , y ;
     cin >> x >> y ;
     cout << query(1 , 1 , n , x , y ) << endl ;
  }
