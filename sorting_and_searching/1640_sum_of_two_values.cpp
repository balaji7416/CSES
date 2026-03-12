#include <bits/stdc++.h>
using namespace std;

#define int long long

/*
    Problem 1640: Sum of Two Values
    Pattern: two pointer
    Time: O(NlogN) Space: O(N)
    Link: https://cses.fi/problemset/task/1640
*/

vector<int> nums;
int n, x;

void solve1()
{
    /*unordered_map TLE 'ed LLAMMO*/
    map<int, int> mp;
    for (int i = 0; i < n; i++)
    {
        int req = x - nums[i];
        if (mp.count(req))
        {
            cout << mp[req] + 1 << " " << i + 1 << endl;
            return;
        }
        mp[nums[i]] = i;
    }

    cout << "IMPOSSIBLE" << endl;
}
void solve2()
{
    // sort + two pointer (preffered)
    vector<pair<int, int>> pairs;
    for (int i = 0; i < n; i++)
    {
        pairs.push_back({nums[i], i});
    }
    sort(pairs.begin(), pairs.end());

    int l = 0, r = n - 1;
    while (l < r)
    {
        auto [n1, idx1] = pairs[l];
        auto [n2, idx2] = pairs[r];
        int sum = n1 + n2;

        if (sum == x)
        {
            cout << idx1 + 1 << " " << idx2 + 1 << endl;
            return;
        }
        if (sum < x)
        {
            l++;
        }
        else
        {
            r--;
        }
    }
    cout << "IMPOSSIBLE" << endl;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin >> n >> x;
    nums.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    // solve1();
    solve2();
    return 0;
}