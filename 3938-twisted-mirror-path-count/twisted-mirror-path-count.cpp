class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1000000007;
        int m = grid.size(), n = grid[0].size();
        vector<int> right(n, 0), down(n, 0);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) {
                    right[0] = 1;
                    down[0] = 0;
                    continue;
                }
                int fromTop = 0;
                if (i > 0) {
                    fromTop = grid[i - 1][j] == 0
                                  ? (right[j] + down[j]) % MOD
                                  : right[j];
                }
                int fromLeft = 0;
                if (j > 0) {
                    fromLeft = grid[i][j - 1] == 0
                                   ? (right[j - 1] + down[j - 1]) % MOD
                                   : down[j - 1];
                }
                down[j] = fromTop;
                right[j] = fromLeft;
            }
        }
        return (right[n - 1] + down[n - 1]) % MOD;
    }
};