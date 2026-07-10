class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int,int>>a(n);
        for(int i=0;i<n;i++){
            a[i]={nums[i],i};
        }
        sort(a.begin(),a.end());
        vector<int>getid(n);
        for(int i=0;i<n;i++){
            getid[a[i].second]=i;
        }
        //Sparse table for Binary Lifting
        int st[100005][18];
        int l=0;
        for(int r=0;r<n;r++){
            while(a[r].first-a[l].first>maxDiff){
                st[l][0]=r-1;
                l++;
            }
        }
        while(l<n){
            st[l][0]=n-1;
            l++;
        }

        for(int j=1;j<18;j++){
            for(int i=0;i<n;i++){
                st[i][j]=st[st[i][j-1]][j-1];
            }
        }

        vector<int>ans(queries.size(),-1);
        for(int i=0;i<queries.size();i++){
            int u=getid[queries[i][0]];
            int v=getid[queries[i][1]];
            if(u>v)swap(u,v);
            if(u==v){
                ans[i]=0;
                continue;
            }

            int cnt=0;
            for(int j=17;j>=0;j--){
                if(st[u][j]<v){
                    u=st[u][j];
                    cnt+=(1<<j);
                }
            }
            if(st[u][0]>=v)ans[i]=cnt+1;
        }
        return ans;
    }
};