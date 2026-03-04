#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1679: Course Schedule I
    Pattern: topo sort (Kahn's algo / dfs)
    Time: O(E+V) Space: O(E+V)
    Link: https://cses.fi/problemset/task/1679
*/
/* Approach:
   use standard topo sort (Kahn's algo / dfs)
*/

bool dfs(int u, vector<vector<int>> &adj, vector<bool> &visited, vector<bool> &inRec, stack<int> &ans)
{
    visited[u] = true;
    inRec[u] = true;
    for (auto v : adj[u])
    {
        if (!visited[v])
        {
            if (dfs(v, adj, visited, inRec, ans))
            {
                return true;
            }
        }
        else if (inRec[v])
        {
            return true;
        }
    }
    inRec[u] = false;
    ans.push(u + 1);
    return false;
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
    }

    /*with kahn's algorithm*/
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
        {
            q.push(i);
        }
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
        topo.push_back(u + 1);
    }
    /*
        if (topo.size() < n)
        {
            cout << "IMPOSSIBLE" << endl;
        }
        else
        {
            for (auto i : topo)
            {
                cout << i << " ";
            }
            cout << endl;
        }
    */
    /*with dfs*/
    stack<int> ans;
    vector<bool> visited(n, false);
    vector<bool> inRec(n, false);
    bool cycleFound = false;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
            if (dfs(i, adj, visited, inRec, ans))
            {
                cycleFound = true;
                break;
            }
    }

    if (cycleFound)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        while (!ans.empty())
        {
            cout << ans.top() << " ";
            ans.pop();
        }
        cout << endl;
    }
}