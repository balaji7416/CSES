#include <bits/stdc++.h>
using namespace std;

/*
    Problem : Building Roads
    Pattern : dfs
    Link : https://cses.fi/problemset/task/1666
    Time complexity : O(E+v)
    Space complexity : O(v+E)
*/

/* LOGIC:
Make the graph connected by adding the minimum number of roads.

Key Observation:
If a graph has k connected components,
we need exactly (k - 1) edges to connect them.

Approach:
1. Build adjacency list for the undirected graph.
2. Run DFS to identify connected components.
3. For every new component found:
   - If it is not the first component,
     connect its representative node with the previous component’s representative.
4. Store these new roads.
5. Print the number of added roads and the connections.

Why This Works:
Connecting components in a chain:
C1 -- C2 -- C3 -- ... -- Ck

Uses exactly (k - 1) edges,
which is the minimum required to make the graph fully connected.

Time Complexity:
O(V + E)
- Each node visited once.
- Each edge explored once per endpoint.

Space Complexity:
O(V + E)
- Adjacency list
- Visited array
- Recursion stack (worst case O(V))
*/

void dfs(int u, vector<vector<int>> &adj, vector<bool> &visited)
{
    visited[u] = true;
    for (auto v : adj[u])
    {
        if (!visited[v])
        {
            dfs(v, adj, visited);
        }
    }
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

    vector<pair<int, int>> roads;
    vector<bool> visited(n, false);
    int prev = -1;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            dfs(i, adj, visited);
            if (prev != -1)
            {
                roads.push_back({prev + 1, i + 1});
            }
            prev = i;
        }
    }
    cout << roads.size() << endl;
    for (auto [src, dest] : roads)
    {
        cout << src << " " << dest << endl;
    }

    return 0;
}