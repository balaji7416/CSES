#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

/*
    Problem 1633: dice combinations
    pattern: dp
    Time: O(n) Space: O(n)
*/

int32_t main()
{
    int n;
    cin >> n;

    vector<int> dp(n, -1);
    /*
        dp[i] = no.of ways to get sum n from cur sum as i
    */
    auto dfs = [&](auto &&self, int sum)
    {
        if (sum == n)
            return 1;
        if (sum > n)
            return 0;
        if (dp[sum] != -1)
            return dp[sum];
        int ans = 0;
        for (int i = 1; i <= 6; i++)
        {
            ans = (ans + self(self, sum + i)) % mod;
        }
        return dp[sum] = ans;
    };
    auto dfs2 = [&]()
    {
        vector<int> dp(n + 1);
        /*
            dp[i] = no.of ways to get sum i
        */
        dp[0] = 1;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= 6; j++)
            {
                if (i - j >= 0)
                    dp[i] = (dp[i] + dp[i - j]) % mod;
            }
        }
        return dp[n];
    };
    // int ans = dfs(dfs,0);
    int ans = dfs2();
    cout << ans << endl;
}