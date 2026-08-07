// Nevermind I just doing experiment using binary search in C++
// But if you need solution in C++ here I go

class Solution {
public:

    string smallestNumber(string num, long long t) {

        // Find the count of factors of numbers from 2 to 9 in t
        int n = num.size();
        int factcount = count(t);

        if (factcount == INT_MAX) 
        return "-1";
        if (factcount > num.length()) 
        {
            // If there are more factors than digits in num
            return SmallestString(t, factcount);
        }

        // I use binary search to determine the smallest valid number
        long long l = 0, h = n, vl = -1, ans = -1;

        while (l <= h) 
        {
            long long mid = (l + h) / 2;
            long long crt = t;
            bool zeroEncountered = false;

            // Check factors in the first mid digits
            for (int i = 0; i < mid; i++) 
            {
                // Can't have a 0 dividing t
                if (num[i] == '0') 
                {
                    h = i;
                    zeroEncountered = true;
                    break;
                }
                // Divide t by gcd of current digit
                crt /= gcd(crt, num[i] - '0');
            }

            if (zeroEncountered) 
            continue;

            // If I can proceed with mid digits
            bool possible = false;

            if (mid == n) 
            {
                if (crt == 1) 
                return num;
            }
            else 
            {
                // Check if I can create a valid number using the next digit
                for (int i = max(1, num[mid] - '0'); i < 10; i++) 
                {
                    long long newT = crt / gcd(crt, i);
                    // Factors left
                    int positionsRequired = count(newT);

                    if (positionsRequired <= n - mid - 1 && (i > num[mid] - '0' || CreateGreaterWithRest(num, mid + 1, newT))) 
                    {
                        vl = i;
                        possible = true;
                        break;
                    }
                }
            }
            if (possible) 
            {
                // Expand search space to the right
                l = mid + 1;
                ans = mid;
            }
            else 
            {
                h = mid - 1;
            }
        }

        // Handle the result based on the search outcome
        long long crt = t;

        if (ans == -1) 
        {
            // Add a leading zero to the number
            num = '0' + num;
            int ind = n;

            // I try to fill from the end with factors
            for (int j = 9; j > 0; j--) 
            {
                while (ind > ans && crt % j == 0) 
                {
                    num[ind--] = '0' + j;
                    crt /= j;
                }
            }
            return num;
        }

        // Replace the digit at the position ans
        num[ans] = '0' + vl;

        for (int i = 0; i <= ans; i++) 
        {
            if (num[i] == '0') 
            continue;

            // Reduce t by using gcd
            crt /= gcd(crt, num[i] - '0');
        }

        int ind = n - 1;

        for (int j = 9; j > 0; j--) 
        {
            while (ind > ans && crt % j == 0) 
            {
                num[ind--] = '0' + j;
                crt /= j;
            }
        }
        return num;
    }

    // Fully represent t using digits 2-9
    string SmallestString(long long t, int ct) {

        string ans(ct, ' ');
        ct--;
        for (int i = 9; i > 1; i--) 
        {
            while (t % i == 0) 
            {
                ans[ct--] = '0' + i;
                t /= i;
            }
        }
        return ans;
    }

    // Counts the total number of factors of numbers 2-9 in vl
    int count(long long vl) 
    {
        int ct = 0;
        for (int i = 9; i > 1; i--) 
        {
            while (vl % i == 0) 
            {
                vl /= i;
                ct++;
            }
        }
        // If vl has factors outside 2-9
        if (vl > 1) 
        return INT_MAX;
        return ct;
    }

    // Checks if it is possible to create a greater number by replacing the digits after ind
    bool CreateGreaterWithRest(string& num, int ind, long long vl) {

        int ct = 0, n = num.size();
        vector<int> tp(10);

        // Factorize vl into digits 2-9
        for (int i = 9; i > 1; i--) 
        {
            while (vl % i == 0) 
            {
                tp[i]++;
                vl /= i;
                ct++;
            }
        }

        // Calculate how many extra positions are left after the current index and factor count
        int extraSpaces = n - ind - ct;
        tp[8] += tp[2] + tp[4];
        tp[2] = 0;
        tp[4] = 0;
        tp[9] += tp[3] + extraSpaces;
        tp[3] = 0;

        // Now, I attempt to form a valid number starting from index in the string by replacing digits
        for (int i = 9; i >= 1; i--) 
        {
            while (ind < n && tp[i] > 0) 
            {
                // This means I can create a larger number
                if (i > num[ind] - '0') 
                return true;
                if (i < num[ind] - '0') 
                return false;
                ind++;
                tp[i]--;
            }
        }
        return true; 
    }
};