class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int minOdd = INT_MAX;
        int minEven = INT_MAX;

        for (int ele : nums1) {
            if (ele % 2 == 0) {
                minEven = min(ele, minEven);
            } else {
                minOdd = min(ele, minOdd);
            }
        }

        if (minOdd == INT_MAX || minEven == INT_MAX)
            return true;

        return minOdd < minEven;
    }
};