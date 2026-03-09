#include <bits/stdc++.h>
using namespace std;

#define int long long

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

int32_t main()
{
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    Tarjan tr(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        tr.addEdge(u, v);
    }
    tr.run();
    auto &scc = tr.scc;
    if (scc.size() == 1)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
        cout << scc[0][0] + 1 << " " << scc[1][0] + 1 << endl;
    }
    return 0;
}