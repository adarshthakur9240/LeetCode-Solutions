class Solution {
public:
    int kItemsWithMaximumSum(int numOnes, int numZeros, int numNegOnes, int k) {
        
        int pickOnes = std::min(numOnes, k);
        k -= pickOnes;

        
        int pickZeros = std::min(numZeros, k);
        k -= pickZeros;


        int pickNegOnes = std::min(numNegOnes, k);

        
        return pickOnes - pickNegOnes;
    }
};
