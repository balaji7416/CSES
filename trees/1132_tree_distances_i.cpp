#include <bits/stdc++.h>
using namespace std;

#define int long long

/*
    Problem 1132: Tree Distances I
    Pattern: dfs / tree diameter trick / two dfs
    Time: O(E+V) Space: O(E+V)
    Link: https://cses.fi/problemset/task/1132
*/

/* IDEA:
 * Use the tree diameter trick.
 *
 * 1. Run DFS from any node (0) to find the farthest node 'a'.
 * 2. Run DFS from 'a' to find the farthest node 'b'. (a,b are the diameter endpoints)
 * 3. Compute distances of all nodes from 'a' -> distA[]
 * 4. Compute distances of all nodes from 'b' -> distB[]
 *
 * Key observation:
 * In a tree, the farthest node from any node i must be one of the
 * diameter endpoints. Therefore:
 *
 *       ans[i] = max(distA[i], distB[i])
 *
 * This gives the maximum distance from node i to any other node.
 *
 * Time Complexity: O(N)
 */

int n;
vector<vector<int>> adj;
vector<int> distA, distB;
pair<int, int> dfs(int u, int p, int dist)
{
    pair<int, int> best = {dist, u};
    for (int v : adj[u])
    {
        if (v == p)
            continue;
        best = max(best, dfs(v, u, dist + 1));
    }
    return best;
}
void dfs(int u, int p, vector<int> &dist)
{
    for (int v : adj[u])
    {
        if (v == p)
            continue;
        dist[v] = 1 + dist[u];
        dfs(v, u, dist);
    }
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    adj.resize(n);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    auto [_, a] = dfs(0, -1, 0);
    auto [__, b] = dfs(a, -1, 0);

    distA.resize(n, 0);
    distB.resize(n, 0);

    // calculate dist of every node from a,b
    dfs(a, -1, distA);
    dfs(b, -1, distB);

    for (int i = 0; i < n; i++)
    {
        cout << max(distA[i], distB[i]) << " ";
    }
    cout << endl;
    return 0;
}