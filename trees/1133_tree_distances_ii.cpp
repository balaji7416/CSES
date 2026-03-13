#include <bits/stdc++.h>
using namespace std;

#define int long long

/*
    Problem 1133: Tree Distances II
    Pattern: dfs / rerooting dp
    Time: O(N) Space: O(E+V)
    Link: https://cses.fi/problemset/task/1133
*/

/*
IDEA: Rerooting DP on trees.

Goal: For every node u compute the sum of distances from u to all nodes.

1️. First DFS (dfs1)
   - Compute subtree[u] = size of subtree rooted at u.
   - Track depth of every node from root (0).

   Using depths we compute:
       ans[0] = sum of distances from node 0 to all nodes.

2️. Second DFS (dfs2) – Rerooting
   Move the root from u → v (child).

   When rerooting:
       nodes in v's subtree get 1 closer  → decrease = subtree[v]
       all other nodes get 1 farther      → increase = n - subtree[v]

   So:
       ans[v] = ans[u] - subtree[v] + (n - subtree[v])

   Propagate this formula to compute answers for all nodes.

Time Complexity: O(N)
Space Complexity: O(N)
*/

vector<vector<int>> adj;
int n;
vector<int> ans, depth, subtree;
int dfs1(int u, int p)
{
    int childTree = 0;
    for (int v : adj[u])
    {
        if (v == p)
            continue;
        depth[v] = 1 + depth[u];
        childTree += dfs1(v, u);
    }
    return subtree[u] = 1 + childTree;
}

void dfs2(int u, int p)
{
    for (int v : adj[u])
    {
        if (v == p)
            continue;
        ans[v] = ans[u] - subtree[v] + (n - subtree[v]);
        dfs2(v, u);
    }
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    adj.resize(n);
    ans.resize(n, 0);
    subtree.resize(n, 0);
    depth.resize(n);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // first calculate the ans for node 0 (or any root)
    dfs1(0, -1);
    ans[0] = accumulate(depth.begin(), depth.end(), 0LL);
    dfs2(0, -1);

    for (auto _ : ans)
    {
        cout << _ << " ";
    }
    cout << endl;
    return 0;
}