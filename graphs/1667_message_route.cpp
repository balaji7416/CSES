#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1667: Message Route
    Link: https://cses.fi/problemset/task/1667
*/

/*
    Approach:
    ----------
    We use BFS on an unweighted, undirected graph to find the
    shortest path from node 1 (0 in 0-based) to node n (n-1).

    Why BFS?
    --------
    In an unweighted graph, BFS guarantees the shortest path
    in terms of number of edges.

    Steps:
    ------
    1. Build adjacency list (0-based indexing).
    2. Run BFS starting from node 0.
    3. Use:
         - visited[] to avoid revisiting nodes
         - parent[] to reconstruct the shortest path
    4. Stop early when we reach node n-1.
    5. If not reachable → print "IMPOSSIBLE".
    6. Otherwise, backtrack using parent[] to build the path.

    Complexity:
    -----------
    Time  : O(V + E)
    Space : O(V + E)

    Key Idea:
    ---------
    parent[v] stores the node from which v was first discovered.
    Backtracking from destination to source reconstructs
    the shortest path.
*/

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--; // convert to 0 based indexing for easier handling
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> visited(n, false); // to stop infinite traversal
    vector<int> parent(n, -1);
    queue<int> q;
    q.push(0);
    visited[0] = true;
    bool found = false;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (u == n - 1)
        {
            found = true;
            break;
        }
        for (auto v : adj[u])
        {
            if (!visited[v])
            {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    // if the dest node (n-1) not found
    if (!found)
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    // build ans by backtracking using parent array
    stack<int> ans;
    int u = n - 1;
    while (u != -1)
    {
        ans.push(u + 1); // push the nodes based on 1 based indexing
        u = parent[u];
    }

    cout << ans.size() << endl;
    while (!ans.empty())
    {
        cout << ans.top() << " ";
        ans.pop();
    }
    cout << endl;
}