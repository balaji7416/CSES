#include <bits/stdc++.h>
using namespace std;
#define int long long
/*
    Problem 1195: Flight Discount
    Pattern: Dijkstra
    Time: O(ElogV), Space: O(E+V)
*/
/* COMPLEXITY EXPLANATION:

Original graph:
    n nodes, m edges

State expansion:
    Each node becomes 2 states:
        (node, coupon_available)
        (node, coupon_used)
    → total nodes = 2n

Each original edge produces:
    From (u,0) → (v,0)         (1 edge)
    From (u,1) → (v,1)         (1 edge)
    From (u,1) → (v,0)         (1 edge using coupon)
    → total edges ≈ 3m

Dijkstra runs on this expanded graph:
    O((V + E) log V)
    = O((2n + 3m) log (2n))

Since constants don’t matter asymptotically:
    Final complexity = O(m log n)

Not exponential.
State count is constant (2 per node),
so graph size increases linearly, not exponentially.
*/

/*  INSIGHTS FROM FLIGHT DISCOUNT:

1) Some shortest path problems require STATE modeling.
   A node is not just (u), it can be (u, state).
   Here state = whether coupon is used or not.

2) Dijkstra works on expanded graphs.
   We transformed original graph of n nodes into 2*n states:
   (node, coupon_available) and (node, coupon_used).

3) Always preserve graph structure.
   Using unordered_map changed semantics by removing parallel edges.
   since it overwrote earlier edges.
   eg. lets say we have edges (1,2,5) and (1,2,7).
   unordered_map will overwrite (1,2,5) with (1,2,7).

   For shortest path problems, always use:
       vector<vector<pair<int,int>>>
   unless deduplication is explicitly required.

4) When constraints allow multiple edges, never overwrite them
   unintentionally.

5) Distances must be long long with INF ~ 1e18.
   Path sums can exceed 2e9 easily.

6) State transitions define correctness:
   - If coupon unused → two transitions (use or skip)
   - If coupon used → only normal transition

7) If a discount must be applied exactly once,
   answer must be dist[destination][coupon_used_state].
*/

/* IMPLEMENTATION STRATEGY:

1) Build adjacency list:
       adj[u].push_back({v, w});

2) Maintain:
       dist[node][coupon_state]
   where coupon_state:
       1 → coupon available
       0 → coupon already used

3) Use min-heap storing:
       {distance, node, coupon_state}

4) Standard Dijkstra pattern:
       - Pop smallest state
       - Skip outdated entries
       - Relax edges based on state

5) Transition rules:
       if coupon_used:
           relax normally
       else:
           relax with:
               - use coupon (w/2, state -> 0)
               - skip coupon (w, state -> 1)

6) Final answer:
       dist[n-1][0]   // must end with coupon used
*/

const int inf = 1e18;
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

    vector<vector<int>> dist(n, vector<int>(2, inf));
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    pq.push({0, 0, 1}); //{weight,node,discount_coupons}
    dist[0][1] = 0;
    while (!pq.empty())
    {
        auto [d, u, c] = pq.top();
        pq.pop();
        if (d > dist[u][c])
            continue;

        for (auto [v, w] : adj[u])
        {
            // if there's no coupon left
            if (c == 0)
            {
                if (d + w < dist[v][0])
                {
                    dist[v][0] = d + w;
                    pq.push({dist[v][0], v, 0});
                }
            }

            // if there's a coupon left, two choices: either use coupon, or keep it for future
            else
            {
                // use coupon
                if (d + w / 2 < dist[v][0])
                {
                    dist[v][0] = d + w / 2;
                    pq.push({dist[v][0], v, 0});
                }

                // keep coupon
                if (d + w < dist[v][1])
                {
                    dist[v][1] = d + w;
                    pq.push({dist[v][1], v, 1});
                }
            }
        }
    }

    /*min cost to reach destination with no coupons
        we can see that ans will be always be reaching dest
        with 0 coupons
    */
    cout << dist[n - 1][0] << endl;
}