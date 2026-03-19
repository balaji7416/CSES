#include <bits/stdc++.h>
using namespace std;

#define int long long

/*
    Problem 1135: Distance Queries
    Pattern: LCA
    Time: O((n+q)logn), space: O(nlogn)
    Link: https://cses.fi/problemset/task/1135
*/

/*
Core Idea: Binary Lifting for LCA + Distance Queries

1. Preprocessing:
   - Build tree using adjacency list.
   - Use BFS/DFS to compute:
        depth[u] = depth from root
        up[u][i] = 2^i-th ancestor of node u
   - Transition:
        up[u][i] = up[ up[u][i-1] ][i-1]

2. Jump Function:
   - Moves a node u up by k steps using binary lifting.
   - Iterate over bits of k and lift accordingly.

3. LCA(a, b):
   - Bring both nodes to same depth using jump().
   - If equal → return.
   - Otherwise, lift both simultaneously from highest power → lowest,
     until their parents differ.
   - Final LCA = parent of either node.

4. Distance:
   - dist(a, b) = depth[a] + depth[b] - 2 * depth[lca(a, b)]

Time Complexity:
   - Preprocessing: O(n log n)
   - Each query: O(log n)
*/

/*use '\n' instead of endl → avoids flush → prevents TLE
    like seriously, it gave tle on two test cases no matter what i did
    until i changed endl to '\n'
*/

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n);
    vector<int> parent(n, -1);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int LOG = 20;
    vector<int> depth(n, 0);
    vector<vector<int>> up(n, vector<int>(LOG, -1));
    auto dfs = [&](auto &&self, int u, int p) -> void
    {
        parent[u] = p;
        for (int v : adj[u])
        {
            if (v == p)
                continue;
            depth[v] = depth[u] + 1;
            self(self, v, u);
        }
    };

    dfs(dfs, 0, -1);
    for (int i = 0; i < n; i++)
    {
        up[i][0] = parent[i];
    }
    for (int i = 1; i < LOG; i++)
    {
        for (int u = 0; u < n; u++)
        {
            up[u][i] = up[u][i - 1] == -1 ? -1 : up[up[u][i - 1]][i - 1];
        }
    }

    auto jump = [&](int x, int k) -> int
    {
        for (int i = 0; i < LOG; i++)
        {
            if (k & (1 << i))
            {
                x = up[x][i];
                if (x == -1)
                    return -1;
            }
        }
        return x;
    };

    auto lca = [&](int a, int b)
    {
        if (depth[a] < depth[b])
        {
            swap(a, b);
        }

        a = jump(a, depth[a] - depth[b]);
        if (a == b)
            return a;
        for (int i = LOG - 1; i >= 0; i--)
        {
            if (up[a][i] != -1 && up[b][i] != -1 && up[a][i] != up[b][i])
            {
                a = up[a][i];
                b = up[b][i];
            }
        }
        return up[a][0];
    };

    while (q--)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        int lca_ = lca(a, b);
        int ans = depth[a] - depth[lca_] + depth[b] - depth[lca_];
        cout << ans << '\n';
    }
    return 0;
}