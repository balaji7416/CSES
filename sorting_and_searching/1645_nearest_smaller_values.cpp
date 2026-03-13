#include <bits/stdc++.h>
using namespace std;

#define int long long
vector<int> nums;
int n;

/*
    Problem 1645: Nearest Smaller Values
    Pattern: monotonic stack
    Time: O(N) Space: O(N)
    Link: https://cses.fi/problemset/task/1645
*/

/*
   Monotonic stack (increasing values).

   Traverse from right → left and keep indices in a stack.
   The stack maintains elements whose nearest smaller element
   on the left has not been found yet.

   When nums[i] < nums[stk.top()], we found the nearest smaller
   element to the left for stk.top(), so record i and pop.

   Each index is pushed and popped at most once → O(n) time.
*/

void solve()
{
    stack<int> stk;
    vector<int> ans(n, -1);
    for (int i = n - 1; i >= 0; i--)
    {
        while (!stk.empty() && nums[i] < nums[stk.top()])
        {
            ans[stk.top()] = i;
            stk.pop();
        }
        stk.push(i);
    }
    for (auto i : ans)
    {
        cout << i + 1 << " ";
    }
    cout << endl;
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
    solve();
    return 0;
}