#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1635: Coin Combinations I
    Pattern: dp
    Time: O(n*x) Space: O(x)
    Link: https://cses.fi/problemset/task/1635
*/

const int mod = 1e9 + 7;
int main()
{
    int n, x;
    cin >> n >> x;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    vector<int> dp(x + 1, -1);
    /*
        dp[i] = no.of ways to get target sum x from curr sum as i
    */
    auto dfs = [&](auto &&self, int sum)
    {
        if (sum == x)
            return 1;
        if (sum > x)
            return 0;
        if (dp[sum] != -1)
            return dp[sum];
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            ans = (ans + self(self, sum + nums[i])) % mod;
        }
        return dp[sum] = ans;
    };
    auto dfs2 = [&]()
    {
        vector<int> dp(x + 1, 0);
        // dp[i] = no.of ways to make sum i
        dp[0] = 1;
        for (int s = 0; s <= x; s++)
        {
            for (int coin : nums)
            {
                if (s + coin <= x)
                {
                    dp[s + coin] = (dp[s + coin] + dp[s]) % mod;
                }
            }
        }
        return dp[x];
    };
    // int ans = dfs(dfs, 0);
    int ans = dfs2();
    cout << ans << endl;
    return 0;
}
