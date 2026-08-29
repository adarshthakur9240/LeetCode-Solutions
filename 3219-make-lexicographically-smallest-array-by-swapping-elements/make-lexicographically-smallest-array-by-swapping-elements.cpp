class Solution {
public:
    static vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        const int n = nums.size();
        vector<int> idx(n, 0);
        iota(idx.begin(), idx.end(), 0);  // Initialize indices
        
        // Sort indices based on values in nums
        stable_sort(idx.begin(), idx.end(), [&](int i, int j) {
            return nums[i] < nums[j];
        });

        vector<vector<int>> group = {{idx[0]}};
        int prev = nums[idx[0]];

        // Create groups based on the limit condition
        for (int i = 1; i < n; i++) {
            int I = idx[i], x = nums[I];
            if (x - prev <= limit) 
                group.back().push_back(I);
             else 
                group.push_back({I});
            prev = x;
        }

        // Sort indices within each group and assign values to nums
        for (auto& seq : group) {
            vector<int> values;
            for (int index : seq) 
                values.push_back(nums[index]);

            sort(seq.begin(), seq.end());  
            for (int i = 0; i < seq.size(); i++) {
                nums[seq[i]] = values[i];
            }
        }

        return nums;
    }
};