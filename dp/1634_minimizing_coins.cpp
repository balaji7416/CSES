#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1634: Minimizing Coins
    Pattern: dp
    Time: O(n*x) Space: O(x)
    Link: https://cses.fi/problemset/task/1634
*/

int main()
{
    int n, x;
    cin >> n >> x;

    vector<int> nums(n);
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    const int inf = 1e9;
    vector<int> dp(x + 1, -1);
    /*
        dp[i] = min coins needed to make sum x with current sum i
    */
    auto dfs = [&](auto &&self, int sum)
    {
        if (sum == x)
            return 0;
        if (dp[sum] != -1)
            return dp[sum];
        int ans = inf;
        for (int i = 0; i < n; i++)
        {
            if (sum + nums[i] <= x)
            {
                int sub = self(self, sum + nums[i]);
                if (sub != inf)
                    ans = min(ans, 1 + sub);
            }
        }
        return dp[sum] = ans;
    };
    auto dfs2 = [&]()
    {
        vector<int> dp(x + 1, inf);
        /*
            dp[i] = min coins needed to make sum x with current sum i
        */
        dp[x] = 0;
        for (int i = x - 1; i >= 0; i--)
        {
            for (int coin : nums)
            {
                if (i + coin <= x)
                {
                    dp[i] = min(dp[i], 1 + dp[i + coin]);
                }
            }
        }
        return dp[0];
    };
    // int ans = dfs(dfs, 0);
    int ans = dfs2();
    ans == inf ? cout << -1 << endl : cout << ans << endl;
}