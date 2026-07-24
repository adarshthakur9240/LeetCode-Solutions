#include <vector>

using namespace std;

class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;
        long long MOD = 1e9 + 7;

        // Base cases
        if (n == 1) return m;
        if (n == 2) {
            long long ans = (long long)m * (m - 1);
            return ans % MOD;
        }

        // dpUp[v] stores the number of valid sequences ending in value v
        // where the last step was UP (i.e., previous value < v)
        vector<long long> dpUp(m + 1, 0);
        // dpDown[v] stores the number of valid sequences ending in value v
        // where the last step was DOWN (i.e., previous value > v)
        vector<long long> dpDown(m + 1, 0);

        // Initialize for sequences of length 2
        for (int v = 1; v <= m; ++v) {
            dpUp[v] = v - 1;       // Number of values < v
            dpDown[v] = m - v;     // Number of values > v
        }

        // Build up to length n
        for (int i = 3; i <= n; ++i) {
            vector<long long> next_dpUp(m + 1, 0);
            vector<long long> next_dpDown(m + 1, 0);

            // Calculate next_dpUp using prefix sums of dpDown
            long long sum_down = 0;
            for (int v = 1; v <= m; ++v) {
                // If we are at v, the previous value must be strictly less than v.
                // Since the last step was DOWN, the previous value came from dpDown.
                // We add dpDown[v-1] to our running sum.
                sum_down = (sum_down + dpDown[v - 1]) % MOD;
                next_dpUp[v] = sum_down;
            }

            // Calculate next_dpDown using suffix sums of dpUp
            long long sum_up = 0;
            for (int v = m; v >= 1; --v) {
                // If we are at v, the previous value must be strictly greater than v.
                // Since the last step was UP, the previous value came from dpUp.
                // We add dpUp[v+1] to our running sum.
                if (v + 1 <= m) {
                    sum_up = (sum_up + dpUp[v + 1]) % MOD;
                }
                next_dpDown[v] = sum_up;
            }

            // Update DP arrays for the next iteration
            dpUp = next_dpUp;
            dpDown = next_dpDown;
        }

        // Sum up all valid sequences of length n
        long long total_arrays = 0;
        for (int v = 1; v <= m; ++v) {
            total_arrays = (total_arrays + dpUp[v]) % MOD;
            total_arrays = (total_arrays + dpDown[v]) % MOD;
        }

        return total_arrays;
    }
};