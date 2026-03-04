#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1669: Round Trip
    Pattern: dfs (cycle detection in undirected graph)
    Time: O(E+V), Space: O(E+V)
    Link: https://cses.fi/problemset/task/1669
*/

/*
    dfs(u) => is there any cycle in the (yes if there is, else no)
    parent[i] == -1 if not visited
*/
/* Approach:
    ----------
    Detect a cycle in an undirected graph using DFS.

    parent[] serves two purposes:
    - Tracks parent of each node.
    - Acts as visited marker (parent[x] == -1 means unvisited).

    For each unvisited node:
    - Set parent[i] = i (root of component).
    - Run DFS.

    During DFS:
    - If neighbor is unvisited → continue DFS.
    - If neighbor is visited and not parent → cycle found.

    Cycle reconstruction:
    - When back-edge u -> v is found,
      backtrack using parent[] from u until v,
      and store the cycle.

    Complexity:
    -----------
    Time  : O(V + E)
    Space : O(V + E)
*/

bool dfs(int u, vector<vector<int>> &adj, vector<int> &parent, vector<int> &ans)
{
    for (auto v : adj[u])
    {
        if (parent[v] == -1)
        {
            parent[v] = u;
            if (dfs(v, adj, parent, ans))
            {
                return true;
            };
        }
        else if (v != parent[u])
        {
            // cycle found, build the cycle
            ans.push_back(v + 1);
            while (u != v)
            {
                ans.push_back(u + 1);
                u = parent[u];
            }
            ans.push_back(v + 1);
            return true;
        }
    }
    return false;
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

    vector<int> parent(n, -1);
    vector<int> ans;

    bool cycle_found = false;
    for (int i = 0; i < n; i++)
    {
        if (parent[i] == -1)
        {
            parent[i] = i; // mark parent as itself
            if (dfs(i, adj, parent, ans))
            {
                cycle_found = true;
                break;
            }
        }
    }
    if (cycle_found)
    {
        cout << ans.size() << endl;
        for (int _ : ans)
        {
            cout << _ << " ";
        }
    }
    else
    {
        cout << "IMPOSSIBLE" << endl;
    }
    cout << endl;
    return 0;
}