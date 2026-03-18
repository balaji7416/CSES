#include <bits/stdc++.h>
using namespace std;

#define int long long

/*
    Problem 1687: Company Queries I
    Pattern: ???
    Time: O(E+V) Space: O(E+V)
    Link: https://cses.fi/problemset/task/1687
*/

/* IDEA / LOGIC : Bin lifting - Powerful Beast,
Binary Lifting (Jump Pointers)

Goal:
Answer "k-th ancestor of node x" queries on a tree efficiently.

Key Idea:
Instead of moving to the parent k times, precompute ancestors at powers of two.

Definition:
up[v][j] = 2^j-th ancestor of node v

Example:
up[v][0] -> 1 step (parent)
up[v][1] -> 2 steps
up[v][2] -> 4 steps
up[v][3] -> 8 steps
...

Building the table:
Base case:
    up[v][0] = parent[v]

Transition:
    up[v][j] = up[ up[v][j-1] ][j-1]

Meaning:
A 2^j jump = two consecutive 2^(j-1) jumps.

Answering a query (x, k):
Decompose k into powers of two using binary representation.
For each bit j set in k:
    jump x = up[x][j]

Example:
k = 13 = 8 + 4 + 1
jump 2^3 -> 2^2 -> 2^0

Complexity:
Preprocessing: O(n log n)
Each query:    O(log n)
Time: O((n+q) log n)
Memory:  O(n log n)
*/

vector<int> parent;
vector<vector<int>> adj;

// Naive and intuitive solution - O(n^q) won't work for large inputs
void solve1()
{
    int n, q;
    cin >> n >> q;
    parent.resize(n, -1);
    for (int i = 0; i < n - 1; i++)
    {
        int u;
        cin >> u;
        u--;
        parent[i + 1] = u;
    }

    while (q--)
    {
        int x, k;
        cin >> x >> k;
        x--;
        for (int i = 0; i < k; i++)
        {
            x = parent[x];
            if (x == -1)
                break;
        }
        x == -1 ? cout << -1 << endl : cout << x + 1 << endl;
    }
}

/*solution built from optmizing the prev solution - O((n+q)logn)
 **binary lifting**
 */
const int LOG = 20; // since 2^20 = 1,048,576 which covers 2e5 range of n
vector<vector<int>> up;
void solve2()
{
    int n, q;
    cin >> n >> q;
    parent.resize(n, -1);
    up.resize(n, vector<int>(LOG, -1));

    for (int i = 0; i < n - 1; i++)
    {
        int u;
        cin >> u;
        u--;
        parent[i + 1] = u;
    }

    // build the bin lifting array

    // 1. base case: 2^0 = 1 the ancestor of node => simply direct parent[node]
    for (int i = 0; i < n; i++)
    {
        up[i][0] = parent[i];
    }

    // 2. build the complete array
    for (int j = 1; j < LOG; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (up[i][j - 1] == -1)
                continue;
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }

    // now answer the queries
    auto k_ansc = [&](int x, int k) -> int
    {
        int j = 0;
        while (k && x != -1)
        {
            if (k & 1)
            {
                x = up[x][j];
            }
            k >>= 1; // drop the least significant bit
            j++;
        }
        return x;
    };
    while (q--)
    {
        int x, k;
        cin >> x >> k;
        x--;
        int ans = k_ansc(x, k);
        ans == -1 ? cout << -1 << endl : cout << ans + 1 << endl;
    }
}

int32_t main()
{
    ios::sync_with_stdio(false);

    // solve1();
    solve2();
    return 0;
}