#include <bits/stdc++.h>
using namespace std;

// Created: 2026-07-30 22:54
#define int long long

/*
    Complexity of each query - (logn)^2
    total queries to process - n
    Total - O(n(logn)^2)
*/

struct fenwick
{
    int n;
    vector<int> bit;
    fenwick(int n)
    {
        this->n = n;
        bit.resize(n + 1, 0);
    }
    void update(int i, int val)
    {
        while (i <= n)
        {
            bit[i] += val;
            i += i & -i;
        }
    }
    int query(int i)
    {
        int s = 0;
        while (i > 0)
        {
            s += bit[i];
            i -= i & -i;
        }
        return s;
    }
    int range_query(int l, int r)
    {
        return query(r) - query(l - 1);
    }
};

int32_t
main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> nums(n);
    fenwick fw(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
        fw.update(i + 1, 1); // initially every position is alive
    }

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;

        // binary search over postion
        int low = 1, high = n;
        int pos = n;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (fw.query(mid) >= x)
            {
                pos = mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        fw.update(pos, -1); // mark the position as dead
        cout << nums[pos - 1] << " ";
    }
    return 0;
}