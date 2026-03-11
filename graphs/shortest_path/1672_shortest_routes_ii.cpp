#include <bits/stdc++.h>
using namespace std;

#define int long long
const int inf = 1e18;

/*
    Problem 1672: Shortest Routes II
    Pattern: Floyd Warshall
    Time: O(V^3) Space: O(V^2)
    Link: https://cses.fi/problemset/task/1672
*/

/* Logic:
    use the floyd warshall algorithm to find the shortest distance between all pairs of nodes
    #note: take the min weight of all paths between two nodes since multiple edges are possible
            i.e., dist[u][v] = min(dist[u][v], w)
*/

int32_t main()
{
    ios::sync_with_stdio(false);
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> dist(n, vector<int>(n, inf));
    for (int i = 0; i < n; i++)
    {
        dist[i][i] = 0;
    }
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[u][v], w);
    }

    // run floyd warshall
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] == inf || dist[k][j] == inf)
                    continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    // answer the queries now
    while (q--)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        dist[u][v] == inf ? cout << -1 << endl : cout << dist[u][v] << endl;
    }
    return 0;
}