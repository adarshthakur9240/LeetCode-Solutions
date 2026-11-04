#include <bits/stdc++.h>
using namespace std;

class Solution {
    multiset<long long> left_half, right_half;
    long long sum_left = 0, sum_right = 0;
    int target_left_size;

    void balance() {
        while ((int)left_half.size() > target_left_size) {
            auto it = prev(left_half.end());
            long long val = *it;

            sum_left -= val;
            left_half.erase(it);

            right_half.insert(val);
            sum_right += val;
        }

        while ((int)left_half.size() < target_left_size) {
            auto it = right_half.begin();
            long long val = *it;

            sum_right -= val;
            right_half.erase(it);

            left_half.insert(val);
            sum_left += val;
        }
    }

    void add(long long val) {
        if (left_half.empty() || val <= *left_half.rbegin()) {
            left_half.insert(val);
            sum_left += val;
        } else {
            right_half.insert(val);
            sum_right += val;
        }
    }

    void remove(long long val) {
        auto it = left_half.find(val);

        if (it != left_half.end()) {
            sum_left -= val;
            left_half.erase(it);
        } else {
            it = right_half.find(val);
            sum_right -= val;
            right_half.erase(it);
        }
    }

    long long get_cost() {
        long long median = *left_half.rbegin();

        long long left_cost =
            median * (long long)left_half.size() - sum_left;

        long long right_cost =
            sum_right - median * (long long)right_half.size();

        return left_cost + right_cost;
    }

public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        left_half.clear();
        right_half.clear();
        sum_left = 0;
        sum_right = 0;

        target_left_size = (x + 1) / 2;

        vector<long long> cost(n, 0);

        for (int i = 0; i < n; i++) {
            add(nums[i]);

            if (i >= x) {
                remove(nums[i - x]);
            }

            if (i >= x - 1) {
                balance();
                cost[i] = get_cost();
            }
        }

        const long long INF = 1e18;

        vector<long long> prev_dp(n + 1, 0);
        vector<long long> curr_dp(n + 1, INF);

        for (int j = 1; j <= k; j++) {
            fill(curr_dp.begin(), curr_dp.end(), INF);

            for (int i = j * x; i <= n; i++) {
                curr_dp[i] = curr_dp[i - 1];

                if (prev_dp[i - x] != INF) {
                    curr_dp[i] = min(curr_dp[i], prev_dp[i - x] + cost[i - 1]);
                }
            }

            prev_dp.swap(curr_dp);
        }

        return prev_dp[n];
    }
};