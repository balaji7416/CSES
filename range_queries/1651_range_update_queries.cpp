#include <bits/stdc++.h>
using namespace std;

// Created: 2026-07-31 12:55
#define int long long

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
    int n, q;
    cin >> n >> q;
    vector<int> nums(n);
    fenwick fw(n + 1);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    // store difference array in fenwick
    fw.update(1, nums[0]);
    for (int i = 1; i < n; i++)
    {
        fw.update(i + 1, nums[i] - nums[i - 1]);
    }

    while (q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            // add value u to all elements in the rane nums[a..b] (1 based idx)
            int a, b, u;
            cin >> a >> b >> u;

            fw.update(a, u);
            if (b + 1 <= n)
                fw.update(b + 1, -u);
        }
        else
        {
            // return value at pos k
            int k;
            cin >> k;
            int ans = fw.query(k);
            cout << ans << endl;
        }
    }
    return 0;
}