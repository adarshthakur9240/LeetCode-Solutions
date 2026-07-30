class Solution {
public:
    int minimumPushes(string word) {
        int n = word.size();

        int q = n / 8;
        int r = n % 8;

        return (q + 1) * (4 * q + r);
    }
};