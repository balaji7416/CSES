#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1668: Building Teams
    pattern: dfs/bfs (bipartite check)
    Time: O(E+V),  Space: O(E+V)
    Link: https://cses.fi/problemset/task/1668
*/

/*dfs(u) -> color all the nodes following bipartite ness and return true
            or return false if it's not possible
*/

/* Approach:
    ----------
    We check whether the given undirected graph is bipartite
    using DFS.

    Idea:
    -----
    A graph is bipartite if we can color nodes using 2 colors
    such that no adjacent nodes have the same color.

    Steps:
    ------
    1. Build adjacency list (0-based indexing).
    2. Maintain color[] initialized to -1 (unvisited).
    3. For every unvisited node:
         - Assign color 0.
         - Run DFS to color neighbors with alternate color.
    4. If at any point two adjacent nodes have the same color,
       return "IMPOSSIBLE".
    5. Otherwise print the assigned teams (color + 1).

    Complexity:
    -----------
    Time  : O(V + E)
    Space : O(V + E)

    Key Insight:
    ------------
    During DFS, color[v] = 1 - color[u] ensures alternate coloring.
    A conflict immediately proves the graph is not bipartite.
*/

bool dfs(int u, vector<vector<int>> &adj, vector<int> &color)
{
    for (auto v : adj[u])
    {
        if (color[v] == -1)
        {
            color[v] = 1 - color[u];
            if (!dfs(v, adj, color))
            {
                return false;
            }
        }
        else if (color[v] == color[u])
        {
            return false;
        }
    }
    return true;
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
        adj[v].push_back(u);
    }

    vector<int> color(n, -1);
    // vector<bool> visited(n,false);
    for (int i = 0; i < n; i++)
    {
        if (color[i] == -1)
        {
            color[i] = 0;
            if (!dfs(i, adj, color))
            {
                cout << "IMPOSSIBLE" << endl;
                return 0;
            };
        }
    }

    for (auto c : color)
    {
        cout << c + 1 << " ";
    }
    cout << endl;
}