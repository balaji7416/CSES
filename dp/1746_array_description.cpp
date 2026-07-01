#include <bits/stdc++.h>
using namespace std;
#define int long long
int32_t main()
{
    int n, m;
    cin >> n >> m;

    int mod = 1e9 + 7;

    vector<int> nums(n);
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    vector<vector<int>> dp(n, vector<int>(m + 1, -1));
    /*
        dp[i][x] = no.of valid arrays from idx i to n-1 if value at idx i is x
    */

    auto dfs = [&](auto &&self, int i, int x) -> int
    {
        if (nums[i] != 0 && nums[i] != x)
            return 0;
        if (x < 1 || x > m)
            return 0;
        if (i == n - 1)
            return 1;
        if (dp[i][x] != -1)
            return dp[i][x];
        return dp[i][x] = (self(self, i + 1, x) % mod + self(self, i + 1, x - 1) % mod + self(self, i + 1, x + 1) % mod) % mod;
    };
    auto dfs2 = [&]()
    {
        vector<vector<int>> dp(n, vector<int>(m + 1, 0));
        /*
            no.of valid arrays ending at idx i if nums[i] =
        */
        if (nums[0] != 0)
            dp[0][nums[0]] = 1;
        for (int i = 1; i <= m; i++)
            dp[0][i] = 1;
        for (int i = 1; i < n; i++)
        {
            for (int x = 1; x <= m; x++)
            {
                dp[i][x] = dp[i - 1][x] + (x - 1 >= 0 ? dp[i - 1][x - 1] : 0) + (x + 1 <= m ? dp[i - 1][x + 1] : 0);
            }
        }
        };

    int ans = 0;
    if (nums[0] != 0)
        ans = dfs(dfs, 0, nums[0]) % mod;
    else
    {
        for (int i = 1; i <= m; i++)
            ans = (ans + dfs(dfs, 0, i)) % mod;
    }
    cout << ans << endl;
}