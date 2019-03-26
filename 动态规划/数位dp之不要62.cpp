#include<bits/stdc++.h>
using namespace std ; 
int a, b,shu[20],dp[20][2];
int dfs(int len, bool if6, bool shangxian)
{
    if (len == 0)
        return 1;
    if (!shangxian && dp[len][if6])
        return dp[len][if6];
    int cnt = 0, maxx = (shangxian ? shu[len] : 9);
    for (int i = 0; i <= maxx; i++)
    {
        if (i == 4 || if6 && i == 2)
            continue;
        cnt += dfs(len - 1, i == 6, shangxian && i == maxx);
    }
    return shangxian ? cnt : dp[len][if6] = cnt;
}

int solve(int x)
{
    memset(shu, 0, sizeof(shu));
    int k = 0;
    while (x)
    {
        shu[++k] = x % 10;
        x /= 10;
    }
    return dfs(k, false, true);
}

int main()
{
    scanf("%d%d", &a, &b);
    printf("%d\n", solve(b) - solve(a - 1));


    return 0;
}
