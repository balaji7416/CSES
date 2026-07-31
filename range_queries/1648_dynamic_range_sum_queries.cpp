#include <bits/stdc++.h>
using namespace std;

// Created: 2026-07-30 22:26
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

int32_t main()
{
    ios::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<int> nums(n);
    fenwick fw(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
        fw.update(i + 1, nums[i]);
    }

    while (q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int k, u;
            cin >> k >> u;
            k--;
            int diff = u - nums[k];
            if (diff != 0)
            {
                fw.update(k + 1, diff);
            }
            nums[k] = u;
        }
        else
        {
            int a, b;
            cin >> a >> b;
            cout << fw.range_query(a, b) << endl;
        }
    }
    return 0;
}