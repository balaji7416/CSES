#include <bits/stdc++.h>
using namespace std;

#define int long long

/*
    Problem 1662: Subarray Divisibility
    Pattern: prefix sum + hashing
    Time: O(N) Space: O(N)
    Link: https://cses.fi/problemset/task/1662
*/

/* Idea:
    subarray sum can be written as prefix[r+1]-prefix[l]
    now we want the subarray divisible by n
    so do that,
    (prefix[r+1] - prefix[l]) % n = 0
    => prefix[r+1] % n = prefix[l] % n

    so we we just move r from 0 to n in prefix sum array
    and check how many prefix[r+1]%n are found before
    and add that count to ans and add this prefix[r+1]%n to map

    Time: O(n) average
    Space: O(n)
*/

vector<int> nums;
int n;
void solve1()
{
    vector<int> prefix(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        prefix[i] = prefix[i - 1] + nums[i - 1];
    }
    unordered_map<int, int> mp;
    int ans = 0;
    for (int r = 0; r <= n; r++)
    {
        int req = (prefix[r] % n + n) % n;
        ans += mp[req];
        mp[req]++;
    }

    cout << ans << endl;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    nums.resize(n);

    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    solve1();
    return 0;
}