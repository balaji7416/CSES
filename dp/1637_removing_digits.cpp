#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1637: Removing Digits
    Pattern: dp
    Time: O(nlogn) Space: O(n)
    Link: https://cses.fi/problemset/task/1637
*/

int main()
{
    int n;
    cin >> n;

    const int INF = 1e9;
    vector<int> dp(n + 1, -1);
    /*
        dp[i] = min no.of steps required to make i zero
    */

    auto dfs = [&](auto &&self, int i)
    {
        if (i == 0)
            return 0;

        if (dp[i] != -1)
            return dp[i];
        int x = i;
        int ans = INF;
        while (x > 0)
        {
            int d = x % 10;
            x /= 10;
            if (d == 0)
                continue;
            ans = min(ans, 1 + self(self, i - d));
        }
        return dp[i] = ans;
    };
    auto dfs2 = [&]()
    {
        vector<int> dp(n + 1, INF);
        dp[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            int x = i;
            while (x > 0)
            {
                int d = x % 10;
                x /= 10;
                dp[i] = min(dp[i], 1 + dp[i - d]);
            }
        }
        return dp[n];
    };
    // int ans = dfs(dfs, n);
    int ans = dfs2();
    cout << ans << endl;

    return 0;
}