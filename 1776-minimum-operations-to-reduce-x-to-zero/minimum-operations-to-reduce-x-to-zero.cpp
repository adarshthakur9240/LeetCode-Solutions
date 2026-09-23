class Solution {
public:
    static int minOperations(vector<int>& nums, int x) {
        int n=nums.size();
        int prefix=nums[0];
        int sz=n;
        for(int i=1; i<n; i++){
            if (prefix>x) {
                sz=i;
                break;
            }
            prefix+=nums[i];
        }
        
        if (sz==n && prefix<x) //impossible
            return -1;

        prefix-=nums[sz-1];// let prefix<=x
        int idx=sz-1;
        int ans=INT_MAX;
        if (idx>=0 && prefix==x) ans=sz-1;

        int suffix=0;
        for (int j=n-1; j>=0; j--) {
            suffix+=nums[j];
            while (suffix+prefix>x && prefix>0){
                idx--;
                prefix-=nums[idx];
                if (suffix+prefix <=x ) break;
            }
            if (suffix+prefix==x){
                ans=min(ans, (n-j)+idx);
            } 
            if (suffix>=x) break;
        }
        return ans==INT_MAX?-1 : ans;
    }
};

auto init = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();