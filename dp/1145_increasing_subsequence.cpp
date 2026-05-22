#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1145: Longest Increasing Subsequence
    Pattern: dp
    Time: O(nlogn) Space: O(n)
    Link: https://cses.fi/problemset/task/1145
*/

int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int &i : nums)
        cin >> i;
    vector<int> tail;

    for (int x : nums)
    {
        auto it = lower_bound(tail.begin(), tail.end(), x);
        if (it == tail.end())
            tail.push_back(x);
        else
            *it = x;
    }
    cout << tail.size() << endl;
}