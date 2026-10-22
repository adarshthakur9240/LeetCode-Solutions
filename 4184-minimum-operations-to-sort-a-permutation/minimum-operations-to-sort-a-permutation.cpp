class Solution {
public:
    int minOperations(vector<int>& nums) {
        bool IisValid = true;
        int IbreakPoint = 0;
        int IBidx = -1;
        int n = nums.size();

        if (n == 1) return 0;

        for (int i = 0; i < n; ++i) {
            if (nums[i] > nums[(i + 1) % n]) {
                ++IbreakPoint;
                IBidx = (i + 1) % n;
            }

            if (IbreakPoint > 1) {
                IisValid = false;
                break;
            }
        }

        bool DisValid = true;
        int DbreakPoint = 0;
        int DBidx = -1;

        if (!IisValid) {
            for (int i = 0; i < n; ++i) {
                if (nums[i] < nums[(i + 1) % n]) {
                    ++DbreakPoint;
                    DBidx = (i + 1) % n;
                }

                if (DbreakPoint > 1) {
                    DisValid = false;
                    break;
                }
            }
        } else {
            DisValid = false;
        }

        if (!IisValid && !DisValid) return -1;

        if (IisValid) {
            return min(IBidx, n - IBidx + 2);
        } else {
            return 1 + min(DBidx, n - DBidx);
        }
    }
};