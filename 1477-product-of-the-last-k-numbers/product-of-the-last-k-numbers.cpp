class ProductOfNumbers {
    vector<int> prefix{1};
    int lastZero = 0;
public:
    ProductOfNumbers() {}

    void add(int num) {
        if (num == 0) {
            prefix.push_back(1);
            lastZero = prefix.size() - 1;
        } else {
            prefix.push_back(prefix.back() * num);
        }
    }

    int getProduct(int k) {
        int n = prefix.size() - 1;
        if (lastZero >= n - k + 1) return 0;
        return prefix[n] / prefix[n - k];
    }
};