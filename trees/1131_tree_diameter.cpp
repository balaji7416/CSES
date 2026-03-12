#include <bits/stdc++.h>
using namespace std;

#define int long long

/*
    Problem 1131: Tree Diameter
    Pattern: dfs
    Time: O(E+V) Space: O(E+V)
    Link: https://cses.fi/problemset/task/1131
*/

/* Idea:
Tree Diameter using Two DFS.

Key Idea:
In a tree, if you start from any node and find the farthest node A,
then A is guaranteed to be one endpoint of the diameter.

If we start another DFS from A, the farthest node from A will be the
other endpoint B of the diameter.

The distance between A and B is the tree's diameter.

Algorithm:
1. DFS from any node (e.g., 0) to find farthest node A.
2. DFS from A to find farthest node B and its distance.
3. That distance is the diameter.

Time: O(N)
*/

vector<vector<int>> adj;
vector<int> depth;

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

int32_t main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    adj.resize(n);
    depth.resize(n, 0);

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto [_, e1] = dfs(0, -1, 0);
    auto [diameter, e2] = dfs(e1, -1, 0);

    cout << diameter << endl;
    return 0;
}