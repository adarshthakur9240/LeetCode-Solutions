class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        int s=0, r=0;
        for(int x: nums){
            s+=(x<target);
            r+=(x==target);
        }
        vector<int> ans(r);
        iota(ans.begin(), ans.end(), s);
        return ans;
    }
};