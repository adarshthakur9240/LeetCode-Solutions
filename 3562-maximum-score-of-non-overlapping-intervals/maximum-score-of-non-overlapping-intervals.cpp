const int N=5e4+1;
struct Data{
    int l, r, w, id=-1;
    Data(){}
    Data(int l, int r, int w, int id):l(l), r(r), w(w), id(id){}
    bool operator<(Data& o) const{
        return r<o.r;
    }
};
Data A[N];
using ll=long long;
ll dp[N][5];
array<int, 4> idx[N][5];
class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        const int n=intervals.size(), INF=INT_MAX;
        for(int i=0; i<n; i++){
            const auto& I=intervals[i];
            A[i]=Data(I[0], I[1], I[2], i);
        }
        sort(A, A+n);
        memset(dp, 0, sizeof(ll)*(n+1)*5);
        for(int i=0; i<=n; i++)
            for(int j=0; j<5; j++) idx[i][j].fill(INF);

        for(int i=0; i<n; i++){
            auto [l, r, w, id]=A[i];
            int k=lower_bound(A, A+i, l, [](const Data& d, int val) {
                return d.r < val;
            })-A;
            for(int j=1; j<5; j++){
                ll skip=dp[i][j];
                ll take=dp[k][j-1]+w;
                if (skip>take){
                    dp[i+1][j]=dp[i][j];
                    idx[i+1][j]=idx[i][j];
                }
                else{
                    dp[i+1][j]=take;
                    auto curIdx=idx[k][j-1];
                    curIdx[j-1]=id;
                    for (int a=j-2; a>=0; a--){
                        if (curIdx[a]<id) break;
                        swap(curIdx[a], curIdx[a+1]);
                    }
                    if (skip==take) idx[i+1][j]=min(idx[i][j], curIdx);
                    else  idx[i+1][j]=curIdx;
                }
            }
        }
        vector<int> ans;
        for(int i=0; i<4; i++){
            int id=idx[n][4][i];
            if (id==INF) break;
            ans.push_back(id);
        }
        return ans;
    }
};