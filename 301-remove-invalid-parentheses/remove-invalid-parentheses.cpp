#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        auto isValid = [](const string& str) {
            int count = 0;
            for (char c : str) {
                if (c == '(') count++;
                else if (c == ')') {
                    if (count == 0) return false;
                    count--;
                }
            }
            return count == 0;
        };

        vector<string> res;
        unordered_set<string> visited;
        queue<string> q;
        bool found = false;

        q.push(s);
        visited.insert(s);

        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                string curr = q.front(); q.pop();
                if (isValid(curr)) {
                    res.push_back(curr);
                    found = true;
                }
                if (found) continue; // stop generating next level once found valid strings

                for (int j = 0; j < (int)curr.size(); j++) {
                    if (curr[j] != '(' && curr[j] != ')') continue;
                    string next = curr.substr(0, j) + curr.substr(j + 1);
                    if (!visited.count(next)) {
                        visited.insert(next);
                        q.push(next);
                    }
                }
            }
            if (found) break;
        }

        return res;
    }
};
