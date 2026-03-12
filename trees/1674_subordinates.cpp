#include <bits/stdc++.h>
using namespace std;

#define int long long
vector<vector<int>> adj;
vector<int> subtree;

/*
    Problem 1674: Subordinates
    Pattern: dfs / graphs / tree
    Time: O(E+V) Space: O(E+V)
    Link: https://cses.fi/problemset/task/1674
*/

/* Logic:
    dfs(u) => size of subtree of node u
    calculate the subtree size of every node
    and return subtree size - 1 since we need only the subordinates (subtree sizes excluding root)
*/

int dfs(int u, int p)
{
    int child_tree = 0;
    for (int v : adj[u])
    {
        if (v == p)
            continue;
        child_tree += dfs(v, u);
    }
    return subtree[u] = 1 + child_tree;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    adj.resize(n);
    subtree.resize(n, 0);
    for (int i = 1; i < n; i++)
    {
        int v;
        cin >> v;
        v--;
        adj[i].push_back(v);
        adj[v].push_back(i);
    }
    dfs(0, -1);

    for (int s : subtree)
    {
        cout << s - 1 << " ";
    }
    cout << endl;
    return 0;
}