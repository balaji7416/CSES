#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1681: Game Routes
    Pattern: top + dp
    Time: O(E+V) Space: O(E+V)
    Link: https://cses.fi/problemset/task/1681
*/
const int mod = 1e9 + 7;
vector<vector<int>> adj;

int main()
{
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
            q.push(i);
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

    vector<int> dp(n, 0);
    // dp[i] => no.of ways to reach node i from node 0
    dp[0] = 1;
    for (auto u : topo)
    {
        for (auto v : adj[u])
        {
            dp[v] = (dp[v] + dp[u]) % mod;
        }
    }

    cout << dp[n - 1] << endl;
    return 0;
}