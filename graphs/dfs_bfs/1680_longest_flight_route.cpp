#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1680: Longest Flight Route
    Pattern: dfs
    Time: O(E+V) Space: O(E+V)
    Link: https://cses.fi/problemset/task/1680
*/
/* Approach:
    dfs(u) => max nodes from node u to node n-1
    dp[u] = max nodes from node u to node n-1 (for memoization)
    child[u] = child of u (for reconstruction of path)

*/

int dfs(int u, vector<vector<int>> &adj, vector<int> &child, vector<int> &dp)
{
    int n = adj.size();
    if (u == n - 1)
    {
        return 1;
    }
    if (dp[u] != -1)
    {
        return dp[u];
    }
    int mnodes = 0; // maxnodes init to zero
    for (auto v : adj[u])
    {
        int nodes = dfs(v, adj, child, dp);
        if (nodes > mnodes)
        {
            child[u] = v;
            mnodes = nodes;
        }
    }
    // if no path found return just 0, so that recursion won't be corrupted
    return dp[u] = mnodes == 0 ? 0 : 1 + mnodes;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
    }
    vector<int> child(n, -1);
    vector<int> dp(n, -1); // dp[i] = max nodes from node i to node n-1
    int ans = dfs(0, adj, child, dp);
    if (ans == 0)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        cout << ans << endl;
        int u = 0;
        while (u != n - 1)
        {
            cout << u + 1 << " ";
            u = child[u];
        }
        cout << n << endl;
    }
}