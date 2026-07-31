#include <bits/stdc++.h>
using namespace std;

// Created: 2026-07-31 13:43
#define int long long

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
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> nums(n);
    fenwick fw(n);
    // here in fenwick bit[i] = 1 if the element at idx i doesn't appeared before; 0 otherwise;
    // query[i] = no.of unique elements till idx i

    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    vector<tuple<int, int, int>> queries;
    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;
        queries.push_back({a, b, i});
    }

    sort(queries.begin(), queries.end(), [&](tuple<int, int, int> &a, tuple<int, int, int> &b)
         { return get<1>(a) < get<1>(b); });

    vector<int> ans(q);
    unordered_map<int, int, custom_hash> mp;
    int i = 1;
    for (auto &[a, b, idx] : queries)
    {
        while (i <= b)
        {
            if (mp.count(nums[i - 1]))
            {
                fw.update(mp[nums[i - 1]], -1); // mark the prev occurrence as dead
                // mp.erase(nums[i-1]);
            }
            fw.update(i, 1); // mark this latest occrrence as alive
            mp[nums[i - 1]] = i;
            i++;
        }
        int res = fw.range_query(a, b);
        ans[idx] = res;
    }

    for (int i : ans)
        cout << i << '\n';
    return 0;
}