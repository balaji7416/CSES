#include <bits/stdc++.h>
using namespace std;

#define int long long

/*
    Problem 1641: Sum of Three Values
    Pattern: two pointer + sorting
    Time: O(N^2) Space: O(N)
    Link: https://cses.fi/problemset/task/1641
*/

/* Idea:
    Sort (value, index) pairs so we can use two pointers.

    For each element i (acting as the first number),
    reduce the problem to a two-sum with target = target - pairs[i].first.

    Run two pointers (l, r) on the sorted array to find two numbers
    whose sum equals the required value. Skip positions equal to i
    so the same element isn't reused.

    If found, print the original indices stored in the pairs.

    Time Complexity: O(n^2)
    - n choices for first element
    - O(n) two-pointer scan for each

    Space Complexity: O(n)
*/

int n,
    target;
vector<int> nums;

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
        auto &[n1, idx1] = pairs[i];
        int req = target - n1;
        int l = 0, r = n - 1;
        while (l < r)
        {
            if (l == i)
            {
                l++;
                continue;
            }
            if (r == i)
            {
                r--;
                continue;
            }

            auto &[n2, idx2] = pairs[l];
            auto &[n3, idx3] = pairs[r];

            if (n2 + n3 == req)
            {
                cout << idx1 + 1 << " " << idx2 + 1 << " " << idx3 + 1 << endl;
                return;
            }
            else if (n2 + n3 < req)
            {
                l++;
            }
            else
            {
                r--;
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