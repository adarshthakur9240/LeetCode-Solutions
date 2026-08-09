class Solution {
public:
    map<tuple<int, int, int>, int> memo;
    int n;
    vector<int> piles;

    int solve(int player, int i, int M) {
        if (i >= n) return 0;

        auto key = make_tuple(player, i, M);
        if (memo.count(key)) return memo[key];

        int stones = 0;
        int result = (player == 1) ? 0 : INT_MAX;

        for (int x = 1; x <= 2 * M; x++) {
            if (i + x > n) break;

            stones += piles[x + i - 1];
            if (player == 1) {
                result = max(result, stones + solve(0, i + x, max(M, x)));
            } else {
                result = min(result, solve(1, i + x, max(M, x)));
            }
        }

        memo[key] = result;
        return result;
    }

    int stoneGameII(vector<int>& p) {
        piles = p;
        n = piles.size();
        return solve(1, 0, 1);
    }
};