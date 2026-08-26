class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int l = 0, r = 0;
        int onesCount = 0;
        int shortestLength = INT_MAX;
        int startIndex = -1;
        vector<string> ans;

        while (r < s.length()) {
            if (s[r] == '1') {
                onesCount++;
            }

            while (onesCount == k) {
                if (r - l + 1 <= shortestLength) {
                    if (r - l + 1 < shortestLength) {
                        ans.clear();  // Start a new set of substrings if shorter
                    }
                    shortestLength = r - l + 1;
                    startIndex = l;
                    ans.push_back(s.substr(startIndex, shortestLength));
                }

                if (s[l] == '1') {
                    onesCount--;
                }

                l++;
            }

            r++;
        }

        if (startIndex == -1) {
            return "";
        }

        sort(ans.begin(), ans.end());

        for (int i = 0; i < ans.size(); i++) {
            if (ans[i].length() == shortestLength) {
                return ans[i];
            }
        }

        return "";
    }
};