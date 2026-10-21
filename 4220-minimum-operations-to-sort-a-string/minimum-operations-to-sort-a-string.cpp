
class Solution {
public:
    int minOperations(string s) {
        int n = s.size();

        // Case 1: Already sorted
        if (is_sorted(s.begin(), s.end())) {
            return 0;
        }

        // Case 2: An unsorted string of length 2
        // can only be sorted by selecting the entire string,
        // which is not allowed.
        if (n == 2) {
            return -1;
        }

        char mn = *min_element(s.begin(), s.end());
        char mx = *max_element(s.begin(), s.end());

        // Case 3: One operation is enough if the first
        // character is the minimum, or the last is the maximum.
        if (s[0] == mn || s[n - 1] == mx) {
            return 1;
        }

        // Count occurrences of the global minimum and maximum.
        int minCount = count(s.begin(), s.end(), mn);
        int maxCount = count(s.begin(), s.end(), mx);

        // Case 4: Three operations are needed when the first
        // character is the unique maximum and the last is
        // the unique minimum.
        if (s[0] == mx && maxCount == 1 &&
            s[n - 1] == mn && minCount == 1) {
            return 3;
        }

        // Case 5: All other unsorted strings need two operations.
        return 2;
    }
};