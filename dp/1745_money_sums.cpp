#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1745: Money Sums
    Pattern: dp (subset sum dp)
    Time: O(N*total) Space: O(N)
    Link: https://cses.fi/problemset/task/1745
*/

/*
    idea:
        dp[i] = true if there is a subset of nums that sums to i
        base case:
            dp[0] = true // sum 0 trivially possible
        transition:
            for each num x in nums,
                for each sum i from toal-x to 0,
                    if sum i is possible so is sum i+x
*/

int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);

    for (int i = 0; i < n; i++)
        cin >> nums[i];

    int total = accumulate(nums.begin(), nums.end(), 0);
    vector<bool> dp(total + 1, false);

    dp[0] = true; // sum 0 is possible

    for (int x : nums)
    {
        for (int i = total - x; i >= 0; i--)
        {
            if (dp[i])
                dp[i + x] = true;
        }
    }

    vector<int> ans;
    for (int i = 1; i <= total; i++)
    {
        if (dp[i])
            ans.push_back(i);
    }
    cout << ans.size() << endl;
    for (int x : ans)
        cout << x << " ";
    cout << endl;
    return 0;
}