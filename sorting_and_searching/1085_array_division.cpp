#include <bits/stdc++.h>
using namespace std;

#define int long long

/*
    Problem 1085: Array Division
    Pattern: binary search on answer
    Time: O(n log(sum(arr))) Space: O(1)
    Link: https://cses.fi/problemset/task/1085
*/

/*Idea:
We want to split the array into at most k contiguous parts such that
the maximum sum among the parts is minimized.

Observation:
- The minimum possible answer is max(arr[i]) (a part must contain at least one element).
- The maximum possible answer is sum(arr) (take everything in one part).

Approach:
Binary search on the answer (maximum allowed segment sum).

For a candidate value `mid`:
- Greedily build segments while keeping the current segment sum ≤ mid.
- If adding an element exceeds mid, start a new segment.
- Count how many segments are needed.

If the number of segments ≤ k → `mid` is feasible
why ? since we can increase the number of segments by splitting
still keeping the current segment sum ≤ mid.
, try a smaller value.
Otherwise → increase `mid`.

Thus we find the minimum possible maximum segment sum.
Time Complexity: O(n log(sum(arr))).
**/

int32_t main()
{
    ios::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int low = INT_MIN, high = 0;
    for (int _ : arr)
    {
        low = max(low, _);
        high += _;
    }
    int ans = high;

    auto is_valid = [&](int mid) -> bool
    {
        int curr = 0, parts = 1;
        for (auto _ : arr)
        {
            if (curr + _ > mid)
            {
                curr = 0;
                parts++;
            }
            curr += _;
        }
        return parts <= k;
    };

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (is_valid(mid))
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    cout << ans << endl;

    return 0;
}