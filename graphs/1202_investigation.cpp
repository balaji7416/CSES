#include <bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 1e18;
const int mod = 1e9 + 7;
vector<tuple<int, int, int>> dp;

/*
    Problem 1202: Investigation
    Pattern: Dijkstra
    Time: O(ElogV), Space: O(E+V)
*/
/* Implementation :

1) Run Dijkstra from source (node 0)
   → compute dist[] = shortest distance to every node.

2) Observe:
   If dist[u] + w == dist[v],
   then edge (u → v) lies on some shortest path.
   These edges form a DAG (because weights > 0 ⇒ dist strictly increases).

3) Build implicit shortest-path DAG:
   Instead of constructing it explicitly,
   during DFS only traverse edges satisfying:
       dist[u] + w == dist[v]

4) Define DP state:
   dp[u] = {paths, min_nodes, max_nodes}
   meaning:
       paths     = number of shortest paths from u → destination
       min_nodes = minimum nodes in such paths (including u)
       max_nodes = maximum nodes in such paths (including u)

5) Base case:
       destination → {1, 1, 1}

6) Transition:
       For all valid shortest edges u → v:
           accumulate paths
           take min of min_nodes
           take max of max_nodes
       then add +1 to account for current node.

7) Final answer:
       dist[n-1], paths,
       min_nodes - 1, max_nodes - 1
   (-1 because problem wants number of edges, not nodes)
*/
/* KEY INSIGHTS:

1) Shortest paths form a DAG when all edge weights are positive.
   Reason: dist[u] < dist[v] for every shortest edge.

2) Counting shortest paths is NOT brute force.
   It is DP over the shortest-path DAG.

3) Once distances are fixed,
   shortest-path structure is deterministic —
   you only need to consider edges preserving dist[] equality.

4) State DP over graph nodes works because:
   - No cycles in shortest-path DAG
   - Memoization guarantees O(n + m) over valid edges

5) min/max path length must propagate carefully.
   Unreachable branches must not corrupt values.

6) Many multi-answer shortest path problems
   can be solved in two phases:
       Phase 1 → Dijkstra
       Phase 2 → DP on shortest DAG

7) Modeling matters more than memorizing.
   You didn’t modify Dijkstra —
   you extracted structural information from it.
*/

bool filled(tuple<int, int, int> &t)
{
    auto [x, y, z] = t;
    return x != -1 && y != -1 && z != -1;
}
tuple<int, int, int> dfs(int u, vector<vector<pair<int, int>>> &adj, vector<int> &dist)
{
    int n = adj.size();
    if (u == n - 1)
    {
        return {1, 1, 1};
    }

    if (filled(dp[u]))
    {
        return dp[u];
    }
    int paths = 0, min_nodes = 1e9, max_nodes = 0;
    for (auto [v, w] : adj[u])
    {
        if (dist[u] + w == dist[v])
        {
            auto [p, minm, maxm] = dfs(v, adj, dist);
            paths = (paths + p) % mod;
            min_nodes = min(min_nodes, minm);
            max_nodes = max(max_nodes, maxm);
        }
    }
    min_nodes = min_nodes == 1e9 ? 1e9 : min_nodes + 1;
    max_nodes = max_nodes == 0 ? 0 : max_nodes + 1;
    return dp[u] = {paths, min_nodes, max_nodes};
}
int32_t main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].push_back({v, w});
    }

    vector<int> dist(n, inf);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0}); //{weight,node}
    dist[0] = 0;

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto [v, w] : adj[u])
        {
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    dp = vector<tuple<int, int, int>>(n);
    for (int i = 0; i < n; i++)
    {
        auto &[x, y, z] = dp[i];
        x = y = z = -1;
    }
    auto [paths, min_nodes, max_nodes] = dfs(0, adj, dist);
    cout << dist[n - 1] << " " << paths << " " << min_nodes - 1 << " " << max_nodes - 1 << endl;
    return 0;
}
