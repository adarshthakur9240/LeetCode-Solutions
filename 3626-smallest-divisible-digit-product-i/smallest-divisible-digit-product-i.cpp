class Solution {
public:
    int product_digit(int x){
        int ans=1, d=0;
        for(; x; x/=10){
            d=x%10;
            ans*=d;
        }
        return ans;
    }
    int smallestNumber(int n, int t) {
        int P[2]={product_digit(n/10), product_digit(n/10+1)};
        int z0=((n/10)+1)*10;
        for(int z=n; z<n+10; z++){
            int p=P[z>=z0], d=z%10;
            if (p*d%t==0) return z;
        }
        return 0;
    }
};