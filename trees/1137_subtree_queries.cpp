#include <bits/stdc++.h>
using namespace std;

#define int long long

/* Core Idea (Euler Tour + Fenwick Tree):

1. Flatten the tree:
   - Run DFS and assign tin[u] = entry time of node u
   - Compute sz[u] = size of subtree of u
   → Subtree of u becomes a contiguous range:
     [tin[u], tin[u] + sz[u] - 1]

2. Build an array implicitly using tin:
   - Position tin[u] stores value of node u

3. Use Fenwick Tree on this flattened array:
   - add(pos, val) → update value at a position
   - sum(pos) → prefix sum [0..pos]
   - range(l, r) = sum(r) - sum(l-1)

4. Query handling:
   - Update node u to new value:
       diff = new_val - old_val
       fenwick.add(tin[u], diff)
       update value[u]

   - Query subtree sum of u:
       l = tin[u]
       r = tin[u] + sz[u] - 1
       answer = fenwick.range(l, r)

Time Complexity:
- DFS: O(n)
- Each query: O(log n)
*/

struct fenwick
{
    int n;
    vector<int> bit;

    fenwick(int n)
    {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    void add(int i, int val)
    {
        i++;
        while (i <= n)
        {
            bit[i] += val;
            i += (i & -i);
        }
    }

    int sum(int i)
    {
        i++;
        int s = 0;
        while (i > 0)
        {
            s += bit[i];
            i -= (i & -i);
        }
        return s;
    }

    int range(int l, int r)
    {
        if (l > r)
            return 0;
        return sum(r) - (l ? sum(l - 1) : 0);
    }
};

int32_t main()
{
    ios::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<int> value(n);
    for (int i = 0; i < n; i++)
        cin >> value[i];

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> tin(n, 0), sz(n, 0);
    int timer = 0;
    auto dfs = [&](auto &&self, int u, int p) -> void
    {
        tin[u] = timer;
        timer++;
        sz[u] = 1;
        for (int v : adj[u])
        {
            if (v == p)
                continue;
            self(self, v, u);
            sz[u] += sz[v];
        }
    };
    dfs(dfs, 0, -1);
    fenwick fw(n);
    for (int i = 0; i < n; i++)
    {
        fw.add(tin[i], value[i]);
        // tin[i] => idx of node i in flattened array
    }

    while (q--)
    {
        int a, b, c;
        cin >> a;
        if (a == 1)
        {
            cin >> b >> c;
            b--;
            int diff = c - value[b];
            value[b] = c;
            fw.add(tin[b], diff);
        }
        else if (a == 2)
        {
            cin >> b;
            b--;
            int l = tin[b], r = tin[b] + sz[b] - 1;
            cout << fw.range(l, r) << endl;
        }
    }

    return 0;
}