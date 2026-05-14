#include <bits/stdc++.h>
using namespace std;

#define int long long

/*
    Problem 1688: Company Queries II
    Pattern: LCA
    Time: O((n+q)logn), pace: O(nlogn)
    Link: https://cses.fi/problemset/task/1688
*/

/* IDEA:
LCA using Binary Lifting

Idea:
- Precompute 2^i-th ancestors for every node (up[u][i])
- Also store depth of each node

Steps:
1. DFS:
   - depth[v] = depth[u] + 1
   - up[u][0] = parent
   - up[u][i] = 2^i ancestor = up[ up[u][i-1] ][i-1]

2. jump(x, k):
   - Move node x up by k steps using binary representation of k

3. LCA(a, b):
   - Bring both nodes to same depth using jump()
   - If equal → return
   - Lift both simultaneously from highest power → lowest
     until their ancestors differ
   - Return their parent (up[a][0])

Time:
- Preprocessing: O(n log n)
- Each query: O(log n)
*/

int32_t main()
{
    ios::sync_with_stdio(false);

    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++)
    {
        int u;
        cin >> u;
        u--;
        adj[i + 1].push_back(u);
        adj[u].push_back(i + 1);
    }

    int LOG = 20;
    vector<int> depth(n, 0);
    vector<vector<int>> up(n, vector<int>(LOG, -1));

    auto dfs = [&](auto &&self, int u, int p) -> void
    {
        up[u][0] = p;
        for (int i = 1; i < LOG; i++)
        {
            up[u][i] = (up[u][i - 1] == -1 ? -1 : up[up[u][i - 1]][i - 1]);
        }

        for (int v : adj[u])
        {
            if (v == p)
                continue;
            depth[v] = depth[u] + 1;
            self(self, v, u);
        }
    };

    // build the detph, up vectors
    dfs(dfs, 0, -1);

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
            swap(a, b);
        // equilize the depth of a, b
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
        int ans = lca(a, b);
        ans == -1 ? cout << -1 << endl : cout << ans + 1 << endl;
    }
    return 0;
}