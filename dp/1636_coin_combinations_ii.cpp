#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

/*
    Problem 1636: Coin Combinations II
    Pattern: dp
    Time: O(n*x) Space: O(n*x)
    Link: https://cses.fi/problemset/task/1636
*/

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, x;
    cin >> n >> x;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    vector<vector<int>> dp(n, vector<int>(x + 1, -1));
    /*
        dp[i][s] = no.of ways to make target sum x from idx i and with curr sum as s
    */

    // 1. this method will TLE in CSES
    auto dfs = [&](auto &&self, int idx, int sum) -> int
    {
        if (sum == x)
            return 1;
        if (sum > x || idx >= n)
            return 0;
        if (dp[idx][sum] != -1)
            return dp[idx][sum];
        int ans = 0;
        for (int i = idx; i < n; i++)
        {
            ans = (ans + self(self, i, sum + nums[i])) % mod;
        }
        return dp[idx][sum] = ans;
    };

    // this will TLE in CSES
    auto dfs2 = [&](auto &&self, int i, int sum) -> int
    {
        if (sum == x)
            return 1;
        if (sum > x || i >= n)
            return 0;

        if (dp[i][sum] != -1)
            return dp[i][sum];

        return dp[i][sum] = ((self(self, i, sum + nums[i]) % mod) + (self(self, i + 1, sum)) % mod) % mod;
    };

    auto dfs3 = [&]()
    {
        vector<int> dp(x + 1, 0);
        // dp[i] = no.of ways to make target sum i
        dp[0] = 1;
        for (int coin : nums)
        {
            for (int s = coin; s <= x; s++)
            {
                dp[s] = (dp[s - coin] + dp[s]) % mod;
            }
        }
        return dp[x];
    };

    // int ans = dfs(dfs, 0, 0);
    // int ans = dfs2(dfs2, 0, 0);
    int ans = dfs3();
    cout << ans << endl;

    return 0;
}