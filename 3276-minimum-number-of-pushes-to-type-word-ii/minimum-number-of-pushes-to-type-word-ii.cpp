class Solution {
public:
    int minimumPushes(string word) {
        vector<int> freq(26, 0);

        for (char ch : word) {
            freq[ch - 'a']++;
        }

        sort(freq.begin(), freq.end());

        int ans = 0;
        int push = 1;

        for (int i = 25; i >= 0; i--) {
            if (freq[i] == 0) break;

            ans += freq[i] * push;

            if ((25 - i + 1) % 8 == 0) {
                push++;
            }
        }

        return ans;
    }
};