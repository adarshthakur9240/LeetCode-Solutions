class Solution {
public:
    int minimumDeletions(vector<int>& A) {
        auto [it1, it2] = minmax_element(begin(A), end(A));
        int mini = it1 - begin(A), maxi = it2 - begin(A), n = size(A);
        return min({1+max(mini, maxi), n-min(mini, maxi), 1+min(mini, maxi) + (n-max(mini, maxi))});
    }
};