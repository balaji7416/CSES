#include <bits/stdc++.h>
using namespace std;

#define int long long
int n, target;
vector<int> nums;

/*
    Problem 1642: Sum of Four Values
    Pattern: two pointer + sorting
    Time: O(N^3) Space: O(N)
    Link: https://cses.fi/problemset/task/1642
*/

/* Idea:
    Extension of the 3-sum pattern.

    Sort (value, index) pairs. Fix two elements (i, j), then use
    two pointers (l, r) on the remaining sorted part to find two
    numbers such that a[i] + a[j] + a[l] + a[r] = target.

    Sorting enables the two-pointer scan by adjusting l/r based
    on whether the current sum is smaller or larger than target.

    Time: O(n^3)  |  Space: O(n)
*/

void solve1()
{
    vector<pair<int, int>> pairs;
    for (int i = 0; i < n; i++)
    {
        pairs.push_back({nums[i], i});
    }
    sort(pairs.begin(), pairs.end());

    for (int i = 0; i < n; i++)
    {
        auto &[n0, idx0] = pairs[i];

        for (int j = i + 1; j < n; j++)
        {
            auto &[n1, idx1] = pairs[j];
            int l = j + 1,
                r = n - 1;
            while (l < r)
            {

                auto &[n2, idx2] = pairs[l];
                auto &[n3, idx3] = pairs[r];
                int sum = n0 + n1 + n2 + n3;
                if (sum == target)
                {
                    cout << idx0 + 1 << " " << idx1 + 1 << " " << idx2 + 1 << " " << idx3 + 1 << endl;
                    return;
                }
                else if (sum < target)
                {
                    l++;
                }
                else
                {
                    r--;
                }
            }
        }
    }
    cout << "IMPOSSIBLE" << endl;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin >> n >> target;
    nums.resize(n);

    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    solve1();
    return 0;
}