#include <bits/stdc++.h>
using namespace std;

#define int long long

/*
    Problem 1686: Coin Collector
    Pattern: Tarjan's algo + dp
    Time: O(E+V) Space: O(E+V)
    Link: https://cses.fi/problemset/task/1686
*/

/* Logic:
1. Run Tarjan's algorithm to compress the graph into SCCs.
2. All nodes inside an SCC are mutually reachable, so we can collect all their coins.
   Sum the coins of each SCC to form a single weighted node.
3. Build the condensation graph (SCC graph). This graph is always a DAG.
4. Run DP on the DAG where:
       dp[u] = coin[u] + max(dp[v]) for all edges u -> v
   meaning the maximum coins collectable starting from component u.
5. The answer is the maximum dp value over all SCC nodes.
*/

struct Tarjan
{
    int n, timer = 0, scc_count = 0;
    vector<vector<int>> adj, scc;
    vector<int> tin, low, comp_id;
    vector<bool> inStack;
    stack<int> st;

    Tarjan(int n) : n(n)
    {
        adj.resize(n);
        tin.assign(n, -1);
        low.resize(n);
        comp_id.assign(n, -1);
        inStack.assign(n, false);
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    void dfs(int u)
    {
        tin[u] = low[u] = timer++;
        st.push(u);
        inStack[u] = true;

        for (int v : adj[u])
        {
            if (tin[v] == -1)
            {
                dfs(v);
                low[u] = min(low[u], low[v]);
            }
            else if (inStack[v])
            {
                low[u] = min(low[u], tin[v]);
            }
        }

        if (tin[u] == low[u])
        {
            vector<int> comp;
            while (true)
            {
                int v = st.top();
                st.pop();
                inStack[v] = false;
                comp.push_back(v);
                comp_id[v] = scc_count;
                if (v == u)
                    break;
            }
            scc.push_back(comp);
            scc_count++;
        }
    }

    void run()
    {
        for (int i = 0; i < n; i++)
            if (tin[i] == -1)
                dfs(i);
    }
};

vector<int> coin;
vector<vector<int>> dag;
vector<int> dp;

int dfs(int u)
{
    if (dp[u] != -1)
    {
        return dp[u];
    }
    int max_coins = 0;
    for (auto v : dag[u])
    {
        max_coins = max(max_coins, dfs(v));
    }
    return dp[u] = max_coins + coin[u];
}

int32_t main()
{
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int> coins(n);
    Tarjan tr(n);
    for (int i = 0; i < n; i++)
        cin >> coins[i];
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        tr.addEdge(u, v);
    }

    // run tarjan
    tr.run();

    // build the dag out of scc's
    dag.resize(tr.scc_count);

    // for storing the coin of each scc
    coin.resize(tr.scc_count, 0);

    for (int u = 0; u < n; u++)
    {
        for (auto v : tr.adj[u])
        {
            if (tr.comp_id[u] != tr.comp_id[v])
            {
                dag[tr.comp_id[u]].push_back(tr.comp_id[v]);
            }
        }
        coin[tr.comp_id[u]] += coins[u];
    }

    int ans = 0;
    dp.resize(tr.scc_count, -1);
    for (int i = 0; i < tr.scc_count; i++)
    {
        ans = max(ans, dfs(i));
    }
    cout << ans << endl;
    return 0;
}