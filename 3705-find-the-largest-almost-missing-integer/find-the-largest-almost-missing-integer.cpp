class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> subarray_count;
        
        // Process all subarrays of size k
        for (int i = 0; i <= n - k; ++i) {
            unordered_set<int> unique_nums(nums.begin() + i, nums.begin() + i + k);
            for (int num : unique_nums) {
                subarray_count[num]++;
            }
        }
        
        // Find the largest integer that appears in exactly one subarray
        int ans = -1;
        for (const auto& [num, count] : subarray_count) {
            if (count == 1 && num > ans) {
                ans = num;
            }
        }
        
        return ans;
    }
};