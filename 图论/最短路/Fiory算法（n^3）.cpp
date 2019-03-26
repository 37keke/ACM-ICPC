for(int k = 1 ; k <= n ; k++)
    for(int i = 1 ; i<= n ; i++)
    for(int j = 1 ; j <= n ; j++)
  //  mpt[i][j] = min(mpt[i][k] + mpt[k][j] , mpt[i][j]) ; // 求解任意两点最短路
  // if(mpt[i][j] > mpt[i][k] + mpt[k][j] ) mpt[i][j] = mpt[i][k] + mpt[k][j] ;
  // mpt[k][i] = (mpt[k][j] && mpt[j][i])  闭包传递
} }
