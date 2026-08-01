class Solution {
public:
    int solve(vector<int>& nums, int i, int j) {
        if (i > j) {
            return 0;
        }

        if (i == j) {
            return nums[i];
        }

        int take_i = nums[i] - solve(nums, i + 1, j);
        int take_j = nums[j] - solve(nums, i, j - 1);

        return max(take_i, take_j);
    }

    bool predictTheWinner(vector<int>& nums) {
        return solve(nums, 0, nums.size() - 1) >= 0;
    }
};