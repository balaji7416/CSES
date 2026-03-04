#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1678: Round Trip II
    Pattern: dfs (cycle detection in directed graph)
    Time: O(E+V), Space: O(E+V)
    Link: https://cses.fi/problemset/task/1678
*/
/* Approach:
    ----------
    Detect a cycle in a directed graph using DFS.

    Key Idea:
    ---------
    In directed graphs, a cycle exists if we find a back-edge
    to a node currently in the recursion stack.

    We maintain:
    - visited[] : node has been processed before
    - inRec[]   : node is currently in recursion stack
    - parent[]  : to reconstruct the cycle path

    During DFS:
    -----------
    1. Mark node as visited and in recursion stack.
    2. For each neighbor:
         - If unvisited → continue DFS.
         - If inRec[v] is true → back-edge found → cycle exists.
    3. On backtracking, remove node from recursion stack.

    Cycle Reconstruction:
    ---------------------
    When back-edge u → v is found,
    backtrack from u to v using parent[]
    and reverse the path to get correct order.

    Complexity:
    -----------
    Time  : O(V + E)
    Space : O(V + E)
*/

bool dfs(int u, vector<vector<int>> &adj, vector<int> &parent, vector<bool> &inRec, vector<int> &ans, vector<bool> &visited)
{

    inRec[u] = true;
    visited[u] = true;
    for (auto v : adj[u])
    {
        if (!visited[v])
        {
            parent[v] = u;
            if (dfs(v, adj, parent, inRec, ans, visited))
            {
                return true;
            }
        }
        else if (inRec[v])
        {
            // cycle found
            ans.push_back(v + 1);
            while (u != v)
            {
                ans.push_back(u + 1);
                u = parent[u];
            }
            ans.push_back(v + 1);
            reverse(ans.begin(), ans.end()); // since edges are in oppst direction
            return true;
        }
    }
    // back track
    inRec[u] = false;
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
    }
    vector<bool> visited(n, false);
    vector<bool> inRec(n, false);
    vector<int> parent(n, -1);
    vector<int> ans;

    bool cycle_found = false;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            parent[i] = i;
            if (dfs(i, adj, parent, inRec, ans, visited))
            {
                cycle_found = true;
                break;
            }
        }
    }

    if (cycle_found)
    {
        cout << ans.size() << endl;
        for (auto _ : ans)
        {
            cout << _ << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}