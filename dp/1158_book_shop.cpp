#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1158: Book Shop
    Pattern: dp
    Time: O(n*x) Space: O(n*x)
    Link: https://cses.fi/problemset/task/1158
*/

int main()
{
    int n, x;
    cin >> n >> x;
    vector<int> price(n), pages(n);
    for (int &i : price)
        cin >> i;
    for (int &i : pages)
        cin >> i;

    vector<vector<int>> dp(n, vector<int>(x + 1, -1));
    auto dfs = [&](auto &&self, int i, int c)
    {
        if (i == n)
            return 0;
        if (dp[i][c] != -1)
            return dp[i][c];
        int ans = self(self, i + 1, c);
        if (c + price[i] <= x)
            ans = max(ans, pages[i] + self(self, i + 1, c + price[i]));
        return dp[i][c] = ans;
    };
    auto dfs2 = [&]()
    {
        vector<int> dp(x + 1, 0);
        // dp[i] = max pages that can be obtained with price i
        for (int i = 0; i < n; i++)
        {
            for (int j = x; j >= price[i]; j--)
            {
                dp[j] = max(dp[j], dp[j - price[i]] + pages[i]);
            }
        }
        return dp[x];
    };

    // int ans = dfs(dfs, 0, 0);
    int ans = dfs2();
    cout << ans << endl;
}