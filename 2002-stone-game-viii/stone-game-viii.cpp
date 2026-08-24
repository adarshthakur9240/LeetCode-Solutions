class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        const int n = stones.size();
        for(int i = 1; i < n; ++i) stones[i] += stones[i - 1];
        int dp = stones[n - 1];
        for(int i = n - 2; i > 0; --i) dp = max(dp , stones[i] - dp);
        return dp;
    }
};