class Solution {
    inline static int dp[400][1024];
    inline static int goal[400];
    inline static bool station[400];
    inline static int adj[400][4];
    inline static int adjs[400];

public:
    int minMoves(vector<string>& grid, int energy) {
        int m = grid.size();
        int n = grid[0].size();
        int start = -1;
        int litters = 0;
        fill(goal, goal + m * n, 0);
        fill(adjs, adjs + m * n, 0);

        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                int u = r * n + c;
                char ch = grid[r][c];
                station[u] = ch == 'R';
                if (ch == 'S')
                    start = u;
                else if (ch == 'L')
                    goal[u] = 1 << (litters++);
                if (ch != 'X') {
                    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                    for (auto& d : dirs) {
                        uint nr = r + d[0], nc = c + d[1];
                        if (nr < m && nc < n && grid[nr][nc] != 'X') {
                            adj[u][adjs[u]++] = nr * n + nc;
                        }
                    }
                }
            }
        }

        int target = (1 << litters) - 1;
        for (int i = 0; i < m * n; ++i) {
            fill(dp[i], dp[i] + target + 1, -1);
        }

        vector<int> curr, next;
        curr.push_back((start << 16) | energy);
        dp[start][0] = energy;

        for (int moves = 0; !curr.empty(); moves++) {
            for (int val : curr) {
                int u = val >> 16;
                int mask = (val >> 6) & 1023;
                int e = val & 63;
                if (mask == target)
                    return moves;
                if (e == 0)
                    continue;

                for (int i = 0; i < adjs[u]; ++i) {
                    int v = adj[u][i];
                    int ne = station[v] ? energy : e - 1;
                    int nmask = mask | goal[v];
                    if (ne > dp[v][nmask]) {
                        dp[v][nmask] = ne;
                        next.push_back((v << 16) | (nmask << 6) | ne);
                    }
                }
            }
            curr.swap(next);
            next.clear();
        }

        return -1;
    }
};