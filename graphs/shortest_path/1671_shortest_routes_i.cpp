#include <bits/stdc++.h>
using namespace std;
#define int long long
/*
    Problem 1671: Shortest Routes I
    pattern: Dijstra
    Time: O(ElogV) Space: O(E+V)
    Link: https://cses.fi/problemset/task/1671
*/

/* Approach:
    just use normal dijkstra to find shortest distance froms src to all nodes
    just make sure to use long long since constraints are vey large
    and dont't forget to initialize dist array with
    LONG_LONG_MAX and not INT_MAX since distances like i said
    can go upto 1e4
*/

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

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(n, LONG_LONG_MAX);
    pq.push({0, 0}); //{weight, node}
    dist[0] = 0;
    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        // if edge is outdated
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

    for (int i = 0; i < n; i++)
    {
        cout << dist[i] << " ";
    }
    cout << endl;

    return 0;
}