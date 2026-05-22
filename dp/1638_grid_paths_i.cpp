#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int main()
{
    int n;
    cin >> n;
    vector<string> grid(n);
    for (int i = 0; i < n; i++)
    {
        cin >> grid[i];
    }
    vector<vector<int>> dp(n, vector<int>(n, -1));
    /*
        dp[i][j] = no.of ways to reach (n-1,n-1) from i,j
    */
    auto dfs = [&](auto &&self, int i, int j)
    {
        if (i >= n || i < 0 || j >= n || j < 0)
            return 0;
        if (grid[i][j] == '*')
            return 0;
        if (i == n - 1 && j == n - 1)
            return 1;
        if (dp[i][j] != -1)
            return dp[i][j];
        return dp[i][j] = (self(self, i + 1, j) % mod + self(self, i, j + 1) % mod) % mod;
    };

    auto dfs2 = [&]() -> int
    {
        vector<vector<int>> dp(n, vector<int>(n, 0));
        /*
            dp[i][j] = no.of ways to reach (i,j) from (0,0)
        */
        dp[0][0] = grid[0][0] == '.';
        for (int i = 1; i < n; i++)
        {
            if (grid[0][i] != '*')
                dp[0][i] = dp[0][i - 1];
            if (grid[i][0] != '*')
                dp[i][0] = dp[i - 1][0];
        }
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (grid[i][j] == '*')
                    continue;

                dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % mod;
            }
        }
        return dp[n - 1][n - 1];
    };
    // int ans = dfs(dfs, 0, 0);
    int ans = dfs2();
    cout << ans << endl;
}