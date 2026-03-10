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
vector<vector<int>> adj;
vector<int> dp;
vector<int> child;
int d;
int dfs(int u)
{
    if (u == d)
        return 1;

    if (dp[u] != -1)
        return dp[u];

    int max_nodes = 0;
    for (auto v : adj[u])
    {
        int nodes = dfs(v);
        if (nodes > max_nodes)
        {
            max_nodes = nodes;
            child[u] = v;
        }
    }
    return dp[u] = max_nodes == 0 ? 0 : max_nodes + 1;
}

int main()
{
    int n, m;
    cin >> n >> m;
    adj.resize(n);
    child.resize(n, -1);
    dp.resize(n, -1);
    d = n - 1;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
    }

    int max_nodes = dfs(0);
    if (max_nodes == 0)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        cout << max_nodes << endl;
        int u = 0;
        while (u != n - 1)
        {
            cout << u + 1 << " ";
            u = child[u];
        }
        cout << n << " " << endl;
    }

    return 0;
}