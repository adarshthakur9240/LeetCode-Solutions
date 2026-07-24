class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int n = nums.size();

        map<int, int> freq1;
        map<int, int> freq2;

        int maxFreq1 = 0;
        int maxFreqNum1;
        int maxFreq2 = 0;
        int maxFreqNum2;
        for (int i = 0; i < n; i++) {
            int num = nums[i];

            if (i % 2 == 0) {
                freq1[num] = freq1[num] + 1;
                if (freq1[num] > maxFreq1) {
                    maxFreq1 = freq1[num];
                    maxFreqNum1 = num;
                }
            }
            else {
                freq2[num] = freq2[num] + 1;
                if (freq2[num] > maxFreq2) {
                    maxFreq2 = freq2[num];
                    maxFreqNum2 = num;
                }
            }
        }

        if (maxFreqNum1 != maxFreqNum2) {
            return (ceil(n / 2.0) - maxFreq1) + ((n / 2) - maxFreq2); 
        }

        freq1.erase(maxFreqNum1);
        freq2.erase(maxFreqNum2);

        int secondMaxFreq1 = 0;
        int secondMaxFreq2 = 0;
        for (auto itr = freq1.begin(); itr != freq1.end(); itr++) {
            secondMaxFreq1 = max(secondMaxFreq1, itr -> second);
        }
        for (auto itr = freq2.begin(); itr != freq2.end(); itr++) {
            secondMaxFreq2 = max(secondMaxFreq2, itr -> second);
        }

        return min(
                (ceil(n / 2.0) - maxFreq1) + ((n / 2) - secondMaxFreq2),
                (ceil(n / 2.0) - secondMaxFreq1) + ((n / 2) - maxFreq2)
            );
    }
};