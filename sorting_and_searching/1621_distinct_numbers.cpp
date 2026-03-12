#include <bits/stdc++.h>
using namespace std;

#define int long long

/*
    Problem 1621: Distinct Numbers
    Pattern: hashing
    Time: O(N) Space: O(N)
    Link: https://cses.fi/problemset/task/1621
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

int32_t main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    /*method 1: use custom hash to tackle the demonic cses test case
    unordered_set<int, custom_hash> st;
    int count = 0;
    for (auto n : nums)
    {
        if (!st.count(n))
        {
            count++;
            st.insert(n);
        }
    }
        */

    // /*method 2: use set*/
    // set<int> st(nums.begin(), nums.end());
    // cout << st.size() << endl;

    /*method 3: sort and remove the duplicates: STL wizardy*/
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    cout << nums.size() << endl;

    return 0;
}