#include <bits/stdc++.h>
using namespace std;

#define int long long

/*
    Problem 1660: Subarray Sum II
    Pattern: prefix sum + hashing
    Time: O(N) Space: O(N)
    Link: https://cses.fi/problemset/task/1661
 */

/* Idea:
    Use prefix sums + hashmap to count subarrays with sum = x.

    Let prefix[r] be the sum of the first r elements. For a subarray
    ending at r to have sum x, we need a previous prefix value:

        prefix[l] = prefix[r] - x

    Store frequencies of prefix sums in a hashmap while iterating.
    For each r, add how many times (prefix[r] - x) appeared before.

    Time: O(n) average
    Space: O(n)


    #note if all nums are positive we can use sliding window isntead
    here's the sample code:
    int l = 0;
l   ong long sum = 0, ans = 0;

for (int r = 0; r < n; r++) {
    sum += nums[r];

    while (sum > x) {
        sum -= nums[l];
        l++;
    }

    if (sum == x) ans++;
}

cout << ans << endl;

*/

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

vector<int> nums;
int n, x;

void solve1()
{
    /*method 1: works for both negative and positive number*/
    vector<int> prefix(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        prefix[i] = prefix[i - 1] + nums[i - 1];
    }
    unordered_map<int, int, custom_hash> mp;
    // mp.reserve(1 << 20); // to prevent rehashing
    // mp.max_load_factor(0.25);
    // map<int, int> mp;
    int ans = 0;
    for (int r = 0; r <= n; r++)
    {
        int req = prefix[r] - x;
        ans += mp[req];
        mp[prefix[r]]++;
    }
    cout << ans << endl;
}

void solve2()
{
    /*works if the nums are positive (preferred if no nums are negative)*/
    int l = 0, sum = 0;
    int ans = 0;
    for (int r = 0; r < n; r++)
    {
        sum += nums[r];
        while (sum > x)
        {
            sum -= nums[l];
            l++;
        }
        if (sum == x)
        {
            ans++;
        }
    }
    cout << ans << endl;
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
    solve1();
    // solve2();
    return 0;
}