#include <bits/stdc++.h>
using namespace std;

#define int long long
const int inf = 1e18;

struct Edge
{
    int u, v, w;
};
int32_t main()
{
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<Edge> edges;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        edges.push_back({u, v, w});
        adj[u].push_back(v);
    }

    vector<int> score(n, -inf);
    score[0] = 0;

    // run bellman to find the path with largest cost
    for (int i = 0; i < n - 1; i++)
    {
        bool changed = false;
        for (auto &[u, v, w] : edges)
        {
            if (score[u] != -inf && score[u] + w > score[v])
            {
                score[v] = score[u] + w;
                changed = true;
            }
        }
        if (!changed)
            break;
    }

    // check for a positive cycle
    vector<bool> bad(n, false);
    for (auto &[u, v, w] : edges)
    {
        if (score[u] != -inf && score[u] + w > score[v])
        {
            bad[v] = true;
        }
    }

    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        if (bad[i])
            q.push(i);
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : adj[u])
        {
            if (!bad[v])
            {
                bad[v] = true;
                q.push(v);
            }
        }
    }

    if (bad[n - 1])
    {
        cout << -1 << endl;
    }
    else
    {
        cout << score[n - 1] << endl;
    }

    return 0;
}