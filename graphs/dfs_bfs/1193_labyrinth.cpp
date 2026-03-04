#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1193: Labyrinth
    Pattern: BFS
    Time: O(n*m) Space: O(n*m)
    Link: https://cses.fi/problemset/task/1193
*/

/* LOGIC:

We need to find the shortest path from 'A' to 'B' in a grid.
Since all moves have equal cost, BFS guarantees the shortest path.

Approach:
1. Locate starting cell 'A'.
2. Run BFS from 'A'.
3. For each valid neighbor (inside grid, not '#', not visited):
   - Mark visited.
   - Store its parent cell.
   - Store the direction taken to reach it (L, R, U, D).
4. Stop BFS as soon as 'B' is reached (shortest path found).

Path Reconstruction:
- If 'B' was never reached → answer is "NO".
- Otherwise:
  - Backtrack from 'B' to 'A' using the parent matrix.
  - Collect stored directions.
  - Reverse the string to get correct order.

Key Points:
- BFS ensures shortest path in unweighted grid.
- Parent matrix is used to reconstruct the path.
- Direction matrix avoids recomputing moves during backtracking.

Time Complexity: O(n * m)
Space Complexity: O(n * m)
*/

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
char dirc(int i, int j)
{
    if (i == 0 && j == 1)
    {
        return 'R';
    }
    else if (i == 0 && j == -1)
    {
        return 'L';
    }
    else if (i == 1 && j == 0)
    {
        return 'D';
    }
    else
    {
        return 'U';
    }
}
char moves[] = {'R', 'L', 'D', 'U'}; // use direction[r][c] = moves[i]
string bfs(int r, int c, vector<vector<char>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    queue<pair<int, int>> q; //{row,col}
    q.push({r, c});
    visited[r][c] = true;
    // string path = "";
    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));
    vector<vector<char>> direction(n, vector<char>(m, '*'));

    int end_r = -1, end_c = -1;
    while (!q.empty())
    {
        auto [i, j] = q.front();
        q.pop();
        if (grid[i][j] == 'B')
        {
            end_r = i, end_c = j;
            break;
        }
        for (int k = 0; k < 4; k++)
        {
            int nr = i + dx[k];
            int nc = j + dy[k];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] != '#' && !visited[nr][nc])
            {
                visited[nr][nc] = true;
                parent[nr][nc] = {i, j};
                // direction[nr][nc] = dirc(dx[k], dy[k]);
                direction[nr][nc] = moves[k];
                q.push({nr, nc});
            }
        }
    }
    if (end_r == -1)
        return "";
    string path = "";
    int i = end_r, j = end_c;
    while (i != r || j != c)
    {
        path += direction[i][j];
        auto [pr, pc] = parent[i][j];
        i = pr, j = pc;
    }
    reverse(path.begin(), path.end());
    return path;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];
        }
    }
    string path = "";
    bool found = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 'A')
            {
                path = bfs(i, j, grid);
                found = true;
                break;
            }
        }
        if (found)
            break;
    }
    if (path == "")
    {
        cout << "NO" << endl;
    }
    else
    {
        cout << "YES" << endl;
        cout << path.size() << endl;
        cout << path << endl;
    }
}