#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9 + 7;

/*
    Problem 1681: Game Routes
    Pattern: dfs
    Time: O(E+V) Space: O(E+V)
    Link: https://cses.fi/problemset/task/1681
*/

/*
    dfs(u) => number of ways to reach node n (destination)
    this problem can also be solved with bottom up using topo + dp
*/

vector<vector<int>> adj;
vector<int> dp;
int dfs(int u, int d)
{
    if (u == d)
        return 1;
    if (dp[u] != -1)
        return dp[u];
    int ans = 0;
    for (auto v : adj[u])
    {
        ans = (ans + dfs(v, d)) % mod;
    }
    return dp[u] = ans;
}
int32_t main()
{
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    adj.resize(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
    }

    dp.resize(n, -1);
    cout << dfs(0, n - 1) << endl;

    return 0;
}