#include <bits/stdc++.h>
using namespace std;

// Created: 2026-07-14 22:13
#define int long long

struct fenwick
{
    int n;
    vector<int> bit;

    fenwick(int n) : n(n)
    {
        bit.resize(n + 2, 0);
    }
    void update(int i, int val)
    {
        i++;
        while (i <= n)
        {
            bit[i] += val;
            i += i & -i;
        }
    }
    int query(int i)
    {
        i++;
        int s = 0;
        while (i > 0)
        {
            s += bit[i];
            i -= i & -i;
        }
        return s;
    }
    int range_query(int a, int b)
    {
        return query(b) - query(a - 1);
    }
};

struct query
{
    char type;
    int a, b;
    query(char t, int a, int b) : type(t), a(a), b(b) {}
};

int32_t
main()
{
    ios::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;

    vector<int> nums(n);

    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    vector<int> values = nums;
    vector<query> qrs;
    while (q--)
    {
        char t;
        cin >> t;
        int a, b;
        if (t == '!')
        {
            cin >> a >> b;
            qrs.push_back(query(t, a, b));
            values.push_back(b);
        }
        else
        {
            cin >> a >> b;
            qrs.push_back(query(t, a, b));
        }
    }

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    fenwick fw(values.size());
    for (int i : nums)
    {
        int idx = lower_bound(values.begin(), values.end(), i) - values.begin();
        fw.update(idx, 1);
    }

    for (auto qr : qrs)
    {
        if (qr.type == '!')
        {
            int old = lower_bound(values.begin(), values.end(), nums[qr.a - 1]) - values.begin();
            int nw = lower_bound(values.begin(), values.end(), qr.b) - values.begin();

            fw.update(old, -1);
            fw.update(nw, 1);
            nums[qr.a - 1] = qr.b;
        }
        else
        {
            int l = lower_bound(values.begin(), values.end(), qr.a) - values.begin();
            int r = upper_bound(values.begin(), values.end(), qr.b) - values.begin() - 1;
            cout << fw.range_query(l, r) << endl;
        }
    }

    return 0;
}