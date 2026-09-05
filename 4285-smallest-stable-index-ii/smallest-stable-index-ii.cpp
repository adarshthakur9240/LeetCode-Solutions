class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> prefix(n);
        vector<int> suffix(n);
        prefix[0] = nums[0];
        suffix [n-1] = nums[n-1];
        for(int i=1;i<n;i++){
            prefix[i] = max(nums[i],prefix[i-1]);
        }
        for(int i=n-2;i>=0;i--){
            suffix[i] = min(nums[i],suffix[i+1]);
        }
        for(int i=0;i<n;i++) {
            int diff = prefix[i]-suffix[i];
            if(diff <= k) return i;
        }
        return -1;
    }
};