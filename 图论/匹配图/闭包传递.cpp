for (int k=1;k<=n;k++)//传递闭包
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            arr[k][i] = (arr[k][j] && arr[j][i])
