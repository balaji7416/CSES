#include <bits/stdc++.h>
using namespace std;

#define int long long

/*
    Problem 1684: Giant Pizza
    Pattern: Tarjan's algo + 2-SAT
    Time: O(E+V) Space: O(E+V)
    Link: https://cses.fi/problemset/task/1684
*/

/* Logic:
2-SAT modelling used in this solution:

2-SAT = Boolean satisfiability problem
        where each clause has 2 literals
#note: 3-SAT is NP-complete means there is no known polynomial time algorithm

Each ingredient i is represented by two nodes in the graph:
    i       -> +i  (ingredient i chosen with '+')
    i + n   -> -i  (ingredient i chosen with '-')

Thus total nodes = 2*n.

For every clause (A OR B) given in the input, we use the standard 2-SAT
implication transformation:

    (A OR B)  ≡  (!A -> B) AND (!B -> A)

So we add two directed edges in the implication graph:
    !A -> B
    !B -> A

Here negation is handled by switching between the two nodes of a variable:
    +i ↔ -i
    i  ↔ i+n

After building the implication graph we run Tarjan's SCC algorithm.

Key observations:
1. If a variable and its negation belong to the same strongly connected
   component, then they imply each other:
        x -> !x and !x -> x
        #note: false -> false, false -> true are perfectly valid
we try to first assing the later side of implication since it forces nothing
   which means both must be true simultaneously → contradiction.
   Hence the instance is impossible.

2. Tarjan assigns component ids in reverse topological order of the SCC DAG.
   Therefore implications always go from a larger component id to a smaller one.
   so if the dag of scc components is C1 -> C2 -> C3
   that means the comp_id(C1) > comp_id(C2) > comp_id(C3)
   that means if comp[i] < comp[!i] that means i appears later than !i that means !i -> ... -> i
   so we safely pick i = true since it doesn't forces anything

3. To obtain a valid assignment, we compare the component ids of a variable
   and its negation:
        if comp[i] < comp[i+n]  → choose '+'
        else                    → choose '-'

This picks the literal that appears later in the implication ordering,
ensuring no implication constraint is violated.

Time complexity:
    O((n + k)) for building the graph + Tarjan SCC.
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
    int k, n;
    cin >> k >> n;
    Tarjan tr(2 * n);

    for (int i = 0; i < k; i++)
    {
        char a, b;
        int u, v;
        cin >> a >> u >> b >> v;
        u--;
        v--;
        tr.addEdge(a == '+' ? u + n : u, b == '+' ? v : v + n);
        tr.addEdge(b == '+' ? v + n : v, (a == '+' ? u : u + n));
    }
    tr.run();
    vector<int> comp = tr.comp_id;
    for (int i = 0; i < n; i++)
    {
        if (comp[i] == comp[i + n])
        {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (comp[i] < comp[i + n])
        {
            cout << "+ ";
        }
        else
        {
            cout << "- ";
        }
    }
    cout << endl;
    return 0;
}