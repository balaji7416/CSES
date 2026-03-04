#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
/*
    Problem 1680: Longest Flight Route
    Pattern: topo + dp
    Time: O(E+V) Space: O(E+V)
    Link: https://cses.fi/problemset/task/1680
*/
/* Approach:

Goal:
Find the longest path (by number of nodes) from node 1 to node n
in a directed acyclic graph (DAG).

Key Observations:
1. The graph is guaranteed to be a DAG.
2. Longest path in a general directed graph is NP-hard.
3. But in a DAG, we can solve it in O(V + E) using:
      Topological Sort + Dynamic Programming.

------------------------------------------------------------
DP Modelling:

Let:
    dp[u] = maximum number of nodes in a path from node 1 to node u.

Initialization:
    dp[0] = 1        (path starting at node 1 contains itself)
    dp[i] = -inf     (means node i is not reachable from node 1)

Why -inf?
    To distinguish unreachable nodes from valid paths.
    It prevents fake transitions during DP propagation.

Transition:
For every directed edge u → v:
    if dp[u] is reachable:
        dp[v] = max(dp[v], dp[u] + 1)

This extends the longest path ending at u to v.

------------------------------------------------------------
Why Topological Sort?

In a DAG, we process nodes in topological order so that:
    For every edge u → v,
    u is processed before v.

This guarantees that when we update dp[v],
dp[u] is already finalized.

------------------------------------------------------------
Algorithm Steps:

1. Build adjacency list.
2. Compute in-degrees.
3. Perform Kahn's Algorithm to get topological order.
4. Run DP over nodes in topo order.
5. If dp[n-1] == -inf:
       Output "IMPOSSIBLE"
   Else:
       Reconstruct path using parent[] array.

------------------------------------------------------------
Time Complexity:
    O(V + E)

Space Complexity:
    O(V + E)

Core Pattern:
    DAG + Longest Path
    => Topological Sort + DP Propagation
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
        u--;
        v--;
        adj[u].push_back(v);
    }

    vector<int> inDegree(n, 0);
    for (int i = 0; i < n; i++)
    {
        for (auto v : adj[i])
        {
            inDegree[v]++;
        }
    }
    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        if (inDegree[i] == 0)
        {
            q.push(i);
        }
    }
    vector<int> topo;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (auto v : adj[u])
        {
            inDegree[v]--;
            if (inDegree[v] == 0)
            {
                q.push(v);
            }
        }
        topo.push_back(u);
    }

    vector<int> dp(n, -inf);
    vector<int> parent(n, -1);
    dp[0] = 1;
    for (auto u : topo)
    {
        if (dp[u] == -inf)
            continue;
        for (auto v : adj[u])
        {
            if (dp[u] + 1 > dp[v])
            {
                dp[v] = dp[u] + 1;
                parent[v] = u;
            }
        }
    }
    if (dp[n - 1] == -inf)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        stack<int> stk;
        int u = n - 1;
        while (u != 0)
        {
            stk.push(u + 1);
            u = parent[u];
        }
        stk.push(1);
        cout << stk.size() << endl;
        while (!stk.empty())
        {
            cout << stk.top() << " ";
            stk.pop();
        }
        cout << endl;
    }
}