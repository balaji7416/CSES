#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1192: Counting Rooms
    Pattern: dfs/bfs
    Time: O(n*m) Space: O(n*m)
    Link: https://cses.fi/problemset/task/1192
*/

/* LOGIC: count the no.of connected components
   1. run dfs on the grid from each unvisited cell
   2. mark all cells reachable by dfs as visited
   3. count the connected components
*/

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void dfs(int i, int j, vector<vector<char>> &grid, vector<vector<bool>> &visited)
{
    int n = grid.size();
    int m = grid[0].size();
    if (i < 0 || i >= n || j < 0 || j >= m)
    {
        return;
    }
    if (grid[i][j] == '#' || visited[i][j])
    {
        return;
    }
    visited[i][j] = true;
    for (int k = 0; k < 4; k++)
    {
        dfs(i + dx[k], j + dy[k], grid, visited);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m, '.'));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];
        }
    }
    int rooms = 0;
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '.' && !visited[i][j])
            {
                dfs(i, j, grid, visited);
                rooms++;
            }
        }
    }
    cout << rooms << endl;
    return 0;
}