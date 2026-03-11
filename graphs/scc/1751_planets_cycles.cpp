#include <bits/stdc++.h>
using namespace std;

#define int long long

/*
    Problem 1751: Planets and Cycles
    Pattern: Tarjan's algo
    Time: O(E+V) Space: O(E+V)
    Link: https://cses.fi/problemset/task/1751
*/

/* Logic
Each planet has exactly one outgoing edge, forming a functional graph.
Such graphs consist of trees that eventually lead into cycles.

Step 1: Find Strongly Connected Components
------------------------------------------
Tarjan's algorithm is used to find SCCs in O(V+E).
In a functional graph, every SCC represents a cycle.
All nodes in the same SCC can reach each other indefinitely.

Step 2: Compress the graph
--------------------------
Each SCC is treated as a single node, forming a condensed graph (DAG).
Edges between nodes of different SCCs become edges between components.

comp_id[i]  -> component of node i
comp_size[c] -> number of nodes in component c (cycle size)

Step 3: Build SCC DAG
---------------------
For every edge u -> v in the original graph,
if comp_id[u] != comp_id[v], add an edge:

    comp_id[u] -> comp_id[v]

This produces a Directed Acyclic Graph of components.

Step 4: Topological ordering
----------------------------
A topological order of the SCC DAG is computed using Kahn's algorithm.
Reversing this order allows us to process components from sinks
(cycles) backwards toward incoming trees.

Step 5: DP on SCC DAG
---------------------
dp[c] represents the number of unique planets reachable starting
from component c.

Initial value:
    dp[c] = comp_size[c]

Transition:
    dp[c] += dp[next_component]

This works because each component has at most one outgoing edge
in a functional graph.

Step 6: Map results back to nodes
---------------------------------
Every node in the same SCC shares the same answer:

    answer[i] = dp[comp_id[i]]

This gives the number of planets visited before repetition.

Overall Complexity:
    O(V + E)
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

int32_t main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    Tarjan tr(n);

    for (int u = 0; u < n; u++)
    {
        int v;
        cin >> v;
        v--;
        tr.addEdge(u, v);
    }
    tr.run();

    vector<int> comp_size(tr.scc_count, 0);
    vector<vector<int>> dag(tr.scc_count);
    for (int i = 0; i < n; i++)
    {
        for (auto v : tr.adj[i])
        {
            if (tr.comp_id[i] != tr.comp_id[v])
            {
                dag[tr.comp_id[i]].push_back(tr.comp_id[v]);
            }
        }
        comp_size[tr.comp_id[i]]++;
    }

    vector<int> inDegree(tr.scc_count, 0);
    for (int i = 0; i < tr.scc_count; i++)
    {
        for (auto v : dag[i])
        {
            inDegree[v]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < tr.scc_count; i++)
    {
        if (inDegree[i] == 0)
        {
            q.push(i);
        }
    }
    vector<int> topo;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : dag[u])
        {
            inDegree[v]--;
            if (inDegree[v] == 0)
            {
                q.push(v);
            }
        }
        topo.push_back(u);
    }
    reverse(topo.begin(), topo.end());

    vector<int> dp(tr.scc_count);
    for (int i = 0; i < tr.scc_count; i++)
    {
        dp[i] = comp_size[i];
    }
    for (int c : topo)
    {
        for (auto v : dag[c])
        {
            dp[c] += dp[v];
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << dp[tr.comp_id[i]] << " ";
    }
    cout << endl;
    return 0;
}