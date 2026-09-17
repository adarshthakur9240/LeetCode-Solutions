#include <vector>
#include <unordered_map>
#include <climits>
using namespace std;

class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        unordered_map<int, int> sumIndex;
        sumIndex[0] = -1;

        vector<int> minLenLeft(n, INT_MAX);
        int res = INT_MAX;
        int currSum = 0;
        int minLen = INT_MAX;

        for (int i = 0; i < n; ++i) {
            currSum += arr[i];

            if (sumIndex.find(currSum - target) != sumIndex.end()) {
                int start = sumIndex[currSum - target] + 1;
                int len = i - start + 1;
                if (start > 0 && minLenLeft[start - 1] != INT_MAX) {
                    res = min(res, minLenLeft[start - 1] + len);
                }
                minLen = min(minLen, len);
            }
            minLenLeft[i] = minLen;
            sumIndex[currSum] = i;
        }

        return res == INT_MAX ? -1 : res;
    }
};
